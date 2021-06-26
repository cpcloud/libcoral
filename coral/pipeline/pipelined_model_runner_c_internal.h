#ifndef EDGETPU_CPP_PIPELINE_PIPELINED_MODEL_RUNNER_C_INTERNAL_H_
#define EDGETPU_CPP_PIPELINE_PIPELINED_MODEL_RUNNER_C_INTERNAL_H_

#include <memory>
#include "coral/pipeline/pipelined_model_runner.h"

struct CoralPipelinedModelRunner {
  std::unique_ptr<coral::PipelinedModelRunner> runner;
};

#endif // EDGETPU_CPP_PIPELINE_PIPELINED_MODEL_RUNNER_C_INTERNAL_H_
