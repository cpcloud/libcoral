HEADERS = [
  'strategy.h',
  'partitioner.h',
  'utils.h',
  'profiling_partition_util.h',
]

install_headers(HEADERS, subdir : 'coral/tools/partitioner')

coral_tools_partitioner_utils = declare_dependency(
  sources : [
    'utils.cc',
    'utils.h',
  ],
  dependencies : [
    absl_flat_hash_map,
    absl_flat_hash_set,
    absl_memory,
    glog,
    tensorflow_lite,
  ],
)

coral_tools_partitioner_strategy = declare_dependency(
  sources : [
    'strategy.cc',
    'strategy.h',
  ],
  dependencies : [
    coral_tools_partitioner_utils,
    absl_flat_hash_set,
    glog,
    tensorflow_lite,
  ],
  include_directories : include_directories('../../..'),
)

executable(
  'partition_with_num_ops',
  'partition_with_num_ops.cc',
  dependencies : [
    coral_tools_partitioner_strategy,
    coral_tools_partitioner_utils,
    absl_flags,
    absl_flags_parse,
    absl_strings,
    glog,
  ],
  install : true,
)

coral_tools_partitioner_partitioner = declare_dependency(
  sources : [
    'partitioner.cc',
    'partitioner.h',
  ],
  dependencies : [
    coral_tools_partitioner_strategy,
    coral_tools_partitioner_utils,
    absl_flat_hash_set,
    absl_memory,
    absl_strings,
    glog,
    tensorflow_lite,
  ],
)

if build_edgetpu_tests or build_benchmarks
  coral_tools_partitioner_profiling_partition_util = declare_dependency(
    sources : [
      'profiling_partition_util.cc',
      'profiling_partition_util.h',
    ],
    dependencies : [
      coral_tools_partitioner_strategy,
      coral_tools_partitioner_utils,
      coral_pipeline_test_utils,
      coral_tools_model_pipelining_benchmark_util,
      absl_flat_hash_map,
      absl_strings,
      glog,
      tensorflow_lite,
    ],
  )
endif

if build_benchmarks
  executable(
    'profiling_partitioner',
    'profiling_partitioner.cc',
    dependencies : [
      coral_tools_partitioner_profiling_partition_util,
      coral_tools_partitioner_strategy,
      coral_tools_partitioner_utils,
      coral_tools_model_pipelining_benchmark_util,
      absl_flags,
      absl_flags_parse,
      absl_strings,
      glog,
      edgetpu,
      dl,
    ],
    install : true,
  )
endif

if build_edgetpu_tests
  test(
    'coral_tools_partitioner_partitioner_test',
    executable(
      'coral_tools_partitioner_partitioner_test',
      'partitioner_test.cc',
      dependencies : [
        coral_test_data_models,
        coral_tools_partitioner_partitioner,
        coral_tools_partitioner_utils,
        coral_test_main_with_edgetpu,
        coral_test_utils,
        absl_flat_hash_set,
        absl_flags_parse,
        absl_memory,
        gtest,
        gmock,
        dl,
      ],
    ),
    is_parallel : false,
    suite : 'edgetpu',
  )

  test(
    'coral_tools_partitioner_utils_test',
    executable(
      'coral_tools_partitioner_utils_test',
      'utils_test.cc',
      dependencies: [
        coral_test_data_models,

        coral_tools_partitioner_utils,
        coral_test_main_with_edgetpu,
        coral_test_utils,
        absl_flags_parse,
        absl_memory,
        absl_strings,
        gtest,
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
    'coral_tools_partitioner_profiling_partition_util_test',
    executable(
      'coral_tools_partitioner_profiling_partition_util_test',
      'profiling_partition_util_test.cc',
      dependencies : [
        coral_test_data_models,
        coral_tools_partitioner_profiling_partition_util,
        coral_test_main_with_edgetpu,
        coral_test_utils,
        absl_flags_parse,
        absl_memory,
        absl_strings,
        gtest,
        gmock,
        glog,
        dl,
      ],
    ),
    is_parallel : false,
    suite : 'edgetpu',
  )
endif
