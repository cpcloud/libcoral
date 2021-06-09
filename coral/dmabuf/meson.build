if build_dmabuf_tests
  test(
    'coral_dmabuf_dmabuf_devboard_test',
    executable(
      'coral_dmabuf_dmabuf_devboard_test',
      'dmabuf_devboard_test.cc',
      dependencies : [
        coral_test_main_with_edgetpu,
        coral_test_utils,
        coral_tflite_utils,
        absl_flags_parse,
        absl_status,
        gtest,
        glog,
        edgetpu,
        gstallocators,
        gstreamer,
        dl,
      ],
    ),
    is_parallel : false,
    suite : 'dmabuf',
  )

  test(
    'coral_dmabuf_model_pipelining_dmabuf_devboard_test',
    executable(
      'coral_dmabuf_model_pipelining_dmabuf_devboard_test',
      'model_pipelining_dmabuf_devboard_test.cc',
      dependencies : [
        coral_test_main_with_edgetpu,
        coral_test_utils,
        coral_pipeline_pipelined_model_runner,
        coral_pipeline_test_utils,
        absl_flags_parse,
        absl_strings,
        gtest,
        glog,
        edgetpu,
        gstallocators,
        gstreamer,
        dl,
      ],
    ),
    is_parallel : false,
    suite : 'dmabuf',
  )
endif
