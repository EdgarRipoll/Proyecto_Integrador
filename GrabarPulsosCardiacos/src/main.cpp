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


try {
    PowerKey = new mraa::Gpio(7);
} catch (std::exception& e) {
    std::cout << e.what() << "Invalid GPIO" << std::endl;
}
int response = PowerKey->dir(mraa::DIR_OUT);
if (response != MRAA_SUCCESS)
    mraa_result_print((mraa_result_t) MRAA_SUCCESS);
PowerKey->write(0);

///////////////////////INICIALIZACION DE TIMER///////////////////////////////////
	if(start_timer(interrupt, &Timer_Interrupt))
	  {
	    printf("\n timer error\n");
	    return(1);
	  }

//////////////////////BUCLE DE PROGRAMA/////////////////////////////////////////
	while(running==0)
	{
		if((contTimer > 5000) && (interrupt == 2))
		{
			contTimer = 0;
			interrupt = 500;
			if(start_timer(interrupt, &Timer_Interrupt))
			    printf("\n timer error\n");
		}
		if((contTimer > 20) && (interrupt == 500))
		{
			contTimer = 0;
			interrupt = 2;
			if(start_timer(interrupt, &Timer_Interrupt))
			    printf("\n timer error\n");
		}
	}
	myfile.close();
    ArraySensor->~ArrayPC_Sensor();
    return MRAA_SUCCESS;
}

