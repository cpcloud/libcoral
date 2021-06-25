#ifndef EDGETPU_CPP_PIPELINE_PIPELINED_MODEL_RUNNER_C_H_
#define EDGETPU_CPP_PIPELINE_PIPELINED_MODEL_RUNNER_C_H_

#include "tensorflow/lite/c/c_api.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CoralPipelinedModelRunner CoralPipelinedModelRunner;
typedef struct CoralPipelineTensor CoralPipelineTensor;

CoralPipelinedModelRunner *
CoralPipelinedModelRunnerCreate(TfLiteInterpreter **interpreters, size_t n);
void CoralPipelinedModelRunnerDestroy(CoralPipelinedModelRunner *runner);
bool CoralPipelinedModelRunnerPush(CoralPipelinedModelRunner *runner,
                                   CoralPipelineTensor **tensors, size_t n);
bool CoralPipelinedModelRunnerPop(CoralPipelinedModelRunner *runner,
                                  CoralPipelineTensor **raw_tensors, size_t *n);

#ifdef __cplusplus
}
#endif

#endif // EDGETPU_CPP_PIPELINE_PIPELINED_MODEL_RUNNER_C_H_
