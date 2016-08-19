#include "Variables.h"
void Timer_Interrupt();


void Timer_Interrupt()
{
	if(toggle)
	{
		Radial->getMedicion();
		toggle=0;
		//PowerKey->write(1);
	}else{
		Ulnar->getMedicion();
		toggle=1;
		//PowerKey->write(0);
	}
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

