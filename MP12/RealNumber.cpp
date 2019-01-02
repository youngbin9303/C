/* Young Bin Jo
This MP caculated the addition, deduction, multiplication and division between real number, rational number and polar number. For calculation
between real numbers, I just used regular calculation. For calculation between real and rational, I used decimal value for rational part.
For caculation between real and polar, I converted polar number to complex number in form of a + bi and used real number as a + 0i. After doing
calculation in complex form, I converted magnitude part as sqrt(a^2 + b^2) and phase part as arctan(b/a). For rational part, I used GCD to
simplify the fraction after operation. For polar part, I used condition to calculate the phase component based on the quadrant of polar number
after calculation. Last thing to consider was overload. For operation between real and polar, the result appeared as polar number.

*/

#include "RealNumber.h"

//to_String converts real and imaginary components to string of type a+bi
string RealNumber::to_String(void){
	stringstream my_output;
	my_output << value;
	return my_output.str();
}

//Empty constructor sets NumberType as undefined value
RealNumber::RealNumber(){
	NumberType = REAL; value = 0.0; 
}
//Complete constructor sets NumberType according to input value
RealNumber::RealNumber(double rval){
	NumberType = REAL; value = rval; 
}

//Getter function for NumberType variable
double RealNumber::get_value(void) const{
	return value; 
}
//Setter function for RealNumber variable
void RealNumber::set_value(double rval){
	value = rval; 
}

double RealNumber::magnitude(){
	return abs(value);
} 

// Operation between real number and real number. 

RealNumber RealNumber::operator + (const RealNumber& arg) 
{
    return RealNumber(get_value() + arg.get_value());
}

RealNumber RealNumber::operator - (const RealNumber& arg) 
{
    return RealNumber(get_value() - arg.get_value());
}

RealNumber RealNumber::operator * (const RealNumber& arg)
{
    return RealNumber(get_value() * arg.get_value());
}

RealNumber RealNumber::operator / (const RealNumber& arg) 
{
    return RealNumber(get_value() / arg.get_value());
}

// Operation between real and polar. Result comes out as polar number due to overload.

PolarNumber RealNumber::operator + (const PolarNumber& arg)
{
	float c;
	float a = ((get_value()) + (arg.get_magComponent() * cos(arg.get_phaseComponent())));
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
PolarNumber RealNumber::operator - (const PolarNumber& arg)
{
	float c;
	float a = ((get_value()) - (arg.get_magComponent() * cos(arg.get_phaseComponent())));
	float b = (((0 - arg.get_magComponent() * sin(arg.get_phaseComponent()))));
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

PolarNumber RealNumber::operator * (const PolarNumber& arg)
{
    return PolarNumber(get_value() * arg.get_magComponent(), arg.get_phaseComponent());
}

PolarNumber RealNumber::operator / (const PolarNumber& arg)
{
    return PolarNumber(get_value() / arg.get_magComponent(), (-1.) * arg.get_phaseComponent());
}

// Operation between real and rational. Used decimal value of rational part.

RealNumber RealNumber::operator + (const RationalNumber& arg)
{
    return RealNumber(get_value() + arg.decimal_value());
}

RealNumber RealNumber::operator - (const RationalNumber& arg)
{
    return RealNumber(get_value() - arg.decimal_value());
}

RealNumber RealNumber::operator * (const RationalNumber& arg)
{
    return RealNumber(get_value() * arg.decimal_value());
}

RealNumber RealNumber::operator / (const RationalNumber& arg)
{
    return RealNumber(get_value() / arg.decimal_value());
}
