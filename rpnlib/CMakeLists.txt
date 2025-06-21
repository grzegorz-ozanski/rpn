# CMakeList.txt: configuration file for the rpnlib library
#

if (MSVC)
    add_compile_options(/utf-8)
endif()
add_library (rpnlib  "command.cpp" "operator.cpp" "rpn.cpp" "token.cpp" )

target_include_directories(rpnlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
