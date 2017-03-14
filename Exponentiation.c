/* 
 * ============================================================================
 * Name        : Exponentiation.c
 * Author      : Meninx
 * Version     : 1.0
 * Copyright   : Copyright 2017. You can use this code however and wherever you want no strings attached
 * Description : Exponentiation Functions with different approaches (simplified versions)
 *               Computing x^y 
 *               Computing x^y mod m
 * ============================================================================
 */

#include <stdio.h>

/* The complexity of this function is O(log2(n))  */

unsigned long long int pow_1(int x,int y)
{
	if(y==0)
		return 1;

	if(y%2!= 0)
		return pow_1(x,y-1)*x;

	unsigned long long int res=pow_1(x,y/2);

	return res*res;

}

/* The complexity of this function is O(n) + O(1)  */

unsigned long long int pow_2(int x,int y)
{
	if(y==0)
		return 1;

	return x*pow_2(x,y-1);
}

/* The complexity of this function is O(n) + O(log2(n)) */

unsigned long long int pow_3(int x,int y)
{
	if(y==0)
		return 1;

	if(y%2!= 0)
		return x*pow_3(x,y-1);

	return pow_3(x,y/2)*pow_3(x,y/2);
}

/*
 * Modular exponentiation O(log2(n)):
 * x^y mod m = (   x^(y/2)       *      x^(y/2)    ) mod m
 *           = ( (x^(y/2) mod m) * (x^(y/2) mod m) ) mod m
 *
 * x^y mod m = ( ( x mod m ) ^ y  ) mod m
 */

int mod_1(int x,int y,int m)
{
	int mod;

	if(y==0)
		return 1%m;

	if(y==1)
		return x%m;

	if(y%2!=0)
	{
		mod=mod_1(x,y-1,m)*(x%m);
		return mod%m;
	}

	/* Case if y is even - No need for condition check - */

	mod=mod_1(x,y/2,m);

	mod=mod*mod;

	return mod%m;
}

int main(void)
{
	int x,y,m,choice;

	printf("Print 0 to compute x^y or x^y mod m otherwise: ");
	scanf("%d",&choice);

	if(choice==0)
	{
		printf("Please enter x and y: ");
		scanf("%d %d",&x,&y);
		printf("%llu\n",pow_1(x,y));
	}
	else
	{
		printf("Please enter x, y and m: ");
		scanf("%d %d %d",&x,&y,&m);
		printf("%d\n",mod_1(x,y,m));
	}

	return 0;
}

