project(
  'libcoral',
  'cpp',
  version : '1.0.0',
  default_options : [
    'cpp_std=c++11',
  ],
)

add_project_arguments(
  [
    '-Wno-sign-compare',
  ],
  language : 'cpp',
)

cxx = meson.get_compiler('cpp')

absl_algorithm_container = dependency('absl_algorithm_container')
absl_base = dependency('absl_base')
absl_flags = dependency('absl_flags')
absl_flags_parse = dependency('absl_flags_parse')
absl_flat_hash_set = dependency('absl_flat_hash_set')
absl_flat_hash_map = dependency('absl_flat_hash_map')
absl_memory = dependency('absl_memory')
absl_node_hash_map = dependency('absl_node_hash_map')
absl_optional = dependency('absl_optional')
absl_status = dependency('absl_status')
absl_strings = dependency('absl_strings')
absl_span = dependency('absl_span')
absl_time = dependency('absl_time')
absl_synchronization = dependency('absl_synchronization')

build_benchmarks = get_option('benchmarks').enabled()

test_suites = get_option('tests')

build_tests = test_suites.length() != 0
build_cpu_tests = test_suites.contains('cpu')
build_dmabuf_tests = test_suites.contains('dmabuf')
build_edgetpu_tests = test_suites.contains('edgetpu')
build_pipeline_tests = test_suites.contains('pipeline')
build_stress_tests = test_suites.contains('stress')

build_examples = get_option('examples').enabled()

dl = cxx.find_library('dl')

edgetpu = dependency('edgetpu')

eigen3 = dependency('eigen3')

flatbuffers = dependency('flatbuffers')

# gstreamer is only required if building dmabuf tests
# it isn't used in anything core to the functionality of libcoral
gstallocators = dependency('gstreamer-allocators-1.0', required : build_dmabuf_tests)
gstreamer = dependency('gstreamer-1.0', required : build_dmabuf_tests)

# gbenchmark is a transitiv dependency of some of the test suites
gbenchmark = dependency('benchmark', required : build_benchmarks or build_tests)

glog = dependency('glog')
gmock = dependency('gmock', required : build_tests)
gtest = dependency('gtest', required : build_tests)
gtest_main = dependency('gtest_main', required : build_tests)

pkgconfig = import('pkgconfig')

tensorflow_lite = dependency('tensorflow-lite')

if build_tests or build_benchmarks
  subdir('test_data')
endif

subdir('coral')
