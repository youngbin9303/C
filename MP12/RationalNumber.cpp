#include "RationalNumber.h"

//to_String converts numerator and denominator to string of type num/denom
string RationalNumber::to_String(void){
	stringstream my_output;
	my_output << numerator << "/" << denominator;
	return my_output.str();
}

RationalNumber::RationalNumber(){
	NumberType = RATIONAL; numerator = 0; denominator = 0; 
}

RationalNumber::RationalNumber(int numer, int denom){
	NumberType = RATIONAL; numerator = numer; denominator = denom; 
}

void RationalNumber::set_numerator(int numer){
	numerator = numer; 
}
 
void RationalNumber::set_denominator(int denom){
	denominator = denom; 
}

int RationalNumber::get_numerator(void) const{ 
	return numerator; 
}

int RationalNumber::get_denominator(void) const{ 
	return denominator; 
}

void RationalNumber::set_value (int numer, int denom){ 
	numerator = numer; denominator = denom; 
}

// Used euclid method for calculation gcd.
int RationalNumber::gcd(int a, int b) 
{
	while(a != b)
	{
		if(a > b)
		{
			a = a - b;
		}
		else					
		{
			b = b - a;
		}
	}
	return a;
}
double RationalNumber::magnitude(){ 
	return abs(get_numerator() / get_denominator());
}
double RationalNumber::decimal_value() const{ 
	return ((double)numerator)/((double)denominator); 
}

// Operation between rational and rational. 

RationalNumber RationalNumber::operator + (const RationalNumber& arg) 
{
    int common = gcd((get_numerator() * arg.get_denominator() + arg.get_numerator() * get_denominator()), (get_denominator() * arg.get_denominator())); 
    return RationalNumber(((get_numerator() * arg.get_denominator() + arg.get_numerator() * get_denominator())/common), (get_denominator() * arg.get_denominator()/common));
}

RationalNumber RationalNumber::operator - (const RationalNumber& arg) 
{
   int common = gcd((get_numerator() * arg.get_denominator() - arg.get_numerator() * get_denominator()), (get_denominator() * arg.get_denominator())); 
    return RationalNumber(((get_numerator() * arg.get_denominator() - arg.get_numerator() * get_denominator())/common), (get_denominator() * arg.get_denominator()/common));
}

RationalNumber RationalNumber::operator * (const RationalNumber& arg)
{
    int common = gcd((get_numerator() * arg.get_numerator()),(get_denominator() * arg.get_denominator()));
    return RationalNumber((get_numerator() * arg.get_numerator())/common, (get_denominator() * arg.get_denominator())/common); 
}

RationalNumber RationalNumber::operator / (const RationalNumber& arg) 
{
    int common = gcd((get_numerator() * arg.get_denominator()),(get_denominator() * arg.get_numerator()));
    return RationalNumber(((get_numerator() * arg.get_denominator())/common), ((get_denominator() * arg.get_numerator())/common));
}


// Operation between rational and polar.

PolarNumber RationalNumber::operator + (const PolarNumber& arg)
{
	float c;
    	float a = ((decimal_value()) + (arg.get_magComponent() * cos(arg.get_phaseComponent())));
	float b = ((arg.get_magComponent() * sin(arg.get_phaseComponent())));
	if (a<0 && b<0){
	c = atan(b/a) - M_PI;
	}
	else if (a<0 && b>0){
	c = atan(b/a) + M_PI;
	}
	else if (a>0 && b<0){
	c = atan(b/a);
	}
	else if (a>0 && b>0){
	c = atan(b/a);
	}
	return PolarNumber(sqrt(pow(a,2)+pow(b,2)), c);
}

PolarNumber RationalNumber::operator - (const PolarNumber& arg)
{
	float c;
    	float a = ((decimal_value()) - (arg.get_magComponent() * cos(arg.get_phaseComponent())));
	float b = ((0 - (arg.get_magComponent() * sin(arg.get_phaseComponent()))));
	if (a<0 && b<0){
	c = atan(b/a) - M_PI;
	}
	else if (a<0 && b>0){
	c = atan(b/a) + M_PI;
	}
	else if (a>0 && b<0){
	c = atan(b/a);
	}
	else if (a>0 && b>0){
	c = atan(b/a);
	}
	return PolarNumber(sqrt(pow(a,2)+pow(b,2)), c);
}

//For multiplication, rational number changes both mag component and polarinary component

PolarNumber RationalNumber::operator * (const PolarNumber& arg)
{
    return PolarNumber((decimal_value() * arg.get_magComponent()), (arg.get_phaseComponent()));
}

//For division, we multiply numerator and denominator by conjugate Polar number

PolarNumber RationalNumber::operator / (const PolarNumber& arg)
{
    return PolarNumber((decimal_value() / arg.get_magComponent()), (-1.) * arg.get_phaseComponent());
}


// Operation between rational and real

RealNumber RationalNumber::operator + (const RealNumber& arg)
{
    return RealNumber(decimal_value() + arg.get_value());
}

RealNumber RationalNumber::operator - (const RealNumber& arg)
{
    return RealNumber(decimal_value() - arg.get_value());
}

RealNumber RationalNumber::operator * (const RealNumber& arg)
{
    return RealNumber(decimal_value() * arg.get_value());
}

RealNumber RationalNumber::operator / (const RealNumber& arg)
{
    return RealNumber(decimal_value() / arg.get_value());
}

