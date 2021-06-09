install_headers('file_utils.h', subdir : 'coral/examples')

coral_examples_file_utils = declare_dependency(
  sources : [
    'file_utils.cc',
    'file_utils.h',
  ],
  dependencies : [
    absl_strings,
    glog,
  ],
)

if build_examples
  executable(
    'coral_examples_two_models_one_tpu',
    'two_models_one_tpu.cc',
    dependencies : [
      coral_examples_file_utils,
      coral_tflite_utils,
      coral_classification_adapter,
      absl_flags,
      absl_flags_parse,
      glog,
      edgetpu,
      tensorflow_lite,
      dl,
    ],
    install : true,
  )

  executable(
    'coral_examples_two_models_two_tpus_threaded',
    'two_models_two_tpus_threaded.cc',
    dependencies : [
      coral_examples_file_utils,
      coral_tflite_utils,
      coral_classification_adapter,
      absl_flags,
      absl_flags_parse,
      glog,
      edgetpu,
      tensorflow_lite,
      dl,
    ],
    install : true,
  )

  executable(
    'coral_examples_classify_image',
    'classify_image.cc',
    dependencies : [
      coral_examples_file_utils,
      coral_tflite_utils,
      coral_classification_adapter,
      absl_flags,
      absl_flags_parse,
      glog,
      edgetpu,
      tensorflow_lite,
      dl,
    ],
    install : true,
  )

  executable(
    'coral_examples_backprop_last_layer',
    'backprop_last_layer.cc',
    dependencies : [
      coral_examples_file_utils,
      coral_tflite_utils,
      coral_classification_adapter,
      coral_learn_backprop_softmax_regression_model,
      absl_flags,
      absl_flags_parse,
      eigen3,
      flatbuffers,
      glog,
      edgetpu,
      tensorflow_lite,
      dl,
    ],
    install : true,
  )

  executable(
    'coral_examples_model_pipelining',
    'model_pipelining.cc',
    dependencies : [
      coral_pipeline_pipelined_model_runner,
      coral_pipeline_utils,
      edgetpu,
      tensorflow_lite,
      dl,
    ],
    install : true,
  )
endif
