# CMakeList.txt: projekt CMake dla elementu RPN, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#

# Dodaj źródło do pliku wykonywalnego tego projektu.
if (MSVC)
    add_compile_options(/utf-8)
endif()
add_library (rpnlib  "command.cpp" "operator.cpp" "rpn.cpp" "token.cpp" )

target_include_directories(rpnlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
