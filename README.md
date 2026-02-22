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

### Build Steps

``` bash
mkdir build
cd build
cmake ..
make
./slr_parser
```
