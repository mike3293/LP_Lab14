#pragma once
#include "stdafx.h"

#define MAX_WORDS 1000
#define WORD_SIZE 20

void clearSpace(unsigned char source[], int size);
unsigned char** divideText(unsigned char source[], int size);