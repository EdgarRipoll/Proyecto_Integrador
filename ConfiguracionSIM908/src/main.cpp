#include "Funciones.hpp"

using namespace std;


///////////////////////DECLARACION DE FUNCIONES//////////////////////////////////

///////////////////////DECLARACION DE VARIABLES//////////////////////////////////

//////////////////////INICIO PROGRAMA////////////////////////////////////////////
int main()
{
    fd = open("/dev/ttyMFD1",O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1)
    {
       perror("open_port: Unable to open /dev/ttyO1\n");
       exit(1);
    }

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

///////////////////////INICIALIZACION DE INTERRUPCION SERIAL//////////////////////
    saio.sa_handler = signal_handler_IO;
    saio.sa_flags = 0;
    saio.sa_restorer = NULL;
    sigaction(SIGIO,&saio,NULL);

    fcntl(fd, F_SETFL, FNDELAY);
    fcntl(fd, F_SETOWN, getpid());
    fcntl(fd, F_SETFL,  O_ASYNC );
///////////////////////INICIALIZACION DE TIMER///////////////////////////////////
	if(start_timer(1000, &Timer_Int))
	  {
	    printf("\n timer error\n");
	    return(1);
	  }

//////////////////////BUCLE DE PROGRAMA/////////////////////////////////////////
	while(true)
	{
		if(RecibeDatos)
		{
			RecibeDatos=0;
			//OrganizaTrama(Respuesta);
			Respuesta = new DatosRecibidos(DatosSIM908);
			std::cout << Respuesta->getRawResponse();
			//Respuesta->OrganizaTrama(Separador);
			//InterpretaDatos();
			switch	(Respuesta->getTipoRespuesta()){
				case COMANDO:	if((Respuesta->getToken(0) == "+CMTI: \"SM\""))
									WriteCommand(LeerSMS);
								break;

				case SMS:	MensajeRecibido = new SMSRecibido();
							if(MensajeRecibido->getToken(5) == "Ubicación")
								WriteCommand(PedirUbicacion);
							if(MensajeRecibido->getToken(5) == "Salud")
								EnviaSalud();
							break;

				case GPS:	DatosGPS = new	GPSRecibido();
							DatosGPS->DecoNMEA(latitud,longitud);
							//linkgoogle = Respuesta->getLinkGoogle(latitud,longitud);
							//telefono = Respuesta->getTokenChar(1);
							EnviaSMS(DatosGPS->getLinkGoogle(latitud,longitud), MensajeRecibido->getTokenChar(1));
							break;
			}
		}
	}
	delete PowerKey;
	delete DTR;
	delete RI;
	delete SIM908;
	return response;
}
