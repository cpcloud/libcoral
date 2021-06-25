#ifndef EDGETPU_CPP_PIPELINE_COMMON_C_H_
#define EDGETPU_CPP_PIPELINE_COMMON_C_H_

#include "tensorflow/lite/c/common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CoralPipelinedModelRunner CoralPipelinedModelRunner;
typedef struct CoralPipelineTensor CoralPipelineTensor;

CoralPipelineTensor *CoralPipelineTensorCreate(CoralPipelinedModelRunner *runner,
                                               size_t n, TfLiteType ty);
void CoralPipelineTensorDestroyWrapper(CoralPipelineTensor *tensor);
void CoralPipelineTensorCopyFromBuffer(CoralPipelineTensor *tensor,
                                       const char *buf, size_t n);
void CoralPipelineTensorCopyToBuffer(const CoralPipelineTensor *tensor,
                                     char *buf, size_t n);

#ifdef __cplusplus
}
#endif

#endif // EDGETPU_CPP_PIPELINE_COMMON_C_H_
