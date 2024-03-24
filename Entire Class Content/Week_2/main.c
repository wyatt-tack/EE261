#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
int main(int argc, char** argv)
	{
	float a = 1.2;
	int b  = a; //Will the compiler throw an error for this?
	//int b = (int)a+1; //try with and without the addition
	printf("Value of a is %f\n", a);
	printf("Value of b is %d\n",b);
	printf("\n\n");



    int a_2 = 16;
	printf("Size of variable a       : %d\n",sizeof(a_2));
	printf("Size of int data type    : %d\n",sizeof(int));
	printf("Size of char data type   : %d\n",sizeof(char));
	printf("Size of long data type   : %d\n",sizeof(long));
	printf("Size of float data type  : %d\n",sizeof(float));
	printf("Size of double data type : %d\n",sizeof(double));


	printf("\n\n");

	    printf("CHAR_BIT    :   %d\n",	CHAR_BIT);
    printf("CHAR_MAX    :   %d\n",	CHAR_MAX);
    printf("CHAR_MIN    :   %d\n",	CHAR_MIN);
    printf("INT_MAX     :   %d\n",	INT_MAX);
    printf("INT_MIN     :   %d\n",	INT_MIN);
    printf("LONG_MAX    :   %ld\n", (long) LONG_MAX);
    printf("LONG_MIN    :   %ld\n", (long) LONG_MIN);
    printf("SCHAR_MAX   :   %d\n",	SCHAR_MAX);
    printf("SCHAR_MIN   :   %d\n",	SCHAR_MIN);
    printf("SHRT_MAX    :   %d\n",	SHRT_MAX);
    printf("SHRT_MIN    :   %d\n",	SHRT_MIN);
    printf("UCHAR_MAX   :   %d\n",	UCHAR_MAX);
    printf("UINT_MAX    :   %u\n",	(unsigned int)   UINT_MAX);
    printf("ULONG_MAX   :   %lu\n",	(unsigned long)  ULONG_MAX);
    printf("USHRT_MAX   :   %d\n",	(unsigned short) USHRT_MAX);

	return 0;
	}
