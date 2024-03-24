#include<stdio.h>
int main1()
	{
	float a = 1.2;
	//int b  = a; //Will the compiler throw an error for this?
	int b = (int)a+1; //try with and without the addition
	printf("Value of a is %f\n", a);
	printf("Value of b is %d\n",b);
	return 0;
	}
