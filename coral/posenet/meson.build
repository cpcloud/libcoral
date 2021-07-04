HEADERS = [
  'posenet_decoder_op.h',
  'posenet_decoder.h',
]

install_headers(HEADERS, subdir : 'coral/posenet')

coral_posenet_posenet_decoder = declare_dependency(
  sources : [
    'posenet_decoder.cc',
    'posenet_decoder.h',
  ],
  include_directories : include_directories('../..'),
)

coral_posenet_posenet_decoder_op = declare_dependency(
  sources : [
    'posenet_decoder_op.cc',
    'posenet_decoder_op.h',
  ],
  dependencies : [
    coral_posenet_posenet_decoder,
    flatbuffers,
    tensorflow_lite,
  ],
)

if build_edgetpu_tests
  coral_posenet_test_utils = declare_dependency(
    sources : [
      'test_utils.cc',
      'test_utils.h',
    ],
    dependencies : [
      coral_test_utils,
      coral_tflite_utils,
      absl_strings,
      absl_span,
      gtest,
    ],
  )

  test(
    'coral_posenet_bodypix_test',
    executable(
      'coral_posenet_bodypix_test',
      'bodypix_test.cc',
      dependencies : [
        coral_test_data_posenet_images,
        coral_test_data_posenet_models,
        coral_posenet_posenet_decoder_op,
        coral_posenet_test_utils,
        coral_test_main_with_edgetpu,
        coral_test_utils,
        coral_tflite_utils,
        absl_strings,
        gtest,
        glog,
        dl,
      ],
    ),
    is_parallel : false,
    suite : 'edgetpu',
  )

  test(
    'coral_posenet_models_test',
    executable(
      'coral_posenet_models_test',
      'models_test.cc',
      dependencies : [
        coral_test_data_posenet_images,
        coral_test_data_posenet_models,
        coral_test_data_posenet_reference_results,
        coral_posenet_posenet_decoder_op,
        coral_posenet_test_utils,
        coral_test_main_with_edgetpu,
        coral_test_utils,
        coral_tflite_utils,
        absl_flags,
        absl_flags_parse,
        gtest,
        glog,
        dl,
      ],
    ),
    is_parallel : false,
    suite : 'edgetpu',
  )

  test(
    'coral_posenet_posenet_decoder_test',
    executable(
      'coral_posenet_posenet_decoder_test',
      'posenet_decoder_test.cc',
      dependencies : [
        coral_posenet_posenet_decoder,
        coral_test_main,
        absl_strings,
        gtest,
        glog,
      ],
    ),
    suite : 'cpu',
  )
endif

if build_benchmarks
  POSENET_MODEL_BENCHMARK_CASES = [
    {
      'benchmark_name': 'BM_PoseNet_MobileNetV1_075_353_481_WithDecoder',
      'model_path': 'posenet/posenet_mobilenet_v1_075_353_481_quant_decoder',
    },
    {
      'benchmark_name': 'BM_PoseNet_MobileNetV1_075_481_641_WithDecoder',
      'model_path': 'posenet/posenet_mobilenet_v1_075_481_641_quant_decoder',
    },
    {
      'benchmark_name': 'BM_PoseNet_MobileNetV1_075_721_1281_WithDecoder',
      'model_path': 'posenet/posenet_mobilenet_v1_075_721_1281_quant_decoder',
    },
  ]

  posenet_model_benchmark_deps = []

  foreach case : POSENET_MODEL_BENCHMARK_CASES
    model_path = case.get('model_path')
    benchmark_name = case.get('benchmark_name')
    posenet_model_benchmark_deps += declare_dependency(
      link_with : library(
        benchmark_name,
        '../models_benchmark_lib.cc',
        cpp_args : [
          '-DARG_BENCHMARK_NAME=@0@'.format(benchmark_name),
          '-DARG_TFLITE_CPU_FILEPATH=@0@.tflite'.format(model_path),
          '-DARG_TFLITE_EDGETPU_FILEPATH=@0@_edgetpu.tflite'.format(model_path),
          '-DARG_RUN_CPU_MODEL=@0@'.format(case.get('run_cpu_model', 1)),
          '-DARG_RUN_EDGETPU_MODEL=@0@'.format(case.get('run_edgetpu_model', 1)),
        ],
        dependencies : [
          coral_test_utils,
          gbenchmark,
          glog,
          dl,
        ],
      )
    )
  endforeach

  benchmark(
    'coral_posenet_models_benchmark',
    executable(
      'coral_posenet_models_benchmark',
      dependencies : posenet_model_benchmark_deps + [
        coral_benchmark_main_with_edgetpu,
        coral_test_data_posenet_models,
        dl,
      ],
    ),
    suite : ['cpu', 'edgetpu'],
  )
endif

coral_posenet_decoder_lib = declare_dependency(
  link_with : library(
    'posenet_decoder',
    'posenet_decoder_tflite_plugin.cc',
    dependencies : [
      coral_posenet_posenet_decoder_op,
      tensorflow_lite,
    ],
    install : true,
    implicit_include_directories : false,
  ),
)
