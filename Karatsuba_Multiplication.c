/* 
 * ============================================================================
 * Name        : Karatsuba_multiplication.c
 * Author      : Meninx
 * Version     : 1.0
 * Copyright   : Copyright 2017. You can use this code however and wherever you want no strings attached
 * Description : C Function to Perform Karatsuba mutliplication of numbers with at most 18 digits (for architecture 64-bit)
 * ============================================================================
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

unsigned long long int Pow_10[9]={10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};

/* 
 * This recursive function is computing the multiplication of 2 numbers x and y
 * using karatsuba approach and showing the process of every iteration 
 */

unsigned long long int karatsuba (unsigned long long* x, unsigned long long int* y, char* res, int check)
{
	int sizex=log10(*x)+1;
	int sizey=log10(*y)+1;

	int max=sizex;

	if(sizey>max)
		max=sizey;
	if(max%2!=0)
		++max;

	printf("\n\nx=%llu y=%llu \n",*x,*y);

	/*	for long long int with 64 bits we can use the multiplication safely for 9 digits each */

	if(*x<=Pow_10[7] && *y<=Pow_10[7])
	{
		printf("%llu\n",(*x)*(*y));
		return (unsigned long long int)(*x)*(*y);
	}

	/* 
	 * 	x=10^(n/2)*a+b
	 * 	y=10^(n/2)*c+d
	 */

	unsigned long long int a,b,c,d;
	unsigned long long int ac,bd,abcd;
	int maxdiv2=max/2;

	a=*x/Pow_10[maxdiv2-1];
	b=*x%Pow_10[maxdiv2-1];
	c=*y/Pow_10[maxdiv2-1];
	d=*y%Pow_10[maxdiv2-1];

	printf("a=%-8lld b=%-8lld\nc=%-8lld d=%-8lld\n",a,b,c,d);

	unsigned long long int sum1=a+b;
	unsigned long long int sum2=c+d;

	ac=karatsuba(&a,&c,res,check+1);
	bd=karatsuba(&b,&d,res,check+1);
	abcd=karatsuba(&sum1,&sum2,res,check+1)-ac-bd;

	if(check!=0 && (sizex+sizey<=19))
	{
		printf("\n%llu*10^%d + %llu*10^%d + %llu\n",ac,max,abcd,maxdiv2,bd);

		unsigned long long int ress=(unsigned long long int)ac*Pow_10[max-1]+abcd*Pow_10[maxdiv2-1]+bd;

		return ress;
	}
	else
	{
		printf("     \n%llu*10^%d + %llu*10^%d + %llu\n",ac,max,abcd,max/2,bd);

		/* 
		 * 
		 * 
		 * 	Still missing the last part of implementation for calculating the result and put it in 
		 * 	the array res 
		 * 
		 * 
		 */

		return 0;
	}
}

int main(void)
{
	unsigned long long int x,y;
	scanf("%llu %llu",&x,&y);

	/* read input x and y */

	int sizex=log10(x)+1;
	int sizey=log10(y)+1;

	char* res= (char*)calloc(sizex+sizey+1,sizeof(char));

	karatsuba(&x,&y,res,0);

	free(res);
	return 0;
}

