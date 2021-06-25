#ifndef EDGETPU_CPP_PIPELINE_INTERNAL_DEFAULT_ALLOCATOR_C_H_
#define EDGETPU_CPP_PIPELINE_INTERNAL_DEFAULT_ALLOCATOR_C_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CoralBuffer CoralBuffer;
typedef struct CoralAllocator CoralAllocator;

void *CoralBufferGetPtr(CoralBuffer *buffer);

CoralAllocator *CoralDefaultAllocatorCreate(void);
void CoralDefaultAllocatorDestroy(CoralAllocator *allocator);

CoralBuffer *CoralDefaultAllocatorAlloc(CoralAllocator *allocator, size_t size);
void CoralDefaultAllocatorFree(CoralAllocator *allocator, CoralBuffer *buffer);

#ifdef __cplusplus
}
#endif

#endif // EDGETPU_CPP_PIPELINE_INTERNAL_DEFAULT_ALLOCATOR_C_H_
