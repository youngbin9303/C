#include <stdio.h>
#include "prime.h"


int main()
{
	int number, a, result;
	
	printf("Enter a number: ");
	scanf("%d", &number);
	
	printf("Printing primes less than or equal to %d:\n", number);
	
	
	for(a=2; a <= number; a++)
	{
		result = is_prime(a);
		if(result == 1)
		{
			printf("%d", a);
			if(a <= number-2)
			printf(", ");
			else
			printf(" ");
		}
	}
	printf("\n");
	

  // Write the code to take a number n from user and print all the prime numbers between 1 and n


  return 0;
}

