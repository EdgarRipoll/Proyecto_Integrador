#include "Variables.h"
void Timer_Interrupt();
int contTimer=0;
int interrupt = 2;
bool toggle=0;
mraa::Gpio* PowerKey;
void Timer_Interrupt()
{



	contTimer++;

	if(toggle)
	{
		toggle=0;
		PowerKey->write(1);
	}else{
		toggle=1;
		PowerKey->write(0);
	}
/*
	adc_value = ArraySensor->getRawValue();
	if (myfile.is_open())
		myfile << adc_value<<std::endl;
	else std::cout << "Unable to open file";*/
}

