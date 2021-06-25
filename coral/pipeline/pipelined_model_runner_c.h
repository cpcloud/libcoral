#ifndef EDGETPU_CPP_PIPELINE_PIPELINED_MODEL_RUNNER_C_H_
#define EDGETPU_CPP_PIPELINE_PIPELINED_MODEL_RUNNER_C_H_

#include "coral/pipeline/common_c.h"
#include "coral/pipeline/internal/default_allocator_c.h"
#include "coral/pipeline/pipelined_model_runner_c.h"
#include "tensorflow/lite/c/c_api.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CoralPipelinedModelRunner CoralPipelinedModelRunner;
typedef struct CoralAllocator CoralAllocator;

CoralAllocator *CoralPipelinedModelRunnerGetInputTensorAllocator(
    CoralPipelinedModelRunner *runner);
CoralAllocator *CoralPipelinedModelRunnerGetOutputTensorAllocator(
    CoralPipelinedModelRunner *runner);
void CoralPipelinedModelRunnerDestroyAllocator(CoralAllocator *allocator);
CoralPipelinedModelRunner *
CoralPipelinedModelRunnerCreate(TfLiteInterpreter **interpreters, size_t n,
                                CoralAllocator *input_tensor_allocator,
                                CoralAllocator *output_tensor_allocator);
void CoralPipelinedModelRunnerDestroy(CoralPipelinedModelRunner *runner);
bool CoralPipelinedModelRunnerPop(CoralPipelinedModelRunner *runner,
                                  CoralPipelineTensor *raw_tensors, size_t *n);
bool CoralPipelinedModelRunnerPush(CoralPipelinedModelRunner *runner,
                                   CoralPipelineTensor *tensors, size_t n);

#ifdef __cplusplus
}
#endif

#endif // EDGETPU_CPP_PIPELINE_PIPELINED_MODEL_RUNNER_C_H_
