coral_detection_lib = library(
  'coral_detection',
  dependencies : [
    coral_detection_adapter,
    dl,
  ],
  install : true,
)

pkgconfig.generate(coral_detection_lib)

if build_cpu_tests
  test(
    'coral_detection_adapter_test',
    executable(
      'coral_detection_adapter_test',
      'adapter_test.cc',
      dependencies : [
        coral_test_data_models,
        coral_detection_adapter,
        coral_bbox,
        coral_test_main,
        absl_span,
        gtest,
        glog,
        dl,
        gmock
      ],
    ),
    suite : 'cpu',
  )
endif

if build_edgetpu_tests
  test(
    'coral_detection_models_test',
    executable(
      'coral_detection_models_test',
      'models_test.cc',
      dependencies : [
        coral_test_data_images,
        coral_test_data_models,
        coral_test_main_with_edgetpu,
        coral_test_utils,
        absl_strings,
        gtest,
        dl,
      ],
    ),
    is_parallel : false,
    suite : 'edgetpu',
  )
endif
