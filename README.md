# RPN Calculator (C++)

A simple Reverse Polish Notation (RPN) calculator written in modern C++.

## Features

- Basic arithmetic: `+`, `-`, `*`, `/`, 'neg' (negation), 'abs' (absolute value)
- Complex operators '^', '**' (power), 'ln' (natural logarithm), 'log' (base 10 logarithm), 'logn' (logarithm base n)
- Error handling (invalid input, division by zero)
- Interactive REPL loop

## Build

This project uses [CMake](https://cmake.org/) as a build system. To build the project, follow these steps:

```bash
# 1. Create a build directory
mkdir build
cd build

# 2. Generate build files using CMake
cmake ..

# 3. Build the project
cmake --build .
```

## Usage

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
