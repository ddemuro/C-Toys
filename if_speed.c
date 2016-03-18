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
#include <math.h>
#include <time.h>
#include <sys/time.h>
using namespace std;

////////////////////////////////// Additional functions
 int wasteTime(int limit){
     int a = 0;
     for(;a <= 2000;a++){
         if(limit != 0 && limit >= a)
             return a;
     }
     return a;
 }
 
 // Get overall time
 double get_wall_time(){
     struct timeval time;
     if (gettimeofday(&time,NULL)){
         //  Handle error
         return 0;
     }
         return (double)time.tv_sec + (double)time.tv_usec * .000001;
 }
 
 // Get cpu time
 double get_cpu_time(){
     return (double)clock() / CLOCKS_PER_SEC;
 }

 
 // Add here a compute operation you want to test
 // Exactly the one you expect to be faster
 void wasteTimeFaster() {
    //  Perform some computation.
    if(wasteTime(0) < 8);
    if (wasteTime(20) > 10);
 }
 
 // Add here a compute operation you want to test
 // Exactly the one you expect to be faster
 void wasteTimeSlower() {
     //  Perform some computation.
     if(wasteTime(0) < 8 && wasteTime(20) > 10);
 }
 
 // This code is argued to be slower
 double testSlower(bool showTime){
     if(showTime)
         printf("This method is argued to be slower");
     //  Start Timers
     double wall0 = get_wall_time();
     double cpu0  = get_cpu_time();
     wasteTimeSlower();
     // Stop timers
     double wall1 = get_wall_time();
     double cpu1  = get_cpu_time();
     if(showTime){
         cout << "Wall Time = " << wall1 - wall0 << endl;
         cout << "CPU Time  = " << cpu1  - cpu0  << endl;
     }
     return cpu1 - cpu0;
 }
 
 // This code is argued to be faster 
 double testFaster(bool showTime){
     if(showTime)
         printf("This method is argued to be faster");
     //  Start Timers
     double wall0 = get_wall_time();
     double cpu0  = get_cpu_time();
     wasteTimeFaster();
     // Stop timers
     double wall1 = get_wall_time();
     double cpu1  = get_cpu_time();
     if(showTime){
         cout << "Wall Time = " << wall1 - wall0 << endl;
         cout << "CPU Time  = " << cpu1  - cpu0  << endl;
     }
     return cpu1 - cpu0;
}

 // Common silly Hello world in main :).
 int main() {
     printf("Hello, world!\n");
     printf("We've created this simple app to test what's faster C... \n");
     printf("In this case, one if? or two ifs?... \n");
     
     double faster = testFaster(true);
     double slower = testSlower(true);
     
     if(faster == slower)
         printf("No difference what so ever!\n");
     
     if(faster > slower)
         printf("testFaster is slower than testSlower...!\n");
     
     if(faster < slower)
         printf("testSlower was faster than testFaster...!\n");
     
     // To check the results we wait for a keystroke...
     getchar();
     
     // Lets make some runs
     printf("To be fair, let's make some runs, average them, and get a global result \n");
     int timesSlowerWasFaster = 0;
     int timesFasterWasSlower = 0;
     int tie = 0;
     int runs = 100;
     
     faster = testFaster(false);
     slower = testSlower(false);
     for(int i = 0;i <= runs; i++){
         printf("%d ",i);
         if(faster == slower)
             tie++;
         if(faster > slower)
             timesSlowerWasFaster++;
         if(faster < slower)
             timesFasterWasSlower++;
     }
     
    printf("\n And the final result is...\n");
    printf("\n.........................................\n");
    if(tie == runs || timesFasterWasSlower == timesSlowerWasFaster)
        printf("No difference what so ever!, ties: %d\n", tie);
    if(timesFasterWasSlower > timesSlowerWasFaster)
        printf("testFaster is slower than testSlower...!\n");
    if(timesFasterWasSlower < timesSlowerWasFaster)
        printf("testSlower was faster than testFaster...!\n");
    printf(".........................................\n");
    //Last stop.
    getchar();
    return 0;
 }
