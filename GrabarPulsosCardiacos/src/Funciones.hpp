#include "Variables.h"

void Timer_Int();
//void signal_handler_IO (int status);   /* definition of signal handler */

void Timer_Int(){
	adc_value = ArraySensor->getRawValue();
	std::cout<<adc_value<<std::endl;
}
/*
void signal_handler_IO (int status)
{

}
*/
