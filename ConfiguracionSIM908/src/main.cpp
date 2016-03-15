#include <unistd.h>
#include <iostream>
#include <exception>
#include <iomanip>
#include <cstdlib>
#include <stdio.h>
#include "mraa.hpp"
#include "Timer.hpp"

using namespace std;


///////////////////////DECLARACION DE FUNCIONES//////////////////////////////////
void Driver();
int WriteCommand(char Com[]);
std::string ReadResponse();

///////////////////////DECLARACION DE VARIABLES//////////////////////////////////
mraa::Uart* SIM908;
char Msj[3]={'A','T','\r'};
std::string Respuesta;


//////////////////////INICIO PROGRAMA////////////////////////////////////////////
int main()
{

////////////////////////INICIALIZO PUERTO SERIE////////////////////////////////////
    try {
        SIM908 = new mraa::Uart(0);
    } catch (std::exception& e) {
        std::cout << e.what() << ", likely invalid platform config" << std::endl;
    }
    try {
        SIM908 = new mraa::Uart("/dev/ttyMFD1");
    } catch (std::exception& e) {
        std::cout << "Error while setting up raw UART, do you have a uart?" << std::endl;
        std::terminate();
    }
    if (SIM908->setBaudRate(9600) != mraa::SUCCESS) {
        std::cout << "Error setting parity on UART" << std::endl;
    }
    if (SIM908->setMode(8, mraa::UART_PARITY_NONE, 1) != mraa::SUCCESS) {
        std::cout << "Error setting parity on UART" << std::endl;
    }
    if (SIM908->setFlowcontrol(false, false) != mraa::SUCCESS) {
        std::cout << "Error setting flow control UART" << std::endl;
    }

/////////////////////////INICIALIZACION DE GPIO//////////////////////////////////

    mraa::Gpio* PowerKey;
    try {
        PowerKey = new mraa::Gpio(4);
    } catch (std::exception& e) {
        std::cout << e.what() << "Invalid GPIO" << std::endl;
    }
    int response = PowerKey->dir(mraa::DIR_OUT);
    if (response != MRAA_SUCCESS)
        mraa_result_print((mraa_result_t) MRAA_SUCCESS);
    PowerKey->write(0);


    mraa::Gpio* RI;
    try {
        RI = new mraa::Gpio(3);
    } catch (std::exception& e) {
        std::cout << e.what() << "Invalid GPIO" << std::endl;
    }
    response = RI->dir(mraa::DIR_IN);
    if (response != MRAA_SUCCESS)
        mraa_result_print((mraa_result_t) MRAA_SUCCESS);


    mraa::Gpio* DTR;
    try {
        DTR = new mraa::Gpio(2);
    } catch (std::exception& e) {
        std::cout << e.what() << "Invalid GPIO" << std::endl;
    }
    response = DTR->dir(mraa::DIR_OUT);
    if (response != MRAA_SUCCESS)
        mraa_result_print((mraa_result_t) MRAA_SUCCESS);
    DTR->write(0);

/////////////////////////ENCENDIDO DEL MODULO////////////////////////////////////

    char Continuar;
    cout << "Encender? (S/N)" << endl;
    cin >> Continuar;
    if(Continuar=='S')
    {
    	PowerKey->write(1);
		sleep(3);
		PowerKey->write(0);
    }

///////////////////////INICIALIZACION DE TIMER///////////////////////////////////
	if(start_timer(1000, &Driver))
	  {
	    printf("\n timer error\n");
	    return(1);
	  }

//////////////////////BUCLE DE PROGRAMA/////////////////////////////////////////
	while(true)
	{
	}
	delete PowerKey;
	delete DTR;
	delete RI;
	delete SIM908;
	return response;
}

void Driver(){
	WriteCommand(Msj);
	Respuesta=ReadResponse();
	cout << Respuesta << endl;
}
int WriteCommand(char Com[])
{
	char* Punt;
	for(unsigned int i=0;i<=sizeof(Com)-1;i++)
	{
		Punt=&Com[i];
		SIM908->write(Punt,1);
	}
	return sizeof(Com);
}
std::string ReadResponse()
{
	std::string Resp;
	if(SIM908->dataAvailable(1000))
		Resp = SIM908->readStr(64);
	return Resp;
}
