if (MSVC)
    add_compile_options(/utf-8)
endif()
include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

add_executable(rpn_tests test_rpn.cpp)

target_link_libraries(rpn_tests PRIVATE Catch2::Catch2WithMain rpnlib)
target_include_directories(rpn_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../rpn)

include(CTest)
include(Catch)
catch_discover_tests(rpn_tests)
