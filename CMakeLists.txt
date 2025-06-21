# CMakeList.txt: global project configuration file
#
cmake_minimum_required (VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Turn onn hot reloading of XAML code for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
project ("RPN")

enable_testing()

# Include subprojects
add_executable(rpn main.cpp)
target_link_libraries(rpn PRIVATE rpnlib)
add_subdirectory ("rpnlib")

enable_testing()
add_subdirectory(tests)
