#ifndef EDGETPU_CPP_PIPELINE_COMMON_C_H_
#define EDGETPU_CPP_PIPELINE_COMMON_C_H_

#include "tensorflow/lite/c/common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CoralPipelineTensor CoralPipelineTensor;
typedef struct CoralAllocator CoralAllocator;

CoralPipelineTensor *CoralPipelineTensorCreate(CoralAllocator *allocator,
                                               size_t n, TfLiteType ty);
void CoralPipelineTensorDestroy(CoralAllocator *allocator,
                                CoralPipelineTensor *tensor);

#ifdef __cplusplus
}
#endif

#endif // EDGETPU_CPP_PIPELINE_COMMON_C_H_
