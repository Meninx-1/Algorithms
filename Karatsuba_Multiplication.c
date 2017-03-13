/* 
 * ============================================================================
 * Name        : Karatsuba_Multiplication.c
 * Author      : Meninx
 * Version     : 1.0
 * Copyright   : Copyright 2017. You can use this code however and wherever you want no strings attached
 * Description : C Function to Perform High Precision Karatsuba mutliplication [O(n^log2(3))] of numbers with at most 16 digits. 
 *               It can also compute numbers with at most 18 digits in condition that the other number
 *               should be at most 8 digits.
 *               The multiplication is restricted only for positive numbers.
 * ============================================================================
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/* When SHOW_PROCESS is set to 1 it will visualize values in each process */
#define SHOW_PROCESS 1

unsigned long long int Pow_10[9]={10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};

/* print the result from variable res */

void print_result(char* res, int sizer)
{
	int j=0;
	if(res[0]==0)
		++j;

	for(;j<=sizer;++j)
		printf("%d",(int)res[j]);

	printf("\n");
}

/* compute how many digits are in number nb */

int Nb_Digits(unsigned long long int nb)
{
	char* str=(char*)calloc(21,sizeof(char));
	sprintf(str,"%llu",nb);
	int count=strlen(str);
	free(str);

	return count;
}

/* 
 *  Compute the final result ac * 10^n + abcd * 10^(n/2) + bd 
 *  and fill the variable res with result
 */

void Compute_and_Fill_Array(unsigned long long int ac, unsigned long long int abcd, unsigned long long int bd,int max, char*res,int sizer) 
{
	int maxdiv2=max/2;

	/* Convert the three components ac, abcd and bd to strings */

	char* strbd=(char*)calloc(21,sizeof(char));
	sprintf(strbd,"%llu",bd);
	int countbd=strlen(strbd);

	char* strac=(char*)calloc(21,sizeof(char));
	sprintf(strac,"%llu",ac);
	int countac=strlen(strac);

	char* strabcd=(char*)calloc(21,sizeof(char));
	sprintf(strabcd,"%llu",abcd);

	int countabcd=strlen(strabcd);

	/* Computing and filling array res */

	for(int j=sizer;j>0;--j)
	{
		if(bd!=0 && countbd>0)
			res[j]+=strbd[--countbd]-48;

		if(abcd!=0 &&  countabcd>0 && j<=sizer-maxdiv2)
			res[j]+=strabcd[--countabcd]-48;

		if(ac!=0 &&  countac>0 && j<=sizer-max)
			res[j]+=strac[--countac]-48;

		res[j-1]+=res[j]/10;
		res[j]=res[j]%10;
	}
	
	free(strac);
	free(strabcd);
	free(strbd);
}

/* 
 * This recursive function is computing the multiplication of two numbers x and y
 * using karatsuba algorithm 
 */

unsigned long long int karatsuba (unsigned long long* x, unsigned long long int* y, char* res, int check)
{

	int sizex=Nb_Digits(*x);
	int sizey=Nb_Digits(*y);

	int max=sizex;

	/* 
	 *  Compute "max" to divide numbers into two equal halves 
	 *
	 *  For better performance set max to 18 
	 */

	if(sizey>max)
		max=sizey;
	if(max%2!=0)
		++max;

#if SHOW_PROCESS
	printf("\n\n(%d) x=%llu y=%llu \n",check,*x,*y);
#endif

	if(sizex+sizey<=18)
	{
		unsigned long long int temp= *x * *y;

#if SHOW_PROCESS
		printf("(%d) res=%llu \n",check,temp);
#endif

		if(check==0)
			Compute_and_Fill_Array(0,0,temp,max,res,sizex+sizey-1);

		return temp;
	}

	/* 
	 *  x=10^(max/2)*a+b
	 *  y=10^(max/2)*c+d
	 */

	unsigned long long int a,b,c,d;
	unsigned long long int ac,bd,abcd;

	int maxdiv2=max/2;

	a = *x/Pow_10[maxdiv2-1];
	b = *x%Pow_10[maxdiv2-1];
	c = *y/Pow_10[maxdiv2-1];
	d = *y%Pow_10[maxdiv2-1];

#if SHOW_PROCESS
	printf("(%d) a=%-8lld b=%-8lld\n    c=%-8lld d=%-8lld\n",check,a,b,c,d);
#endif

	unsigned long long int sum1=a+b;
	unsigned long long int sum2=c+d;

	ac   = karatsuba(&a,&c,res,check+1);
	bd   = karatsuba(&b,&d,res,check+2);
	abcd = karatsuba(&sum1,&sum2,res,check+3)-ac-bd;

#if SHOW_PROCESS
	printf("\n(%d) Final computation of members for numbers %llu and %llu:\n",check,*x,*y);
	printf("ac=%llu\nbd=%llu\nabcd=%llu\n",ac,bd,abcd);
#endif

#if SHOW_PROCESS
	printf("\n(%d) ==> %llu*10^%d + %llu*10^%d + %llu\n",check,ac,max,abcd,maxdiv2,bd);
#endif

	int sizer=sizex+sizey-1;

	Compute_and_Fill_Array(ac,abcd,bd,max,res,sizer);

	return -1Lu;
}

int main(void)
{
	unsigned long long int x,y;

	/* Input x and y */

	printf("Please enter numbers under this form: x y\n");
	scanf("%llu %llu",&x,&y);

	int sizex=Nb_Digits(x);
	int sizey=Nb_Digits(y);

#if SHOW_PROCESS
	printf("Nb_digits(x)= %d Nb_digits(y)=%d \n",sizex,sizey);
#endif

	if((sizex>=17 && sizey>=9) || (sizey>=17 && sizex>=9) || sizex>18 || sizey>18) 
	{
		printf("Cannot continue because result may not be accurate !\n");
		exit(EXIT_FAILURE);
	}

	int sizer=sizex+sizey;

	/* Variable that will hold the result of multiplication */

	char* res=(char*)calloc(sizer+1,sizeof(char));

	karatsuba(&x,&y,res,0);

	print_result(res,sizer-1);

	free(res);

	return 0;
}

