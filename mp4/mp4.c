/* Young Bin Jo
   MP4
   659575499
   
   This MP uses Halley method to find the root of polynomial equation. For Halley method, I used the equation given in website and used 10000 loops provided. 
   For rootbound part, I used and, or symbol to find the sign difference between two coefficients. If there is no sign difference, I wrote the code to print no root found.
   Otherwise I printed all roots.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double abs_double(double y)
{
	return (fabs(y));
	
	//fabs command returns absolute value of double

    //Change this to return the absolute value of y i.e |y|

}

double fx_val(double a, double b, double c, double d, double e, double x)
{
	double output;
	output = a*pow(x,4) + b*pow(x,3) + c*pow(x,2) + d*x + e;
	return output;
	//Copy the polynomial equation
    //Change this to return the value of the polynomial at the value x
}

double fx_dval(double a, double b, double c, double d, double e, double x)
{
	double output;
	output = 4*a*pow(x,3) + 3*b*pow(x,2) + 2*c*x + d;
	return output;
	//write the derivative of polynomial equation
    //Change this to return the value of the derivative of the polynomial at the value x

}

double fx_ddval(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the value of the double derivative of the polynomial at the value x
	double output;
	output = 12*a*pow(x,2) + 6*b*x + 2*c;
	return output;
	//write the double derivative of polynomial equation
}


double newrfind_halley(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the root found starting from the initial point x using Halley's method
    double next; // Xn+1
	double current = x; // Xn: we input the starting value
	double dividend = 2* fx_val(a,b,c,d,e,x)*fx_dval(a,b,c,d,e,x); // 2f(Xn)f'(Xn)
	double divisor = 2*fabs(fx_dval(a,b,c,d,e,x) * fx_dval(a,b,c,d,e,x))-(fx_val(a,b,c,d,e,x)*fx_ddval(a,b,c,d,e,x)); //2|f'(Xn)*f'(Xn)|-f(Xn)*f''(Xn)
	int i;
	
	for (i=0; i < 10000; i++)  // run no more than 10000 iteration
	{
		next = current -(dividend / divisor); // Equation from page Xn+1 = Xn - 2f(Xn)f'(Xn)/2|f'(Xn)*f'(Xn)|-f(Xn)*f''(Xn) 
		
		dividend = 2* fx_val(a,b,c,d,e,next)*fx_dval(a,b,c,d,e,next); 	// for next loop Xn in polynomial equation changes to Xn+1 which is next
		divisor = 2*fabs(fx_dval(a,b,c,d,e,next) * fx_dval(a,b,c,d,e,next))-(fx_val(a,b,c,d,e,next)*fx_ddval(a,b,c,d,e,next));

		if (fabs(next - current) < 0.000001)  // Stop iteration when successive iteration doesn't change by 0.000001
		{
			return next;
		}
		current = next; // for next loop current becomes next and find new next
	}
	return 0;
}

int rootbound(double a, double b, double c, double d, double e, double r, double l)
{
    //Change this to return the upper bound on the number of roots of the polynomial in the interval (l, r)
	double vl=0, vr=0;
	int result=0;
	
	double al=a;
	double bl=(4*a*l+b);
	double cl=6*a*pow(l,2)+3*b*l+c;
	double dl=4*a*pow(l,3)+3*b*pow(l,2)+2*c*l+d;
	double el=a*pow(l,4)+b*pow(l,3)+c*pow(l,2)+d*l+e;

	double ar=a;	
	double br=(4*a*r+b);
	double cr=6*a*pow(r,2)+3*b*r+c;
	double dr=4*a*pow(r,3)+3*b*pow(r,2)+2*c*r+d;
	double er=a*pow(r,4)+b*pow(r,3)+c*pow(r,2)+d*r+e;

	// if there is a sign difference increment vl or vr

	if ((al < 0 && bl > 0) || (al > 0 && bl < 0))
	{
		vl = vl+1;
	}
	if ((bl < 0 && cl > 0) || (bl > 0 && cl < 0))
	{
		vl = vl+1;
	}
	if ((cl < 0 && dl > 0) || (cl > 0 && dl < 0))
	{
		vl = vl+1;
	}
	if ((dl < 0 && el > 0) || (dl > 0 && el < 0))
	{
		vl = vl+1;
	}
	
	if ((ar < 0 && br > 0) || (ar > 0 && br < 0))
	{
		vr = vr+1;
	}
	if ((br < 0 && cr > 0) || (br > 0 && cr < 0))
	{
		vr = vr+1;
	}
	if ((cr < 0 && dr > 0) || (cr > 0 && dr < 0))
	{
		vr = vr+1;
	}
	if ((dr < 0 && er > 0) || (dr > 0 && er < 0))
	{
		vr = vr+1;
	}

	result= fabs(vl-vr); // result is number of sign difference

	if (result == 0)  // if there is no sign difference, there is no root	
	{
		printf("The polynomial has no roots in the given interval.\n");
		return 0;
	}
	else
	{
		return result;	// otherwise return number of sign difference
	}
}

int main(int argc, char **argv)
{
	double a, b, c, d, e, l, r;
	FILE *in;

	if (argv[1] == NULL) {	
		printf("You need an input file.\n");
		return -1;
	}
	in = fopen(argv[1], "r");
	if (in == NULL)
		return -1;
	fscanf(in, "%lf", &a);
	fscanf(in, "%lf", &b);
	fscanf(in, "%lf", &c);
	fscanf(in, "%lf", &d);
	fscanf(in, "%lf", &e);
	fscanf(in, "%lf", &l);
	fscanf(in, "%lf", &r);
    
    //The values are read into the variable a, b, c, d, e, l and r.
    //You have to find the bound on the number of roots using rootbound function.
    //If it is > 0 try to find the roots using newrfind function.
    //You may use the fval, fdval and fddval funtions accordingly in implementing the halleys's method.
    
    double x= l;

	if (rootbound(a,b,c,d,e,r,l)!=0)	// if there is a sign difference
	{
		for ( x=l; x<=r; x= x+0.5)	// values from l to r with a gap of 0.5
		{
			if (newrfind_halley(a,b,c,d,e,x)==0)	// Use newrfind_halley function to check whether there is a root or not
			{
				printf("No roots found.\n");
			}
			else
			{
				printf("Root found: %lf \n",(newrfind_halley(a,b,c,d,e,x)));
			}
		}
	} 
    fclose(in);
    
    return 0;
}
