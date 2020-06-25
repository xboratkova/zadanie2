#include <stdio.h>
#include <stdlib.h>

typedef struct{
	unsigned int rows;
	unsigned int cols;
	float *elem;
}MAT;

#define ELEM(A,r,c) (A.elem[(A.cols)*r+c])


