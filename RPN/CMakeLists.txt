# CMakeList.txt: projekt CMake dla elementu RPN, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#

# Dodaj źródło do pliku wykonywalnego tego projektu.
if (MSVC)
    add_compile_options(/utf-8)
endif()
add_library (rpnlib  "command.cpp" "operator.cpp" "rpn.cpp" "token.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET rpnlib PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(rpnlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
