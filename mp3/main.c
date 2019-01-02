#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	double omega1, omega2, omegac, T, dt;
	int N;

	//Scan the inputs from the user.
	scanf("%lf %lf %lf", &omega1, &omega2, &omegac);
	
	T = 3 * 2 * M_PI / omega1;      // Total time
    	N = 20 * T / (2 * M_PI / omega2);   // Total number of time steps
    	dt = T / N;             // Time step

	int i;
	double Voutnew = 0, Voutcur = 0, Voutprev = 0;
		
		// Write your code here!

 	double a = 0, b = 0, c = 0, d = 0; // Set a, b and c to simplify the equation //
	for (i = 0; i < N; i++) // Set the for loop
		{  
		a = (1 / (sqrt(2) * dt * omegac)); 
		b = (1 / (dt * dt * omegac * omegac));
		c = (sin(omega1 * i * dt));
		d = (0.5 * sin(omega2 * i * dt));
		/* Since the equation is very long, we can simplify by using a, b, c and d.
		  4 expressions will simplify the Voutnew expression */
					
		Voutnew = (1 / (a + b)) * ((((2 * b) - 1) * Voutcur) + ((a - b) * Voutprev) + c + d); // differential equation //
	
		printf("%lf\n", Voutcur);
		Voutprev = Voutcur; // set Voutprev to Voutcur //
		Voutcur = Voutnew; // set Voutcur to Voutnew for next loop//
		

		}
	       
	return 0;
}
