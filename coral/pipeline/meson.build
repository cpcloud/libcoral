HEADERS = [
  'allocator.h',
  'allocator_c_internal.h',
  'common.h',
  'common_c.h',
  'common_c_internal.h',
  'pipelined_model_runner.h',
  'pipelined_model_runner_c.h',
  'utils.h',
]

install_headers(HEADERS, subdir : 'coral/pipeline')

coral_pipeline_allocator = declare_dependency(
  sources : 'allocator.h',
)

coral_pipeline_common = declare_dependency(
  sources : 'common.h',
  dependencies : [
    coral_pipeline_allocator,
    tensorflow_lite,
  ],
)

subdir('internal')

coral_pipeline_common_c = declare_dependency(
  sources : [
    'common_c.cc',
    'common_c.h',
  ],
  dependencies : [
    coral_pipeline_internal_default_allocator_c,
    tensorflow_lite,
  ],
)

coral_pipeline_utils = declare_dependency(
  sources : [
    'utils.cc',
    'utils.h',
  ],
  dependencies : [
    coral_pipeline_allocator,
    coral_pipeline_common,
    coral_pipeline_common_c,
    coral_pipeline_internal_default_allocator_c,
    tensorflow_lite,
  ],
)

if build_pipelining_tests or build_benchmarks
  coral_pipeline_test_utils = declare_dependency(
    sources : [
      'test_utils.cc',
      'test_utils.h',
    ],
    dependencies : [
      coral_pipeline_allocator,
      coral_pipeline_common,
      coral_test_utils,
      coral_tflite_utils,
      absl_strings,
      glog,
      edgetpu,
      tensorflow_lite,
    ],
  )
endif

coral_pipeline_pipelined_model_runner = declare_dependency(
  sources : [
    'pipelined_model_runner.cc',
    'pipelined_model_runner.h',
  ],
  dependencies : [
    coral_pipeline_allocator,
    coral_pipeline_common,
    coral_pipeline_utils,
    coral_pipeline_internal_default_allocator,
    coral_pipeline_internal_default_allocator_c,
    coral_pipeline_internal_memory_pool_allocator,
    coral_pipeline_internal_segment_runner,
    coral_pipeline_internal_thread_safe_queue,
    absl_memory,
    absl_synchronization,
    glog,
    tensorflow_lite,
  ],
)

coral_pipeline_pipelined_model_runner_c = declare_dependency(
  sources : [
    'pipelined_model_runner_c.cc',
    'pipelined_model_runner_c.h',
  ],
  dependencies : [
    coral_pipeline_allocator,
    coral_pipeline_common,
    coral_pipeline_common_c,
    coral_pipeline_utils,
    coral_pipeline_internal_default_allocator,
    coral_pipeline_internal_default_allocator_c,
    coral_pipeline_internal_memory_pool_allocator,
    coral_pipeline_internal_segment_runner,
    coral_pipeline_internal_thread_safe_queue,
    absl_memory,
    absl_synchronization,
    glog,
    tensorflow_lite,
  ],
)

if build_pipelining_tests
  test(
    'coral_pipeline_pipelined_model_runner_test',
    executable(
      'coral_pipeline_pipelined_model_runner_test',
      'pipelined_model_runner_test.cc',
      dependencies : [
        absl_flags,
        absl_flags_parse,
        absl_memory,
        absl_strings,
        coral_pipeline_common,
        coral_pipeline_pipelined_model_runner,
        coral_pipeline_test_utils,
        coral_pipeline_utils,
        coral_test_data_models,
        coral_test_data_pipeline_models,
        coral_test_main_with_edgetpu,
        coral_test_utils,
        coral_tflite_utils,
        dl,
        edgetpu,
        glog,
        gtest,
        tensorflow_lite,
      ],
    ),
    timeout : 0,
    is_parallel : false,
    suite : 'pipeline',
  )

  test(
    'coral_pipeline_models_test',
    executable(
      'coral_pipeline_models_test',
      'models_test_main.cc',
      dependencies : [
        absl_flags,
        absl_flags_parse,
        absl_memory,
        absl_strings,
        coral_pipeline_common,
        coral_pipeline_internal_default_allocator,
        coral_pipeline_pipelined_model_runner,
        coral_pipeline_test_utils,
        coral_pipeline_utils,
        coral_test_data_models,
        coral_test_data_pipeline_models,
        coral_test_utils,
        coral_tflite_utils,
        dl,
        edgetpu,
        glog,
        gtest,
        tensorflow_lite,
      ],
    ),
    timeout : 0,
    is_parallel : false,
    suite : 'pipeline',
  )
endif
