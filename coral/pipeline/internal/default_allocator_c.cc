#include "coral/pipeline/internal/default_allocator.h"
#include "coral/pipeline/internal/default_allocator_c.h"
#include "coral/pipeline/allocator_c_internal.h"

#ifdef __cplusplus
extern "C" {
#endif

void *CoralHeapBufferGetPtr(CoralBuffer *buffer) { return buffer->buffer->ptr(); }

CoralAllocator *CoralDefaultAllocatorCreate(void) {
  auto allocator = new CoralAllocator;
  allocator->allocator = new coral::internal::DefaultAllocator();
  return allocator;
}

void CoralDefaultAllocatorDestroy(CoralAllocator *allocator) {
  delete allocator->allocator;
  delete allocator;
}

CoralBuffer *CoralDefaultAllocatorAlloc(CoralAllocator *allocator, size_t size) {
  auto buf = new CoralBuffer;
  buf->buffer = allocator->allocator->Alloc(size);
  return buf;
}

void CoralDefaultAllocatorFree(CoralAllocator *allocator, CoralBuffer *buffer) {
  allocator->allocator->Free(buffer->buffer);
  delete buffer;
}

#ifdef __cplusplus
}
#endif
