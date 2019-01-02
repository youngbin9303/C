#include "prime.h"

int is_prime(int n){

	int i, remainder;
	
	for (i=2; i < n; i++)
		{
			remainder = n%i;
			if (remainder == 0)
			{
				return 0;
				break;
			}
		}
		return 1;


  // Return 1 if n is a prime, and 0 if it is not
  return 0;
}

