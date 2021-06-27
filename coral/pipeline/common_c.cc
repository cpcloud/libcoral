#include "coral/pipeline/common_c.h"
#include "coral/pipeline/common.h"
#include "coral/pipeline/common_c_internal.h"
#include "coral/pipeline/pipelined_model_runner_c_internal.h"

#include "tensorflow/lite/c/c_api_types.h"

#include "glog/logging.h"

#include <algorithm>

#ifdef __cplusplus
extern "C" {
#endif

CoralPipelineTensor *
CoralPipelineTensorCreate(CoralPipelinedModelRunner *runner, size_t bytes,
                          TfLiteType type) {

  return new CoralPipelineTensor{coral::PipelineTensor{
      .type = type,
      .buffer = CHECK_NOTNULL(
          CHECK_NOTNULL(CHECK_NOTNULL(CHECK_NOTNULL(runner)->runner)
                            ->GetInputTensorAllocator())
              ->Alloc(bytes)),
      .bytes = bytes}};
}

void CoralPipelineInputTensorDestroy(CoralPipelineTensor *tensor) {
  delete CHECK_NOTNULL(tensor);
}

void CoralPipelineOutputTensorDestroy(CoralPipelinedModelRunner *runner,
                                      CoralPipelineTensor *tensor) {
  CHECK_NOTNULL(
      CHECK_NOTNULL(CHECK_NOTNULL(runner)->runner)->GetOutputTensorAllocator())
      ->Free(CHECK_NOTNULL(tensor)->tensor.buffer);
  delete tensor;
}

void CoralPipelineTensorCopyFromBuffer(CoralPipelineTensor *tensor,
                                       const char *buf, size_t bytes) {
  std::copy_n(CHECK_NOTNULL(buf), bytes,
              reinterpret_cast<char *>(CHECK_NOTNULL(
                  CHECK_NOTNULL(CHECK_NOTNULL(tensor)->tensor.buffer)->ptr())));
}

void CoralPipelineTensorCopyToBuffer(const CoralPipelineTensor *tensor,
                                     char *buf, size_t bytes) {
  std::copy_n(reinterpret_cast<const char *>(CHECK_NOTNULL(
                  CHECK_NOTNULL(CHECK_NOTNULL(tensor)->tensor.buffer)->ptr())),
              bytes, CHECK_NOTNULL(buf));
}

#ifdef __cplusplus
}
#endif
