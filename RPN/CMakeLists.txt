# CMakeList.txt: projekt CMake dla elementu RPN, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#

# Dodaj źródło do pliku wykonywalnego tego projektu.
if (MSVC)
    add_compile_options(/utf-8)
endif()
add_executable (RPN "RPN.cpp" "RPN.hpp" "operator.cpp" "token.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RPN PROPERTY CXX_STANDARD 20)
endif()

# TODO: Dodaj testy i zainstaluj elementy docelowe w razie potrzeby.
