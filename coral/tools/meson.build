HEADERS = [
  'tflite_graph_util.h',
  'model_pipelining_benchmark_util.h',
]

install_headers(HEADERS, subdir : 'coral/tools')

coral_tools_tflite_graph_util = declare_dependency(
  sources : [
    'tflite_graph_util.cc',
    'tflite_graph_util.h',
  ],
  dependencies : [
    absl_strings,
    flatbuffers,
    tensorflow_lite,
  ],
  include_directories : include_directories('../..'),
)

executable(
  'join_tflite_models',
  'join_tflite_models.cc',
  dependencies : [
    coral_tools_tflite_graph_util,
    absl_flags,
    absl_flags_parse,
    absl_strings,
    flatbuffers,
    glog,
  ],
  install : true,
)

if build_benchmarks or build_tests
  coral_tools_model_pipelining_benchmark_util = declare_dependency(
    sources : [
      'model_pipelining_benchmark_util.cc',
      'model_pipelining_benchmark_util.h',
    ],
    dependencies : [
      coral_test_utils,
      coral_tflite_utils,
      coral_pipeline_common,
      coral_pipeline_pipelined_model_runner,
      coral_pipeline_test_utils,
      coral_pipeline_utils,
      absl_flags,
      absl_flags_parse,
      absl_strings,
      glog,
      edgetpu,
      tensorflow_lite,
    ],
  )
endif

if build_benchmarks
  executable(
    'multiple_tpus_performance_analysis',
    'multiple_tpus_performance_analysis.cc',
    dependencies : [
      coral_test_data_images,
      coral_test_data_models,
      coral_test_utils,
      coral_tflite_utils,
      absl_flags,
      absl_flags_parse,
      absl_status,
      absl_span,
      glog,
      edgetpu,
      dl,
    ],
    install : true,
  )

  executable(
    'model_pipelining_performance_analysis',
    'model_pipelining_performance_analysis.cc',
    dependencies : [
      coral_tools_model_pipelining_benchmark_util,
      coral_pipeline_test_utils,
      absl_node_hash_map,
      absl_flags,
      absl_flags_parse,
      glog,
      edgetpu,
      dl,
    ],
    install : true,
  )
endif

if build_tests
  test(
    'coral_tools_tflite_graph_util_test',
    executable(
      'coral_tools_tflite_graph_util_test',
      'tflite_graph_util_test.cc',
      dependencies : [
        coral_test_data_tools_models,

        coral_tools_tflite_graph_util,
        coral_test_main_with_edgetpu,
        coral_test_utils,
        gtest,
        flatbuffers,
        glog,
        dl,
      ],
    ),
    timeout : 0,
    is_parallel : false,
    suite : 'stress',
  )
endif

subdir('partitioner')
