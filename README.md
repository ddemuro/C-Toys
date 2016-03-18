# C-Toys
C++ Toys, testing bizarre things we can do with the compiler.

## Short Circuit
After a discussion with a friend who's also a developer... he argued that && inside if statements would evaluate
even when one of them already failed.
My argument was that at the first condition that evaluated false, the if statement would fail.
So I created a simple test application to test such conditions.
_Precedence is important!_

## Speed Test
*If test*:

What's faster? using one if? or more than one if?... Check the results after compiling!.
_one if... I swear lol!_


_How to compile:_
g++ short-circuit.c

_How to run:_
./a.out

## Suggest tests
mail@derekdemuro.com
