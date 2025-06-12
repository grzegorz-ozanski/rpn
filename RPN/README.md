# RPN Calculator (C++)

A minimal reverse polish notation (RPN) calculator written in modern C++.

## Features

- Basic arithmetic: `+`, `-`, `*`, `/`
- Error handling (invalid input, division by zero)
- Interactive REPL loop

## Build

```bash
g++ -std=c++17 -o rpn rpn.cpp
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
