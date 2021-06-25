#include "coral/pipeline/common_c.h"
#include "coral/pipeline/common_c_internal.h"
#include "coral/pipeline/common.h"
#include "coral/pipeline/allocator_c_internal.h"

#ifdef __cplusplus
extern "C" {
#endif

CoralPipelineTensor *CoralPipelineTensorCreate(CoralAllocator *allocator,
                                               size_t n, TfLiteType type) {
  auto tensor = new CoralPipelineTensor;
  tensor->tensor.bytes = n;
  tensor->tensor.type = type;
  tensor->tensor.buffer = allocator->allocator->Alloc(n);
  return tensor;
}

void CoralPipelineTensorDestroy(CoralAllocator *allocator,
                                CoralPipelineTensor *tensor) {
  allocator->allocator->Free(tensor->tensor.buffer);
  delete tensor;
}

#ifdef __cplusplus
}
#endif
