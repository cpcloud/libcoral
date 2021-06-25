#ifndef EDGETPU_CPP_PIPELINE_ALLOCATOR_C_INTERNAL_H_
#define EDGETPU_CPP_PIPELINE_ALLOCATOR_C_INTERNAL_H_

#include "coral/pipeline/allocator.h"

struct CoralBuffer {
  coral::Buffer *buffer;
};

struct CoralAllocator {
  coral::Allocator *allocator;
};

#endif // EDGETPU_CPP_PIPELINE_ALLOCATOR_C_INTERNAL_H_
