/* 
 * ============================================================================
 * Name        : Extended_Multiplication.c
 * Author      : Meninx
 * Version     : 1.0
 * Copyright   : Copyright 2017. You can use this code however and wherever you want no strings attached
 * Description : C Function to Perform High Precision Multiplication for Numbers with at most MAX_DIG_NB Digits O(n^2)
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Maximum Nb of Digits for Numbers to multiply */

#define MAX_DIG_NB 10000
#define MAX_DIG_RESULT MAX_DIG_NB*2

/* 
 * 
 * Printing the content of char array in reverse
 * 
 */

void print_array(char* array, int size)
{
	for(int l=size ;l>0;--l )
	{
		printf("%d",(int)result[l]);
	}
	printf("%d\n",(int)result[0]);
}

/* 
 * 
 * High precision multiplication using usual knonwn calculation
 * Numbers x,y can have at most MAX_DIG_NB digits
 * 
 */

void usual_multiplication(char* x, char* y, char* result)
{
	int sizex=strlen(x);
	int sizey=strlen(y);
	int sizer=sizex+sizey;
	int count=0;

	/* This is a the case if one of number is zero */

	if((sizex==1 && x[0]==48) || (sizey==1 && y[0]==48))
	{
		printf("0\n");
		return;
	}

	/* Multiplication loop */

	for(int i=sizex-1;i>-1;--i)
	{
		for(int j=sizey-1;j>-1;--j)
		{
			result[count+sizey-1-j]+=(y[j]-48)*(x[i]-48);
		}
		++count;
	}

	/* Addition after Muliplication */

	count=sizer-1;
	for(int l=0;l<sizer-1;++l)
	{
		result[l+1]+=result[l]/10;
		result[l]%=10;
		if(result[count]==0)
			--count;
	}

	/* Printing result */

	print_array(result,count);
}

int main(void)
{
	char* x=(char*) calloc(MAX_DIG_NB+1, sizeof(char));
	char* y=(char*) calloc(MAX_DIG_NB+1, sizeof(char));
	char* result=(char*) calloc(MAX_DIG_NB+1, sizeof(char));

	/* Reading Input x and y */

	printf("Please enter two digits for multiplication: ");
	scanf("%s %s",x,y);

	usual_multiplication(x,y,result);

	free(x);
	free(y);
	free(result);

	return 0;
}

