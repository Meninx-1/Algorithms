/* 
 * ============================================================================
 * Name        : Big_Integer_Multiplication.c
 * Author      : Meninx
 * Version     : 1.0
 * Copyright   : Copyright 2017. You can use this code however and wherever you want no strings attached
 * Description : C Function to Perform High Precision Multiplication for Numbers with at most MAX_DIG_NB Digits O(n^2)
 *               The multiplication is restricted only for positive numbers.            
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* MAX_DIG_NB is the maximum Nb of Digits for each number x and y 
* MAX_DIG_NB <= INT_MAX 
*/

#define MAX_DIG_NB 10000
#define MAX_DIG_RESULT MAX_DIG_NB*2

/* 
 * 
 * Printing the content of char array in reverse
 * 
 */

void print_array(char* result, int size)
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
 * Function return the index of last digit in reversed result (index of high-order digit in array)
 * 
 */

int usual_multiplication(char* x, char* y, char* result)
{
	int sizex=strlen(x);
	int sizey=strlen(y);
	int sizer=sizex+sizey;
	int count=0;

	/* This is a the case if one of number is zero */

	if((sizex==1 && x[0]==48) || (sizey==1 && y[0]==48))
	{
		return 0;
	}

	/* Multiplication loop */

	int index;
	for(int i=sizex-1;i>-1;--i)
	{
		for(int j=sizey-1;j>-1;--j)
		{
			index=count+sizey-j-1;
			result[index]+=(y[j]-48)*(x[i]-48);

			/* Move carry to the left - result is in reverse - */

			result[index+1]+=result[index]/10;
			result[index]%=10;
		}
		++count;
	}
	
	/* Index of last digit related to reversed result */
	
	count=count+sizey-1;

	return count;
}

int main(void)
{
	char* x=(char*) calloc(MAX_DIG_NB+1, sizeof(char));
	char* y=(char*) calloc(MAX_DIG_NB+1, sizeof(char));
	char* result=(char*) calloc(MAX_DIG_NB+1, sizeof(char));

	/* Reading Input x and y */

	printf("Please enter two digits for multiplication: ");
	scanf("%s %s",x,y);

	int size_result;
	
	size_result=usual_multiplication(x,y,result);

	/* Printing result */

	print_array(result,size_result);

	free(x);
	free(y);
	free(result);

	return 0;
}

