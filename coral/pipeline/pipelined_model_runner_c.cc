#include <vector>

#include "coral/pipeline/allocator_c_internal.h"
#include "coral/pipeline/common_c.h"
#include "coral/pipeline/common_c_internal.h"
#include "coral/pipeline/internal/default_allocator_c.h"
#include "coral/pipeline/pipelined_model_runner.h"
#include "coral/pipeline/pipelined_model_runner_c.h"
#include "tensorflow/lite/c/c_api_internal.h"

#ifdef __cplusplus
extern "C" {
#endif

struct CoralPipelinedModelRunner {
  coral::PipelinedModelRunner runner;
};

CoralPipelinedModelRunner *
CoralPipelinedModelRunnerCreate(TfLiteInterpreter **raw_interpreters,
                                std::size_t n,
                                CoralAllocator *input_tensor_allocator,
                                CoralAllocator *output_tensor_allocator) {
  std::vector<tflite::Interpreter *> interpreters(n);
  for (std::size_t i = 0; i < n; ++i) {
    interpreters[i] = raw_interpreters[i]->impl.get();
  }
  return new CoralPipelinedModelRunner{coral::PipelinedModelRunner(
      interpreters, input_tensor_allocator->allocator,
      output_tensor_allocator->allocator)};
}

void CoralPipelinedModelRunnerDestroy(CoralPipelinedModelRunner *runner) {
  delete runner;
}

CoralAllocator *CoralPipelinedModelRunnerGetInputTensorAllocator(
    CoralPipelinedModelRunner *runner) {
  return new CoralAllocator{runner->runner.GetInputTensorAllocator()};
}

CoralAllocator *CoralPipelinedModelRunnerGetOutputTensorAllocator(
    CoralPipelinedModelRunner *runner) {
  return new CoralAllocator{runner->runner.GetOutputTensorAllocator()};
}

void CoralPipelinedModelRunnerDestroyAllocator(CoralAllocator *allocator) {
  delete allocator;
}

bool CoralPipelinedModelRunnerPush(CoralPipelinedModelRunner *runner,
                                   CoralPipelineTensor *tensors,
                                   std::size_t n) {
  std::vector<coral::PipelineTensor> input_tensors(n);
  for (std::size_t i = 0; i < n; ++i) {
    input_tensors[i] = tensors[i].tensor;
  }
  return runner->runner.Push(input_tensors);
}

bool CoralPipelinedModelRunnerPop(CoralPipelinedModelRunner *runner,
                                  CoralPipelineTensor *raw_tensors,
                                  std::size_t *n) {
  std::vector<coral::PipelineTensor> tensors;
  bool result = runner->runner.Pop(&tensors);

  *n = tensors.size();
  for (std::size_t i = 0; i < *n; ++i) {
    raw_tensors[i].tensor = std::move(tensors[i]);
  }

  return result;
}

#ifdef __cplusplus
}
#endif
