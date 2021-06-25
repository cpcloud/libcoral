#include "coral/pipeline/common_c.h"
#include "coral/pipeline/allocator_c_internal.h"
#include "coral/pipeline/common.h"
#include "coral/pipeline/common_c_internal.h"
#include <algorithm>

#ifdef __cplusplus
extern "C" {
#endif

CoralPipelineTensor *CoralPipelineTensorCreate(CoralAllocator *allocator,
                                               size_t n, TfLiteType type) {
  return new CoralPipelineTensor{coral::PipelineTensor{
      .bytes = n, type = type, buffer = allocator->allocator->Alloc(n)}};
}

void CoralPipelineTensorDestroyWrapper(CoralPipelineTensor *tensor) {
  delete tensor;
}

void CoralPipelineTensorCopyFromBuffer(CoralPipelineTensor *tensor,
                                       const char *buf, size_t n) {
  std::copy_n(buf, n, reinterpret_cast<char *>(tensor->tensor.buffer->ptr()));
}

void CoralPipelineTensorCopyToBuffer(const CoralPipelineTensor *tensor,
                                     char *buf, size_t n) {
  std::copy_n(reinterpret_cast<char *>(tensor->tensor.buffer->ptr()), n, buf);
}

#ifdef __cplusplus
}
#endif
