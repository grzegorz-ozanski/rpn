# RPN Calculator (C++)

![CI](https://github.com/grzegorz-ozanski/rpn/actions/workflows/cmake-multi-platform.yml/badge.svg)
[![Coverage](https://grzegorz-ozanski.github.io/rpn/coverage/badge_linecoverage.svg)](https://grzegorz-ozanski.github.io/rpn/coverage/)
[![Unit tests](https://img.shields.io/badge/Unit%20tests-Passed%3A???%20Failed%3A???-red)](https://github.com/grzegorz-ozanski/rpn/actions/runs/1)

A simple Reverse Polish Notation (RPN) calculator written in modern C++.

## ✨ Features

- Basic arithmetic: `+`, `-`, `*`, `/`, 'neg' (negation), 'abs' (absolute value)
- Complex operators '^', '**' (power), 'ln' (natural logarithm), 'log' (base 10 logarithm), 'logn' (logarithm base n)
- Error handling (invalid input, division by zero)
- Interactive REPL loop

## 🖥️ Requirements
- C++20 compatible compiler (e.g., GCC, Clang, MSVC); C++17 compatible version is on the way! ;)
- [CMake](https://cmake.org/) 3.16 or higher

## 📦 Build

To build the project, follow these steps:

```bash
# 1. Create a build directory
mkdir build
cd build

# 2. Generate build files using CMake
cmake ..

# 3. Build the project
cmake --build .
```

## 🚀 Usage

1. Navigate to the build directory where the executable is located.
```
cd build
```
2. Run the RPN calculator executable:
```bash
./rpn
```

Example:

```text
> 3 4 +
Result: 7

> 10 2 8 * + 3 -
Result: 23

> 4 0 /
Error: Division by zero
```
Type `exit` to quit.

## 🧪 Testing
1. Navigate to the build directory where tests executable is located.
```
cd build/tests
```
2. Run the RPN calculator executable:
```bash
./rpn_tests_
```

## 🔍 Project Structure
```
RPN/
├── rpnlib/               # Core RPN library source code
│   ├── CMakeLists.txt
│   ├── CMakeSettings.json
│   ├── command.cpp       # Command handling implementation
│   ├── command.hpp       # Command handling interface
│   ├── constant.hpp      # Constants used in calculations
│   ├── entry.hpp         # Base classes for entries (i.e command, operator and constant) infos and registries (collections of all valid entries) 
│   ├── operator.cpp      # Operator handling implementation
│   ├── operator.hpp	  # Operator handling interface
│   ├── rpn.cpp 		  # Main REPL loop
│   ├── rpn.hpp			  # RPN library interface
│   ├── token.cpp         # Token parsing and handling implementation
│   ├── token.hpp		  # Token parsing and handling interface
│   └── utf_console.hpp   # UTF-8 console output handling (Windows-specific)
├── tests/                # Unit tests (see repo for contents)
├── main.cpp              # Main CLI application entry point
├── CMakeLists.txt        # Project build configuration
├── LICENSE.txt           # Poject license
└── README.md             # This file
```
## 🚧 Planned Improvements
* Compatibility with older C++ standards, like C++17
* Add unit tests and test coverage to CI
* Add more complex operators like `sqrt`, `sin`, `cos`, `tan`, etc.

## 🙋 Author

Created by **Grzegorz Ożański**  
with a bit of ChatGPT support for formatting and polish ;)

## 📄 License

MIT License
