install_headers('adapter.h', subdir : 'coral/classification')

if build_tests
  test(
    'coral_classification_adapter_test',
    executable(
      'coral_classification_adapter_test',
      'adapter_test.cc',
      dependencies : [
        coral_classification_adapter,
        coral_test_main,
        gtest,
        glog,
        dl,
        gmock,
      ],
    ),
    suite : 'cpu',
  )

  CLASSIFICATION_MODEL_TEST_CASES = _COCOMPILED_MODEL_TEST_CASES + _INDIVIDUALLY_COMPILED_MODEL_TEST_CASES

  classification_model_test_cases_cpu_deps = []
  classification_model_test_cases_edgetpu_deps = []

  test_deps = [
    coral_test_utils,
    gtest,
    dl,
  ]
  test_src = '../classification_model_test_lib.cc'

  foreach case : CLASSIFICATION_MODEL_TEST_CASES
    model_path = case.get('model_path')
    test_name = model_path.split('.tflite')[0].underscorify()
    cpp_args = [
      '-DARG_EFFECTIVE_MEANS=@0@'.format(case.get('effective_means', '0,0,0')),
      '-DARG_EFFECTIVE_SCALE=@0@'.format(case.get('effective_scale', '1')),
      '-DARG_EXPECTED_TOPK_LABEL=@0@'.format(case.get('expected_topk_label')),
      '-DARG_IMAGE_PATH=@0@'.format(case.get('image_path', 'cat.bmp')),
      '-DARG_K=@0@'.format(case.get('k', '3')),
      '-DARG_MODEL_PATH=@0@'.format(model_path),
      '-DARG_RGB2BGR=@0@'.format(case.get('rgb2bgr', 'false')),
      '-DARG_SCORE_THRESHOLD=@0@'.format(case.get('score_threshold', '0')),
      '-DARG_TEST_NAME=@0@'.format(test_name),
    ]

    if model_path.endswith('_edgetpu.tflite')
      test_suite_name = 'ClassificationModelEdgeTpuTest'
      classification_model_test_cases_edgetpu_deps += declare_dependency(
        link_with : library(
          test_name,
          sources : test_src,
          cpp_args : cpp_args + [
            '-DARG_TEST_SUITE_NAME=@0@'.format(test_suite_name)
          ],
          dependencies : test_deps,
        )
      )
    else
      test_suite_name = 'ClassificationModelCpuTest'
      classification_model_test_cases_cpu_deps += declare_dependency(
        link_with : library(
          test_name,
          sources : test_src,
          cpp_args : cpp_args + [
            '-DARG_TEST_SUITE_NAME=@0@'.format(test_suite_name)
          ],
          dependencies : test_deps,
        )
      )
    endif
  endforeach

  test(
    'coral_classification_models_cpu_test',
    executable(
      'coral_classification_models_cpu_test',
      dependencies : classification_model_test_cases_cpu_deps + [
        coral_test_main,
        coral_test_data_images,
        coral_test_data_models,
        coral_test_data_cocompilation_models,
        dl,
      ],
    ),
    suite : 'cpu',
  )

  test(
    'coral_classification_models_edgetpu_test',
    executable(
      'coral_classification_models_edgetpu_test',
      dependencies : classification_model_test_cases_edgetpu_deps + [
        coral_test_main_with_edgetpu,
        coral_test_data_images,
        coral_test_data_models,
        coral_test_data_cocompilation_models,
        dl,
      ],
    ),
    is_parallel : false,
    suite : 'edgetpu',
  )
endif
