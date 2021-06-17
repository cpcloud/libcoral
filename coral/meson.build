HEADERS = [
  'error_reporter.h',
  'bbox.h',
  'tflite_utils.h',
]

install_headers(HEADERS, subdir : 'coral')

coral_error_reporter = declare_dependency(
  sources : [
    'error_reporter.cc',
    'error_reporter.h',
  ],
  dependencies : [
    tensorflow_lite,
  ],
  include_directories : include_directories('..'),
)

if build_tests
  coral_test_main = declare_dependency(
    sources : [
      'test_main.cc',
    ],
    dependencies : [
      absl_flags_parse,
      gtest,
    ],
  )

  coral_test_main_with_edgetpu = declare_dependency(
    dependencies : [
      coral_test_main,
      edgetpu,
    ]
  )
endif

coral_bbox = declare_dependency(
  sources : 'bbox.h',
  dependencies : [
    absl_strings,
    glog,
  ],
  include_directories : include_directories('..'),
)

coral_posenet_posenet_decoder = declare_dependency(
  sources : [
    'posenet/posenet_decoder.cc',
    'posenet/posenet_decoder.h',
  ],
  include_directories : include_directories('..'),
)

coral_posenet_posenet_decoder_op = declare_dependency(
  sources : [
    'posenet/posenet_decoder_op.cc',
    'posenet/posenet_decoder_op.h',
  ],
  dependencies : [
    coral_posenet_posenet_decoder,
    flatbuffers,
    tensorflow_lite,
  ],
)

coral_tflite_utils = declare_dependency(
  sources : [
    'tflite_utils.cc',
    'tflite_utils.h',
  ],
  dependencies : [
    absl_optional,
    absl_span,
    absl_status,
    absl_strings,
    coral_posenet_posenet_decoder_op,
    flatbuffers,
    glog,
    edgetpu,
    tensorflow_lite,
  ],
)

coral_classification_adapter = declare_dependency(
  sources : [
    'classification/adapter.cc',
    'classification/adapter.h',
  ],
  dependencies : [
    coral_tflite_utils,
    absl_strings,
    absl_span,
    glog,
    tensorflow_lite,
  ],
)

coral_detection_adapter = declare_dependency(
  sources : [
    'detection/adapter.cc',
    'detection/adapter.h',
  ],
  dependencies : [
    coral_bbox,
    coral_tflite_utils,
    absl_strings,
    absl_span,
    glog,
    tensorflow_lite,
  ],
)

if build_tests or build_benchmarks
  coral_test_utils = declare_dependency(
    sources : [
      'test_utils.cc',
      'test_utils.h',
    ],
    dependencies : [
      coral_bbox,
      coral_tflite_utils,
      coral_classification_adapter,
      coral_detection_adapter,
      gbenchmark,
      absl_flags,
      absl_span,
      absl_strings,
      gtest,
      glog,
      tensorflow_lite,
    ],
  )
endif

if build_benchmarks
  coral_benchmark_main = declare_dependency(
    sources : 'benchmark_main.cc',
    dependencies : [
      gbenchmark,
      absl_flags_parse,
    ],
  )

  coral_benchmark_main_with_edgetpu = declare_dependency(
    dependencies : [
      coral_benchmark_main,
      edgetpu,
    ],
  )
  benchmark(
    'coral_cocompiled_models_benchmark',
    executable(
      'coral_cocompiled_models_benchmark',
      'cocompiled_models_benchmark.cc',
      dependencies : [
        coral_test_data_cocompilation_models,
        coral_benchmark_main_with_edgetpu,
        coral_test_utils,
        gbenchmark,
        dl,
      ],
    ),
    timeout : 0,
    suite : 'edgetpu',
  )
endif

if build_edgetpu_tests
  test(
    'coral_segmentation_models_test',
    executable(
      'coral_segmentation_models_test',
      'segmentation_models_test.cc',
      dependencies : [
        coral_test_data_images,
        coral_test_data_models,
        coral_test_main_with_edgetpu,
        coral_test_utils,
        coral_tflite_utils,
        absl_flags_parse,
        gtest,
        glog,
        dl,
      ],
    ),
    timeout : 0,
    is_parallel : false,
    suite : 'edgetpu',
  )

  test(
    'coral_test_utils_test',
    executable(
      'coral_test_utils_test',
      'test_utils_test.cc',
      dependencies : [
        coral_test_data_images,
        coral_test_main_with_edgetpu,
        coral_test_utils,
        coral_classification_adapter,
        absl_strings,
        gtest,
        dl,
      ],
    ),
    is_parallel : false,
    suite : 'edgetpu',
  )

  test(
    'coral_inference_repeatability_test',
    executable(
      'coral_inference_repeatability_test',
      'inference_repeatability_test.cc',
      dependencies : [
        coral_test_data_models,
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
    timeout : 0,
    is_parallel : false,
    suite : 'edgetpu',
  )
endif

if build_cpu_tests
  test(
    'coral_error_reporter_test',
    executable(
      'coral_error_reporter_test',
      'error_reporter_test.cc',
      dependencies : [
        coral_error_reporter,
        absl_memory,
        gtest_main
      ]
    ),
    suite : 'cpu',
  )

  test(
    'coral_bbox_test',
    executable(
      'coral_bbox_test',
      'bbox_test.cc',
      dependencies : [
        coral_bbox,
        gtest_main,
      ],
    ),
    suite : 'cpu',
  )
endif

if build_stress_tests
  test(
    'coral_model_loading_stress_test',
    executable(
      'coral_model_loading_stress_test',
      'model_loading_stress_test.cc',
      dependencies : [
        coral_test_main_with_edgetpu,
        coral_test_utils,
        coral_tflite_utils,
        absl_flags,
        absl_flags_parse,
        gtest,
        glog,
        dl,
      ]
    ),
    timeout : 0,
    is_parallel : false,
    suite : 'stress',
  )

  test(
    'coral_inference_stress_test',
    executable(
      'coral_inference_stress_test',
      'inference_stress_test.cc',
      dependencies : [
        coral_test_data_models,
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
    timeout : 0,
    is_parallel : false,
    suite : 'stress',
  )

  test(
    'coral_multiple_tpus_inference_stress_test',
    executable(
      'coral_multiple_tpus_inference_stress_test',
      'multiple_tpus_inference_stress_test.cc',
      dependencies : [
        coral_test_data_images,
        coral_test_data_models,
        coral_test_main_with_edgetpu,
        coral_test_utils,
        coral_tflite_utils,
        absl_flags,
        absl_flags_parse,
        absl_status,
        absl_span,
        gtest,
        glog,
        dl,
      ],
    ),
    timeout : 0,
    is_parallel : false,
    suite : 'stress',
  )
endif

if build_benchmarks
  MODEL_BENCHMARK_CASES = [
      {
          'benchmark_name': 'BM_MobileNetV1',
          'model_path': 'mobilenet_v1_1.0_224_quant',
      },
      {
          'benchmark_name': 'BM_MobileNetV1_25',
          'model_path': 'mobilenet_v1_0.25_128_quant',
      },
      {
          'benchmark_name': 'BM_MobileNetV1_50',
          'model_path': 'mobilenet_v1_0.5_160_quant',
      },
      {
          'benchmark_name': 'BM_MobileNetV1_75',
          'model_path': 'mobilenet_v1_0.75_192_quant',
      },
      {
          'benchmark_name': 'BM_MobileNetV1_L2Norm',
          'model_path': 'mobilenet_v1_1.0_224_l2norm_quant',
      },
      {
          'benchmark_name': 'BM_MobileNetV2',
          'model_path': 'mobilenet_v2_1.0_224_quant',
      },
      {
          'benchmark_name': 'BM_MobileNetV2INatPlant',
          'model_path': 'mobilenet_v2_1.0_224_inat_plant_quant',
      },
      {
          'benchmark_name': 'BM_MobileNetV2INatInsect',
          'model_path': 'mobilenet_v2_1.0_224_inat_insect_quant',
      },
      {
          'benchmark_name': 'BM_MobileNetV2INatBird',
          'model_path': 'mobilenet_v2_1.0_224_inat_bird_quant',
      },
      {
          'benchmark_name': 'BM_SsdMobileNetV1',
          'model_path': 'ssd_mobilenet_v1_coco_quant_postprocess',
      },
      {
          'benchmark_name': 'BM_SsdMobileNetV2',
          'model_path': 'ssd_mobilenet_v2_coco_quant_postprocess',
      },
      {
          'benchmark_name': 'BM_FaceSsd',
          'model_path': 'ssd_mobilenet_v2_face_quant_postprocess',
      },
      {
          'benchmark_name': 'BM_InceptionV1',
          'model_path': 'inception_v1_224_quant',
      },
      {
          'benchmark_name': 'BM_InceptionV2',
          'model_path': 'inception_v2_224_quant',
      },
      {
          'benchmark_name': 'BM_InceptionV3',
          'model_path': 'inception_v3_299_quant',
      },
      {
          'benchmark_name': 'BM_InceptionV4',
          'model_path': 'inception_v4_299_quant',
      },
      {
          'benchmark_name': 'BM_EfficientNetEdgeTpuSmall',
          'model_path': 'efficientnet-edgetpu-S_quant',
      },
      {
          'benchmark_name': 'BM_EfficientNetEdgeTpuMedium',
          'model_path': 'efficientnet-edgetpu-M_quant',
      },
      {
          'benchmark_name': 'BM_EfficientNetEdgeTpuLarge',
          'model_path': 'efficientnet-edgetpu-L_quant',
      },
      {
          'benchmark_name': 'BM_Deeplab513Mv2Dm1_WithArgMax',
          'model_path': 'deeplabv3_mnv2_pascal_quant',
      },
      {
          'benchmark_name': 'BM_Deeplab513Mv2Dm05_WithArgMax',
          'model_path': 'deeplabv3_mnv2_dm05_pascal_quant',
      },
      {
          'benchmark_name': 'BM_KerasPostTrainingQuantizedUnetMv2128',
          'model_path': 'keras_post_training_unet_mv2_128_quant',
      },
      {
          'benchmark_name': 'BM_KerasPostTrainingQuantizedUnetMv2256',
          'model_path': 'keras_post_training_unet_mv2_256_quant',
      },
      {
          'benchmark_name': 'BM_SsdMobileNetV1FineTunedPet',
          'model_path': 'ssd_mobilenet_v1_fine_tuned_pet',
      },
      {
          'benchmark_name': 'BM_PostTrainingQuantizedTf2KerasMobileNetV1',
          'model_path': 'tf2_mobilenet_v1_1.0_224_ptq',
      },
      {
          'benchmark_name': 'BM_PostTrainingQuantizedTf2KerasMobileNetV2',
          'model_path': 'tf2_mobilenet_v2_1.0_224_ptq',
      },
      {
          'benchmark_name': 'BM_PostTrainingQuantizedTf2KerasMobileNetV3EdgeTpu',
          'model_path': 'tf2_mobilenet_v3_edgetpu_1.0_224_ptq',
      },
      {
          'benchmark_name': 'BM_SsdLiteMobileDet',
          'model_path': 'ssdlite_mobiledet_coco_qat_postprocess',
      },
      {
          'benchmark_name': 'BM_SsdMobileNetV1_NoNms',
          'model_path': 'ssd_mobilenet_v1_coco_quant_no_nms',
      },
      {
          'benchmark_name': 'BM_SsdMobileNetV2_NoNms',
          'model_path': 'ssd_mobilenet_v2_coco_quant_no_nms',
      },
      {
          'benchmark_name': 'BM_Tf2Resnet50ImagenetPtq',
          'model_path': 'tfhub_tf2_resnet_50_imagenet_ptq',
      },
  ]

  coral_models_benchmark_deps = []

  foreach case : MODEL_BENCHMARK_CASES
    model_path = case.get('model_path')
    benchmark_name = case.get('benchmark_name')
    coral_models_benchmark_deps += declare_dependency(
      link_with : library(
        benchmark_name,
        sources : 'models_benchmark_lib.cc',
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
    'coral_models_benchmark',
    executable(
      'coral_models_benchmark',
      dependencies : coral_models_benchmark_deps + [
        coral_test_data_models,
        coral_benchmark_main_with_edgetpu,
        dl,
      ],
    ),
    timeout : 0,
    suite : ['cpu', 'edgetpu'],
  )
endif

## posenet is here to avoid circular dependencies
HEADERS = [
  'posenet/posenet_decoder_op.h',
  'posenet/posenet_decoder.h',
]

install_headers(HEADERS, subdir : 'coral/posenet')

if build_edgetpu_tests
  coral_posenet_test_utils = declare_dependency(
    sources : [
      'posenet/test_utils.cc',
      'posenet/test_utils.h',
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
      'posenet/bodypix_test.cc',
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
      'posenet/models_test.cc',
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
      'posenet/posenet_decoder_test.cc',
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
        'models_benchmark_lib.cc',
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

coral_posenet_posenet_decoder_op = declare_dependency(
  sources : [
    'posenet/posenet_decoder_op.cc',
    'posenet/posenet_decoder_op.h',
  ],
  dependencies : [
    coral_posenet_posenet_decoder,
    flatbuffers,
    tensorflow_lite,
  ],
)

posenet_decoder_lib = library(
  'posenet_decoder',
  'posenet/posenet_decoder_tflite_plugin.cc',
  dependencies : [
    coral_posenet_posenet_decoder_op,
    tensorflow_lite,
  ],
  install : true,
)

pkgconfig.generate(posenet_decoder_lib)

subdir('classification')
subdir('detection')
subdir('pipeline')
subdir('dmabuf')
subdir('learn')
subdir('tools')
subdir('examples')

coral_lib = library(
  'coral',
  dependencies : [
    coral_tflite_utils,
    coral_classification_adapter,
    coral_detection_adapter,
    coral_examples_file_utils,
    coral_pipeline_utils,
    coral_learn_backprop_softmax_regression_model,
    coral_learn_imprinting_engine,
    dl,
  ],
  install : true,
)

pkgconfig.generate(coral_lib)
