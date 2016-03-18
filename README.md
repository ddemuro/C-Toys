# C-Toys
C++ Toys, testing bizarre things we can do with the compiler.

## Short Circuit
After a discussion with a friend who's also a developer... he argued that && inside if statements would evaluate
even when one of them already failed.
My argument was that at the first condition that evaluated false, the if statement would fail.
So I created a simple test application to test such conditions.

_How to compile:_
g++ short-circuit.c
_How to run:_
./a.out

## Suggest tests
mail@derekdemuro.com
