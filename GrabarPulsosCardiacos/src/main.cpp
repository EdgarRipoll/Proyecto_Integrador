#include "Funciones.hpp"
using namespace std;
int running = 0;
void sig_handler(int signo)
	{
	    if (signo == SIGINT) {
	        running = -1;
	    }
	}
//////////////////////INICIO PROGRAMA////////////////////////////////////////////
int main()
{

/////////////////////////INICIALIZACION DE GPIO//////////////////////////////////

ArraySensor = new ArrayPC_Sensor(0);

///////////////////////INICIALIZACION DE TIMER///////////////////////////////////
	if(start_timer(1, &Timer_Interrupt))
	  {
	    printf("\n timer error\n");
	    return(1);
	  }

//////////////////////BUCLE DE PROGRAMA/////////////////////////////////////////
	while(running==0)
	{
	}
	myfile.close();
    ArraySensor->~ArrayPC_Sensor();
    return MRAA_SUCCESS;
}

