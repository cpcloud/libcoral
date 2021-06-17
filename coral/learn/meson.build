HEADERS = [
  'utils.h',
  'imprinting_engine.h',
]

install_headers(HEADERS, subdir : 'coral/learn')

coral_learn_utils = declare_dependency(
  sources : [
    'utils.cc',
    'utils.h',
  ],
  dependencies : [
    coral_tflite_utils,
    absl_memory,
    absl_status,
    absl_strings,
    absl_span,
    flatbuffers,
    glog,
    tensorflow_lite,
  ],
)

coral_learn_imprinting_engine = declare_dependency(
  sources : [
    'imprinting_engine.cc',
    'imprinting_engine.h',
  ],
  dependencies : [
    coral_learn_utils,
    coral_tflite_utils,
    absl_algorithm_container,
    absl_memory,
    absl_status,
    absl_strings,
    absl_span,
    flatbuffers,
    glog,
    tensorflow_lite,
  ],
)

if build_edgetpu_tests
  test(
    'coral_learn_utils_test',
    executable(
      'coral_learn_utils_test',
      'utils_test.cc',
      dependencies : [
        coral_learn_utils,
        coral_test_main_with_edgetpu,
        coral_test_utils,
        coral_tflite_utils,
        absl_memory,
        absl_status,
        gtest,
        flatbuffers,
        glog,
        gmock,
        tensorflow_lite,
        dl,
      ],
    ),
    is_parallel : false,
    suite : 'edgetpu',
  )

  test(
    'coral_learn_imprinting_engine_test',
    executable(
      'coral_learn_imprinting_engine_test',
      'imprinting_engine_test.cc',
      dependencies : [
        coral_learn_imprinting_engine,
        coral_test_data_imprinting_images,
        coral_test_main_with_edgetpu,
        coral_test_utils,
        coral_tflite_utils,
        coral_classification_adapter,
        absl_memory,
        absl_status,
        absl_strings,
        absl_span,
        gtest,
        flatbuffers,
        glog,
        tensorflow_lite,
        dl,
      ],
    ),
    timeout : 0,
    is_parallel : false,
    suite : 'edgetpu',
  )
endif

subdir('backprop')
