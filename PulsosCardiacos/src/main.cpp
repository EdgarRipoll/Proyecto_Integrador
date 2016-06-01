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

sleep(5);


///////////////////////INICIALIZACION DE TIMER///////////////////////////////////
	if(start_timer(5, &Timer_Interrupt))
	  {
	    printf("\n timer error\n");
	    return(1);
	  }
int cont=0;
//////////////////////BUCLE DE PROGRAMA/////////////////////////////////////////
	while(running==0)
	{
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
			if (Raw.is_open())
			{
				for(int j=0; j<=499 ; j++)
					Raw << Radial->getRaw(j) <<std::endl;
			}
			else{
				std::cout << "Unable to open file Raw";
			}
			if (Index.is_open())
			{
				for(int j=0; j<=Radial->getContador()-1 ; j++)
					Index << Radial->getIndex(j) <<std::endl;
			}
			else{
				std::cout << "Unable to open file Index";
			}
			cont++;
			if(cont>20)
				running=1;
		}
	}
	Procesado.close();
	Raw.close();
	Index.close();
	Radial->~HR();
    return MRAA_SUCCESS;
}
