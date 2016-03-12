#include <unistd.h>
#include <iostream>
#include <exception>
#include <iomanip>
#include <cstdlib>
#include <stdio.h>
#include "mraa.hpp"
#include "Timer.hpp"

using namespace std;
mraa::Uart* SIM908;
void Driver();
int main()
{
	string Path;

////////////////////////INICIALIZO PUERTO SERIE////////////////////////////////////


    try {
        SIM908 = new mraa::Uart(0);
    } catch (std::exception& e) {
        std::cout << e.what() << ", likely invalid platform config" << std::endl;
    }
	Path = SIM908->getDevicePath();
	cout << Path<<endl;
    try {
        SIM908 = new mraa::Uart("/dev/ttyMFD1");
    } catch (std::exception& e) {
        std::cout << "Error while setting up raw UART, do you have a uart?" << std::endl;
        std::terminate();
    }
    if (SIM908->setBaudRate(115200) != mraa::SUCCESS) {
        std::cout << "Error setting parity on UART" << std::endl;
    }
    if (SIM908->setMode(8, mraa::UART_PARITY_NONE, 1) != mraa::SUCCESS) {
        std::cout << "Error setting parity on UART" << std::endl;
    }
    if (SIM908->setFlowcontrol(false, false) != mraa::SUCCESS) {
        std::cout << "Error setting flow control UART" << std::endl;
    }



	/*mraa::Uart* PC;
    try {
    	PC = new mraa::Uart("/dev/ttyGS0");
    } catch (std::exception& e) {
        std::cout << "Error while setting up raw UART, do you have a uart?" << std::endl;
        std::terminate();
    }
    if (PC->setBaudRate(115200) != mraa::SUCCESS) {
        std::cout << "Error setting parity on UART" << std::endl;
    }
    if (PC->setMode(8, mraa::UART_PARITY_NONE, 1) != mraa::SUCCESS) {
        std::cout << "Error setting parity on UART" << std::endl;
    }
    if (PC->setFlowcontrol(false, false) != mraa::SUCCESS) {
        std::cout << "Error setting flow control UART" << std::endl;
    }*/
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

///////////////////////DECLARACION DE VARIABLES//////////////////////////////////
	string Mensaje, Respuesta;
	char data[8];
	int longitud;


///////////////////////INICIALIZACION DE TIMER///////////////////////////////////
	if(start_timer(1000, &Driver))
	  {
	    printf("\n timer error\n");
	    return(1);
	  }

	while(true)
	{
			cout << SIM908->readStr(8) << endl;





		/*PC->writeStr("Escribir el mensaje");
		Mensaje = PC->readStr(8);
		SIM908->writeStr(Mensaje);
		if(SIM908->dataAvailable(1000))
		{
			Respuesta = SIM908->readStr(16);
			PC->writeStr(Respuesta);
			//cout << Respuesta << endl;
			longitud = SIM908->read(data,16);
			cout << longitud << endl;
			for(int i=0; i<=longitud; i++)
			{
				cout << data[i] << endl;
			}*/
		//}
	}
	delete PowerKey;
	delete DTR;
	delete RI;
	delete SIM908;
	return response;
}

void Driver(){
	SIM908->writeStr("AT");
	//cout << "AT" << endl;
}
