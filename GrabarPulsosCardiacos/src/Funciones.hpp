#include "Variables.h"
void Timer_Interrupt();


void Timer_Interrupt()
{
	adc_value = ArraySensor->getRawValue();
	if (myfile.is_open())
		myfile << adc_value<<std::endl;
	else std::cout << "Unable to open file";
}

