#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>

int getArgs(int argc, char* argv[], char* inFileName, char* key, char* outFileName);
int encDecFile(char* inFileName, char* key, char* outFileName);
void helpMsg();