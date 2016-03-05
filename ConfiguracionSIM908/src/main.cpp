#include <unistd.h>
#include <iostream>
#include <exception>
#include <iomanip>
#include <cstdlib>
#include <stdio.h>
#include "mraa.hpp"

using namespace std;

int main()
{
	mraa::Uart* SIM908;
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
    if (SIM908->setBaudRate(115200) != mraa::SUCCESS) {
        std::cout << "Error setting parity on UART" << std::endl;
    }
    if (SIM908->setMode(8, mraa::UART_PARITY_NONE, 1) != mraa::SUCCESS) {
        std::cout << "Error setting parity on UART" << std::endl;
    }
    if (SIM908->setFlowcontrol(false, false) != mraa::SUCCESS) {
        std::cout << "Error setting flow control UART" << std::endl;
    }

    string Mensaje, Respuesta;
    while(true)
    {
		cout << "Presione una tecla" << endl;
		cin >> Mensaje;
		SIM908->writeStr(Mensaje);
    }

}
