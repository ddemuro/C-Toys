/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org>

--> Derek Demuro 2016 LOL
*/

#include <stdio.h>
#include <iostream>
using namespace std;

 // To wrap an int for memory testing
 struct intWrapper {
     int i;
 };
 ///////////////////////////////// Parameters
 int addOneCounter = 0;
 intWrapper *wrapme;

////////////////////////////////// Additional functions
 // Returns addOneCounter + 1
 int addOne(){
     return addOneCounter += 1;
 }

 // Common silly Hello world in main :).
 int main() {
     printf("Hello, world!\n");
     printf("We've created this simple app to test short - circuit within C \n");
     printf("yes, silly project, but came to a discussion with a friend... so the results. \n");
     printf("\t Hypothsis: We'll evaluate the first operand in if, then add && if that fails \n");
     printf("\t the rest of the code will not run. Meaning it'll suffice to exit the if operation. \n");
     printf("\t\t Tesis: As expected, short-circuit happened, the other statements didn't happen... clearly. \n");
     printf("This is a simple test, man vs machine!\n");
     printf("addOneCounter: %d, wrapme: %d \n",addOneCounter, wrapme);

     // We check what happens now, does a++ get evaluated?
     printf("addOne is not expected to evaluate now... and! \n");
     if(int a = addOne() && a++)
         printf("addOneCounter: %d, did increment! whoo \n",addOneCounter);
     else
         printf("addOneCounter: %d... did not increment\n",addOneCounter);

     // wrapme is undefined still... should blow up by the second condition
     printf("Wrapme is not expected to evaluate now... and! \n");
     if(wrapme != NULL && wrapme->i == 8)
         printf("Wrapme did evaluate: %d \n", wrapme);
     else
         printf("Wrapme did not evaluate: %d \n", wrapme);

     // wrapme is defined now...
     wrapme = new intWrapper;
     wrapme->i = 8;
     printf("Wrapme is expected to evaluate now... and! \n");
     if(wrapme != NULL && wrapme->i == 8)
         printf("Wrapme did evaluate: %d \n", wrapme);
     else
         printf("Wrapme did not evaluate: %d \n", wrapme);
     delete wrapme;

     printf("A should be zero... but second statement is increment... so...! \n");
     int a = 0;
     if(a && a++);
     printf("a value: %d",a);

     printf("\n As we've seen... if conditions are short-circuit, at the first that doesn't return true in && statements, we exit. \n");
     // To check the results we wait for a keystroke...
     getchar();

     return 0;
 }
