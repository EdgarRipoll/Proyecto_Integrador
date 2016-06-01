#include "Variables.h"
void Timer_Interrupt();


void Timer_Interrupt()
{
	Radial->getMedicion();
	/*
	if(toggle)
	{
		PowerKey->write(1);
		toggle=0;
	}else{
		PowerKey->write(0);
		toggle=1;
	}
*/
}

