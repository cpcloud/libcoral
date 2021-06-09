HEADERS = [
  'layers.h',
  'softmax_regression_model.h',
  'multi_variate_normal_distribution.h',
]
install_headers(HEADERS, subdir : 'coral/learn/backprop')

coral_learn_backprop_layers = declare_dependency(
  sources : [
    'layers.cc',
    'layers.h',
  ],
  dependencies : [
    eigen3,
  ],
)

coral_learn_backprop_multi_variate_normal_distribution = declare_dependency(
  sources : [
    'multi_variate_normal_distribution.cc',
    'multi_variate_normal_distribution.h',
  ],
  dependencies : [
    eigen3,
    glog,
  ],
  include_directories : include_directories('../../..'),
)

coral_learn_backprop_softmax_regression_model = declare_dependency(
  sources : [
    'softmax_regression_model.cc',
    'softmax_regression_model.h',
  ],
  dependencies : [
    coral_learn_backprop_layers,
    coral_learn_backprop_multi_variate_normal_distribution,
    coral_error_reporter,
    coral_learn_utils,
    absl_status,
    eigen3,
    glog,
    tensorflow_lite,
  ],
)

if build_tests
  coral_learn_backprop_test_utils = declare_dependency(
    sources : [
      'test_utils.cc',
      'test_utils.h',
    ],
    dependencies : [
      coral_learn_backprop_multi_variate_normal_distribution,
      coral_learn_backprop_softmax_regression_model,
      eigen3,
      glog,
    ],
  )

  test(
    'coral_learn_backprop_layers_test',
    executable(
      'coral_learn_backprop_layers_test',
      'layers_test.cc',
      dependencies : [
        coral_learn_backprop_layers,
        coral_learn_backprop_test_utils,
        gtest_main,
        tensorflow_lite,
        dl,
      ],
    ),
    suite : 'cpu',
  )

  test(
    'coral_learn_backprop_test_utils_test',
    executable(
      'coral_learn_backprop_test_utils_test',
      'test_utils_test.cc',
      dependencies : [
        coral_learn_backprop_test_utils,
        gtest_main,
        eigen3,
        dl,
      ],
    ),
    suite : 'cpu',
  )

  test(
    'coral_learn_backprop_softmax_regression_model_test',
    executable(
      'coral_learn_backprop_softmax_regression_model_test',
      'softmax_regression_model_test.cc',
      dependencies : [
        coral_learn_backprop_layers,
        coral_learn_backprop_softmax_regression_model,
        coral_learn_backprop_test_utils,
        gtest_main,
        glog,
        dl,
      ],
    ),
    suite : 'cpu',
  )

  test(
    'coral_learn_backprop_multi_variate_normal_distribution_test',
    executable(
      'coral_learn_backprop_multi_variate_normal_distribution_test',
      'multi_variate_normal_distribution_test.cc',
      dependencies : [
        coral_learn_backprop_multi_variate_normal_distribution,
        gtest_main,
        glog,
      ],
    ),
    suite : 'cpu',
  )
endif

if build_benchmarks
  benchmark(
    'coral_learn_backprop_softmax_regression_model_benchmark',
    executable(
      'coral_learn_backprop_softmax_regression_model_benchmark',
      'softmax_regression_model_benchmark.cc',
      dependencies : [
        coral_learn_backprop_layers,
        coral_learn_backprop_softmax_regression_model,
        coral_learn_backprop_test_utils,
        coral_benchmark_main,
        gbenchmark,
        glog,
        dl,
      ],
    ),
    suite: 'cpu',
  )
endif
