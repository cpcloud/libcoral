#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "glog/logging.h"

#include "coral/pipeline/common_c.h"
#include "coral/pipeline/common_c_internal.h"
#include "coral/pipeline/pipelined_model_runner.h"
#include "coral/pipeline/pipelined_model_runner_c.h"
#include "coral/pipeline/pipelined_model_runner_c_internal.h"
#include "tensorflow/lite/c/c_api.h"
#include "tensorflow/lite/c/c_api_internal.h"

#ifdef __cplusplus
extern "C" {
#endif

CoralPipelinedModelRunner *
CoralPipelinedModelRunnerCreate(TfLiteInterpreter **raw_interpreters,
                                std::size_t n) {
  CHECK_NOTNULL(raw_interpreters);

  std::vector<tflite::Interpreter *> interpreters;
  interpreters.reserve(n);

  for (std::size_t i = 0; i < n; ++i) {
    interpreters.push_back(CHECK_NOTNULL(
        CHECK_NOTNULL(CHECK_NOTNULL(raw_interpreters[i])->impl).get()));
  }

  return new CoralPipelinedModelRunner{
      .runner = std::make_unique<coral::PipelinedModelRunner>(interpreters)};
}

void CoralPipelinedModelRunnerDestroy(CoralPipelinedModelRunner *runner) {
  delete CHECK_NOTNULL(runner);
}

bool CoralPipelinedModelRunnerPush(CoralPipelinedModelRunner *runner,
                                   CoralPipelineTensor **tensors,
                                   std::size_t n) {
  CHECK_NOTNULL(tensors);

  std::vector<coral::PipelineTensor> input_tensors;
  input_tensors.reserve(n);

  for (std::size_t i = 0; i < n; ++i) {
    input_tensors.push_back(CHECK_NOTNULL(tensors[i])->tensor);
  }

  return CHECK_NOTNULL(CHECK_NOTNULL(runner)->runner)
      ->Push(std::move(input_tensors));
}

bool CoralPipelinedModelRunnerPop(CoralPipelinedModelRunner *runner,
                                  CoralPipelineTensor **raw_tensors,
                                  std::size_t *n) {
  CHECK_NOTNULL(raw_tensors);
  std::vector<coral::PipelineTensor> tensors;
  bool result = CHECK_NOTNULL(CHECK_NOTNULL(runner)->runner)->Pop(&tensors);

  *CHECK_NOTNULL(n) = tensors.size();
  CHECK_GE(*n, 1);

  for (std::size_t i = 0; i < *n; ++i) {
    raw_tensors[i] = new CoralPipelineTensor{.tensor = std::move(tensors[i])};
    CHECK_NOTNULL(raw_tensors[i]);
  }

  return result;
}

void CoralPipelinedModelRunnerSetInputQueueSize(
    CoralPipelinedModelRunner *runner, std::size_t input_queue_size) {
  CHECK_NOTNULL(CHECK_NOTNULL(runner)->runner)
      ->SetInputQueueSize(input_queue_size);
}

void CoralPipelinedModelRunnerSetOutputQueueSize(
    CoralPipelinedModelRunner *runner, std::size_t output_queue_size) {
  CHECK_NOTNULL(CHECK_NOTNULL(runner)->runner)
      ->SetOutputQueueSize(output_queue_size);
}

CoralSegmentStats *CoralPipelinedModelRunnerGetSegmentStats(
    const CoralPipelinedModelRunner *runner, std::size_t *n) {
  auto segment_stats =
      CHECK_NOTNULL(CHECK_NOTNULL(runner)->runner)->GetSegmentStats();
  *CHECK_NOTNULL(n) = segment_stats.size();
  CHECK_GE(*n, 1);

  auto stats = new CoralSegmentStats[*n];
  CHECK_NOTNULL(stats);

  for (std::size_t i = 0; i < *n; ++i) {
    stats[i].total_time_ns = segment_stats[i].total_time_ns;
    stats[i].num_inferences = segment_stats[i].num_inferences;
  }
  return stats;
}

void CoralPipelinedModelRunnerDestroySegmentStats(
    CoralSegmentStats *segment_stats) {
  delete[] CHECK_NOTNULL(segment_stats);
}

size_t *
CoralPipelinedModelRunnerGetQueueSizes(const CoralPipelinedModelRunner *runner,
                                       size_t *n) {
  const auto queue_sizes =
      CHECK_NOTNULL(CHECK_NOTNULL(runner)->runner)->GetQueueSizes();
  *CHECK_NOTNULL(n) = queue_sizes.size();
  auto result = new size_t[*n];
  std::copy_n(queue_sizes.cbegin(), *n, result);
  return result;
}

void CoralPipelinedModelRunnerDestroyQueueSizes(size_t *queue_sizes) {
  delete[] CHECK_NOTNULL(queue_sizes);
}

#ifdef __cplusplus
}
#endif
