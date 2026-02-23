# SLR Parser for Arithmetic Expressions

------------------------------------------------------------------------

## Project Overview

This project implements an **SLR(1) shift-reduce parser** for a simple
arithmetic expression language.

The program:

-   Uses **Flex** for lexical analysis
-   Implements a **manual SLR(1) parser**
-   Visualizes the entire parsing process:
    -   Stack contents
    -   Remaining input buffer
    -   Performed action (Shift / Reduce / Accept)

------------------------------------------------------------------------

## Supported Language

The arithmetic language supports:

-   Addition (`+`)
-   Subtraction (`-`)
-   Multiplication (`*`)
-   Division (`/`)
-   Parentheses (`(` `)`)
-   Variables (Latin letters, upper and lower case)
-   Integer numbers

### Valid Examples

    a + b
    x * (y + 5)
    (3 + 4) * z

------------------------------------------------------------------------
## Grammar

The grammar for the arithmetic language (with precedence and left associativity) is:

    E → E + T | E - T | T
    T → T * F | T / F | F
    F → ( E ) | id | number

Where:
- `E` : expression
- `T` : term
- `F` : factor
- `id` : variable (sequence of Latin letters)
- `number` : integer

------------------------------------------------------------------------

## Example Output

    STACK      INPUT        ACTION
    $          id*id$       Shift
    $id        *id$         Reduce F→id
    $F         *id$         Reduce T→F
    $T         *id$         Shift
    $T*        id$          Shift
    $T*id      $            Reduce F→id
    $T*F       $            Reduce T→T*F
    $T         $            Reduce E→T
    $E         $            Accept

------------------------------------------------------------------------

## Build Instructions

### Requirements

-   C++17
-   CMake ≥ 3.16
-   Flex

Installs essential compilation tools (GCC, make), CMake build system, and Flex lexer generator:

``` bash
sudo apt install build-essential cmake flex 
```

### Build Steps (with make)

Basic Build (without tests):

``` bash
make 
```

Clean Rebuild:

``` bash
make rebuild
```

Build with Tests:

``` bash
make rebuild TESTING=ON
```

### Executing

Run the parser without arguments to enter expressions manually (Ctrl+D to end):

``` bash
build/slr_parser
```

Run the tests:

``` bash
build/slr_tests
```