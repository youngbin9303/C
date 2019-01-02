#include <stdio.h>
#include <math.h>

int main()
{
	double omega1, omega2, x;
	int n;
	
	printf("Enter values of n, omega1, omega2:");
	scanf("%d %lf %lf" ,&n, &omega1, &omega2);
	
	int i;
	for (i=0; i<n; i++)
    	{
		x = (i*M_PI)/n;
		printf("%lf %lf\n", x, sin(omega1*x)+0.5*sin(omega2*x));
	}

   
    return 0;
}

