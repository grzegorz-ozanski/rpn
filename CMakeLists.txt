# CMakeList.txt: plik projektu CMake najwyższego poziomu, wykonaj konfigurację globalną
# i uwzględnij podprojekty w tym miejscu.
#
cmake_minimum_required (VERSION 3.8)

# Włącz przeładowywanie kodu XAML na gorąco dla kompilatorów MSVC, jeśli jest to obsługiwane.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
project ("RPN")
# Dodaj GoogleTest przez FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# Zapobiega instalacji GoogleTest jako systemowej biblioteki
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Uwzględnij podprojekty.
add_executable(RPN main.cpp)
target_link_libraries(RPN PRIVATE rpnlib)

add_subdirectory ("RPN")
# Testy (DEKLARUJEMY JE TUTAJ)
add_executable(test_rpn tests/tests_rpn.cpp)
target_link_libraries(test_rpn PRIVATE gtest_main rpnlib)

# Najważniejsze dla Test Explorer:
include(GoogleTest)
gtest_discover_tests(test_rpn)
