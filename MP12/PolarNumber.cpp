#include "PolarNumber.h"

//to_String converts mag and phase components to string of type a<b
string PolarNumber::to_String(void){

        stringstream my_output;
	my_output << magComponent<< "<"<<180.0*phaseComponent/M_PI;
        return my_output.str();

}
//Empty Constructor

PolarNumber::PolarNumber(){
	NumberType = POLAR; magComponent = 0.0; phaseComponent = 0.0; 
}

//Complete Constructor

PolarNumber::PolarNumber(double magnitude, double phase){
	NumberType = POLAR; magComponent = magnitude; phaseComponent = phase; 
}
//PolarNumber( const PolarNumber& other );



//Setter and getter functions
void PolarNumber::set_magComponent(double mval){
	magComponent = mval; 
}
 
void PolarNumber::set_phaseComponent(double phval){
	phaseComponent = phval; 
}

double PolarNumber::get_magComponent(void) const{ 
	return magComponent; 
}

double PolarNumber::get_phaseComponent(void) const{ 
	return phaseComponent; 
}

void PolarNumber::set_value (double mval, double phval){ 
	magComponent = mval; phaseComponent = phval;
}
// Polar and Polar operation

PolarNumber PolarNumber::operator + (const PolarNumber& arg) 
{
	float c;
	float a = ((get_magComponent() * cos(get_phaseComponent())) + (arg.get_magComponent() * cos(arg.get_phaseComponent())));
	float b = ((get_magComponent() * sin(get_phaseComponent())) + (arg.get_magComponent() * sin(arg.get_phaseComponent())));
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

PolarNumber PolarNumber::operator - (const PolarNumber& arg) 
{
	float c;
	float a = ((get_magComponent() * cos(get_phaseComponent())) - (arg.get_magComponent() * cos(arg.get_phaseComponent())));
	float b = ((get_magComponent() * sin(get_phaseComponent())) - (arg.get_magComponent() * sin(arg.get_phaseComponent())));
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
PolarNumber PolarNumber::operator * (const PolarNumber& arg)
{
    return PolarNumber((get_magComponent() * arg.get_magComponent()), (get_phaseComponent() + arg.get_phaseComponent()));
}

PolarNumber PolarNumber::operator / (const PolarNumber& arg) 
{
    return PolarNumber((get_magComponent() / arg.get_magComponent()), (get_phaseComponent() - arg.get_phaseComponent()));
}


//Polar Rational operation

PolarNumber PolarNumber::operator + (const RationalNumber& arg)
{
	float c;
	float a = ((get_magComponent() * cos(get_phaseComponent())) + (arg.decimal_value()));
	float b = ((get_magComponent() * sin(get_phaseComponent())));
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
PolarNumber PolarNumber::operator - (const RationalNumber& arg)
{
	float c;
	float a = ((get_magComponent() * cos(get_phaseComponent())) - (arg.decimal_value()));
	float b = ((get_magComponent() * sin(get_phaseComponent())));
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

PolarNumber PolarNumber::operator * (const RationalNumber& arg)
{
    return PolarNumber((get_magComponent() * arg.decimal_value()), (get_phaseComponent()));
}

//For division, we multiply numerator and denominator by conjugate Polar number

PolarNumber PolarNumber::operator / (const RationalNumber& arg)
{
    return PolarNumber((get_magComponent() / arg.decimal_value()), (get_phaseComponent()));
}


//Polar Real operation

PolarNumber PolarNumber::operator + (const RealNumber& arg)
{
	float c;
	float a = ((get_magComponent() * cos(get_phaseComponent())) + (arg.get_value()));
	float b = ((get_magComponent() * sin(get_phaseComponent())));
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

PolarNumber PolarNumber::operator - (const RealNumber& arg)
{
	float c;
	float a = ((get_magComponent() * cos(get_phaseComponent())) - (arg.get_value()));
	float b = ((get_magComponent() * sin(get_phaseComponent())));
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

PolarNumber PolarNumber::operator * (const RealNumber& arg)
{
    return PolarNumber(get_magComponent() * arg.get_value(), get_phaseComponent());
}

PolarNumber PolarNumber::operator / (const RealNumber& arg)
{
    return PolarNumber(get_magComponent() / arg.get_value(), get_phaseComponent());
}
