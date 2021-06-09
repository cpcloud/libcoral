HEADERS = [
  'aligned_alloc.h',
  'thread_safe_queue.h',
  'default_allocator.h',
  'memory_pool_allocator.h',
  'segment_runner.h',
]

install_headers(HEADERS, subdir : 'coral/pipeline/internal')

coral_pipeline_internal_aligned_alloc = declare_dependency(
  sources : 'aligned_alloc.h'
)

coral_pipeline_internal_thread_safe_queue = declare_dependency(
  sources : 'thread_safe_queue.h',
  dependencies : [
    absl_synchronization,
    absl_time,
  ],
)

coral_pipeline_internal_default_allocator = declare_dependency(
  sources : 'default_allocator.h',
  dependencies : [
    coral_pipeline_allocator,
  ],
)

coral_pipeline_internal_memory_pool_allocator = declare_dependency(
  sources : [
    'memory_pool_allocator.cc',
    'memory_pool_allocator.h',
  ],
  dependencies : [
    coral_pipeline_internal_aligned_alloc,
    coral_pipeline_allocator,
    absl_node_hash_map,
    absl_synchronization,
    glog,
  ],
  include_directories : include_directories('../../..'),
)

coral_pipeline_internal_segment_runner = declare_dependency(
  sources : [
    'segment_runner.cc',
    'segment_runner.h',
  ],
  dependencies : [
    coral_pipeline_internal_thread_safe_queue,
    coral_pipeline_allocator,
    coral_pipeline_common,
    absl_base,
    absl_synchronization,
    glog,
    edgetpu,
    tensorflow_lite,
  ],
)

if build_tests
  test(
    'coral_pipeline_internal_memory_pool_allocator_test',
    executable(
      'coral_pipeline_internal_memory_pool_allocator_test',
      'memory_pool_allocator_test.cc',
      dependencies : [
        coral_pipeline_internal_memory_pool_allocator,
        coral_test_main,
        absl_flags_parse,
        absl_memory,
        gtest,
      ],
    ),
    suite : 'cpu',
  )

  test(
    'coral_pipeline_internal_segment_runner_test',
    executable(
      'coral_pipeline_internal_segment_runner_test',
      'segment_runner_test.cc',
      dependencies : [
        coral_test_data_models,

        coral_pipeline_internal_default_allocator,
        coral_pipeline_internal_segment_runner,
        coral_test_main_with_edgetpu,
        coral_test_utils,
        coral_pipeline_allocator,
        coral_pipeline_test_utils,
        coral_pipeline_utils,
        absl_flags_parse,
        absl_memory,
        gtest,
        glog,
        gmock,
        edgetpu,
        tensorflow_lite,
        dl,
      ],
    ),
    is_parallel : false,
    suite : 'edgetpu',
  )
endif
