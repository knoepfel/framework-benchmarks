cmake_minimum_required(VERSION 3.18.2 FATAL_ERROR)

find_package(cetmodules 2.13.00 REQUIRED)
project(framework-benchmarks VERSION 0.01.00 LANGUAGES CXX C)

include(CetCMakeEnv)
cet_cmake_env()

cet_set_compiler_flags(DIAGS VIGILANT WERROR NO_UNDEFINED EXTRA_FLAGS -pedantic)
cet_report_compiler_flags(REPORT_THRESHOLD VERBOSE)

cet_enable_asserts()
add_subdirectory(plugins)

# Make sure tests have correct environment settings.
include(CetTest)

add_subdirectory(benchmark-01)
add_subdirectory(benchmark-02)
add_subdirectory(benchmark-03)
add_subdirectory(benchmark-06)
