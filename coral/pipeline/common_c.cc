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
CoralPipelineTensorCreate(CoralPipelinedModelRunner *runner, size_t n,
                          TfLiteType type) {

  return new CoralPipelineTensor{coral::PipelineTensor{
      .type = type,
      .buffer = CHECK_NOTNULL(
          CHECK_NOTNULL(CHECK_NOTNULL(CHECK_NOTNULL(runner)->runner)
                            ->GetInputTensorAllocator())
              ->Alloc(n)),
      .bytes = n}};
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
                                       const char *buf, size_t n) {
  std::copy_n(CHECK_NOTNULL(buf), n,
              reinterpret_cast<char *>(CHECK_NOTNULL(
                  CHECK_NOTNULL(CHECK_NOTNULL(tensor)->tensor.buffer)->ptr())));
}

void CoralPipelineTensorCopyToBuffer(const CoralPipelineTensor *tensor,
                                     char *buf, size_t n) {
  std::copy_n(reinterpret_cast<const char *>(CHECK_NOTNULL(
                  CHECK_NOTNULL(CHECK_NOTNULL(tensor)->tensor.buffer)->ptr())),
              n, CHECK_NOTNULL(buf));
}

#ifdef __cplusplus
}
#endif
