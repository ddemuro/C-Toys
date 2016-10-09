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

#include <cstdlib>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <libgen.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/xattr.h>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

////////////////////////////////// Additional functions
bool BINARY = false;
int BUFFERSIZE = 512;
int FIRSTFILE = -1;
int LASTFILE = -1;
bool PRINTDIFFS = false;
unsigned long long FSIZE = 0;
unsigned long long LSIZE = 0;


 void compare(){
	cout << "Starting compare between both files. Differing offsets will be printed as a list" << endl;
	cout << "Buffer size:" << BUFFERSIZE << endl;
	// Keep track where i've read.
	unsigned long long firstFileTrack = 0;
	unsigned long long secondFileTrack = 0;
	// File 1 and 2 buffer
	char *compbuffer1 = new char[BUFFERSIZE];
	char *compbuffer2 = new char[BUFFERSIZE];
	int rest = -22;
	// Read files
	while(firstFileTrack < FSIZE && secondFileTrack < LSIZE){
		firstFileTrack += pread64(FIRSTFILE, compbuffer1, BUFFERSIZE, firstFileTrack);
		secondFileTrack += pread64(LASTFILE, compbuffer2, BUFFERSIZE, secondFileTrack);
		rest = memcmp(compbuffer1, compbuffer2, BUFFERSIZE);
		if(rest != 0){
			cout << "Offset: " << firstFileTrack << endl;
			if(PRINTDIFFS){
				cout << "" << endl;
				printf("%s", compbuffer1);
				cout << "\n==========================" << endl;
				printf("%s", compbuffer2);
				cout << "" << endl;
			}
		}
		// Reset
		memset(compbuffer1, 0, BUFFERSIZE);
		memset(compbuffer2, 0, BUFFERSIZE);
	}
	// Cleanup
	cout << "Cleaning up" << endl;
	delete(compbuffer1);
	delete(compbuffer2);
	close(FIRSTFILE);
	close(LASTFILE);
 }

 void usage(){
	cout << "Parameters -B for binary, -f [path for file 1] , -l [path to last file], -b [buffer size in INT size 512 default]" << endl;
 }
 // Common silly Hello world in main :).
 int main(int argc, char *argv[]) {
     printf("Hello, world!\n");
    //Fuse status
    int opt;
    int argc_fuse = 3;
	if(argc_fuse <= argc){
		cout << "Eror, not enough args" << endl;
	}
    while ((opt = getopt(argc, argv, "Bf:l:b:o:P:")) != -1) {
        switch (opt) {
            case 'B':
                BINARY = true;
                break;
            case 'P':
                PRINTDIFFS = true;
                break;
            case 'b':
                BUFFERSIZE = atoi(optarg);
                break;
            case 'f':
                // Size of statted dump
                struct stat firstFileSize;
                lstat(optarg, &firstFileSize);
                FSIZE = firstFileSize.st_size;
                FIRSTFILE = open(optarg, O_RDWR, O_DIRECT);
                if (FIRSTFILE == -1) {
                    perror("First file was not opened, error.");
                    exit(-1);
                }
                break;
            case 'l':
                // Size of statted dump
                struct stat lastFileSize;
                lstat(optarg, &lastFileSize);
                LSIZE = lastFileSize.st_size;
                LASTFILE = open(optarg, O_RDWR, O_DIRECT);
                if (LASTFILE == -1) {
                    perror("Last file was not opened, error.");
                    exit(-1);
                }
                break;
            case ':':
                /* missing option argument */
                fprintf(stderr, "%s: option '-%c' requires an argument\n",
                        argv[0], optopt);
                exit(-2);
                break;
            case '?':
            default:
                usage();
        }
    }
	compare();
	exit(0);
 }
