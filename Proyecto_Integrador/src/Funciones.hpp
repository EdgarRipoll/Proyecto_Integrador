#include "Variables.h"
#include <stdlib.h>
void Timer_Int();
void signal_handler_IO (int status);   /* definition of signal handler */
char* PromedioBMP();


void Timer_Int(){
	if(HabilitarHR)
	{
		if(toggle)
		{
			Radial->getMedicion();
			toggle=0;
		}else{
			Ulnar->getMedicion();
			toggle=1;
		}
		if(!Radial->getMedicion30s() && !Ulnar->getMedicion30s())
			ReestablecerTimer=1;
	}

	cont++;
	if(cont > (1500/Timer))
	{
		//std::cout<<"PideUbicacion\n";
		if(LeaSMS)
		{
			SIM908->WriteATCommand(LeerSMS);
		}
		if(PideUbicacion)
		{
			//std::cout<<"PideUbicacion";
			SIM908->WriteATCommand(PedirUbicacion);
		}
		//std::cout<<"PideUbicacion2: " << PideUbicacion << "\n";
		delay=0;
		cont=0;
	}
}

void signal_handler_IO (int status)
{
		SIM908->ReadResponse();
		delay=1;
}

char* PromedioBMP()
{
	int	BPM_avg;
	BPM_avg = (Ulnar->getBPM() + Radial->getBPM()) / 2;
	sprintf(BPM_Char,"Las pulsaciones por minuto son: %d\r",BPM_avg);
	return	BPM_Char;
}
