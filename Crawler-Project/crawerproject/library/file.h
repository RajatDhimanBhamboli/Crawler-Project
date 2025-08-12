#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <ctime>
#include "strings.h"


bool checkdirectory(char* path);
void createdirectory(char* path);
char* longnumbertostring(long long time);
char* generateUniqueName();
char* downloadfile(char* url, char* directorypath);
char* readfile(char* filepath);

#endif