#include "Funciones.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
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

Radial = new HR(0);
Ulnar = new HR(1);
sleep(10);
/*
try {
    PowerKey = new mraa::Gpio(7);
} catch (std::exception& e) {
    std::cout << e.what() << "Invalid GPIO" << std::endl;
}
int response = PowerKey->dir(mraa::DIR_OUT);
if (response != MRAA_SUCCESS)
    mraa_result_print((mraa_result_t) MRAA_SUCCESS);
PowerKey->write(0);
*/

///////////////////////INICIALIZACION DE TIMER///////////////////////////////////
	if(start_timer(2, &Timer_Interrupt))
	  {
	    printf("\n timer error\n");
	    return(1);
	  }
int cont=0;
//////////////////////BUCLE DE PROGRAMA/////////////////////////////////////////
	while(running==0)
	{
		if(Ulnar->getCambioVector())
		{

			Ulnar->ProcesarSenal();
/*
			if (Procesado.is_open())
			{
				for(int j=0; j<=509 ; j++)
				{
					Procesado << Radial->getProcesamiento(j) <<std::endl;
				}
			}
			else{
				std::cout << "Unable to open file Procesado";
			}
*/
			if (RawU.is_open())
			{
				for(int j=0; j<=499 ; j++)
					RawU << Ulnar->getRaw(j) <<std::endl;
			}
			else{
				std::cout << "Unable to open file Raw";
			}
			if (IndexU.is_open())
			{
				for(int j=0; j<=Ulnar->getContador()-1 ; j++)
					IndexU << Ulnar->getIndex(j) <<std::endl;
			}
			else{
				std::cout << "Unable to open file Index";
			}
		}

		if(Radial->getCambioVector())
		{

			Radial->ProcesarSenal();
/*
			if (Procesado.is_open())
			{
				for(int j=0; j<=509 ; j++)
				{
					Procesado << Radial->getProcesamiento(j) <<std::endl;
				}
			}
			else{
				std::cout << "Unable to open file Procesado";
			}
*/
			if (RawR.is_open())
			{
				for(int j=0; j<=499 ; j++)
					RawR << Radial->getRaw(j) <<std::endl;
			}
			else{
				std::cout << "Unable to open file Raw";
			}
			if (IndexR.is_open())
			{
				for(int j=0; j<=Radial->getContador()-1 ; j++)
					IndexR << Radial->getIndex(j) <<std::endl;
			}
			else{
				std::cout << "Unable to open file Index";
			}
			cont++;
			if(cont>30)
				running=1;
		}
	}
	Procesado.close();
	RawR.close();
	IndexR.close();
	RawU.close();
	IndexU.close();
	Radial->~HR();
	Ulnar->~HR();
    return MRAA_SUCCESS;
}
