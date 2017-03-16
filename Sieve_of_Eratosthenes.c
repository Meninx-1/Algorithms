/* 
 * ============================================================================
 * Name        : Sieve_of_Eratosthenes.c
 * Author      : Meninx
 * Version     : 1.0
 * Copyright   : Copyright 2017. You can use this code however and wherever you want no strings attached
 * Description : C Function to print prime numbers below N [O(sqrt(n)*n*ln(n))] 
 *============================================================================
 */

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

/* Print Prime array */

void Print_Array(int N, _Bool* Primes)
{
	for(int i=2 ;i<=N ;++i )
	{
		if(!Primes[i])
		{
			printf("%d ",i);
		}
	}

	printf("\n");
}

/* This function is intended to do the Sieve */

void Sieve_of_Eratosthenes(int N, _Bool* Primes) 
{
	Primes[0]=true;
	Primes[1]=true;

	int squaren=sqrt(N);

	printf("\nPrimes Numbers under %d are:\n",N);

	for(int i=2 ;i<=squaren;++i )
	{
		if(Primes[i])
		{
			continue;
		}

		for(int j=i*2 ;j<=N ;j+=i )
		{
			Primes[j]=true;
		}
	}

}

int main(void)
{
	int N;
	_Bool* Primes=(_Bool*)calloc(10001,sizeof(_Bool));

	/* Read input N */

	printf("Enter N to get primes below it: ");
	scanf("%d",&N);

	Sieve_of_Eratosthenes(N,Primes);

	Print_Array(N,Primes);

	free(Primes);

	return 0;
}

