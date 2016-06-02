#include "Variables.h"
#include <stdlib.h>
void Timer_Int();
void signal_handler_IO (int status);   /* definition of signal handler */
void EnviaSalud();


void Timer_Int(){
	if(delay)
	{
		cont++;
		if(cont>3)
		{
			if(LeaSMS)
			{
				SIM908->WriteATCommand(LeerSMS);
			}
			if(PideUbicacion)
				{
				std::cout<<"PideUbicacion";
				SIM908->WriteATCommand(PedirUbicacion);
				}
			delay=0;
			cont=0;
		}
	}
}

void signal_handler_IO (int status)
{
		SIM908->ReadResponse();
		delay=1;
}

void EnviaSalud()
{

}
