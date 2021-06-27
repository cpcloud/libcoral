#ifndef EDGETPU_CPP_PIPELINE_PIPELINED_MODEL_RUNNER_C_H_
#define EDGETPU_CPP_PIPELINE_PIPELINED_MODEL_RUNNER_C_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CoralPipelinedModelRunner CoralPipelinedModelRunner;
typedef struct CoralPipelineTensor CoralPipelineTensor;
typedef struct TfLiteInterpreter TfLiteInterpreter;

typedef struct CoralSegmentStats {
  int64_t total_time_ns;
  uint64_t num_inferences;
} CoralSegmentStats;

CoralPipelinedModelRunner *
CoralPipelinedModelRunnerCreate(TfLiteInterpreter **interpreters, size_t n);
void CoralPipelinedModelRunnerDestroy(CoralPipelinedModelRunner *runner);

bool CoralPipelinedModelRunnerPush(CoralPipelinedModelRunner *runner,
                                   CoralPipelineTensor **tensors, size_t n);
bool CoralPipelinedModelRunnerPop(CoralPipelinedModelRunner *runner,
                                  CoralPipelineTensor **raw_tensors, size_t *n);

void CoralPipelinedModelRunnerSetInputQueueSize(
    CoralPipelinedModelRunner *runner, size_t input_queue_size);
void CoralPipelinedModelRunnerSetOutputQueueSize(
    CoralPipelinedModelRunner *runner, size_t output_queue_size);

CoralSegmentStats *CoralPipelinedModelRunnerGetSegmentStats(
    const CoralPipelinedModelRunner *runner, size_t *n);
void CoralPipelinedModelRunnerDestroySegmentStats(
    CoralSegmentStats *segment_stats);

size_t *
CoralPipelinedModelRunnerGetQueueSizes(const CoralPipelinedModelRunner *runner,
                                       size_t *n);
void CoralPipelinedModelRunnerDestroyQueueSizes(size_t *n);

#ifdef __cplusplus
}
#endif

#endif // EDGETPU_CPP_PIPELINE_PIPELINED_MODEL_RUNNER_C_H_
