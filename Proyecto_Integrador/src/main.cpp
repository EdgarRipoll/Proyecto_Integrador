#include "Funciones.hpp"
#include <iostream>
#include <string>
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


/////////////////////////INICIALIZACION DE GPIO//////////////////////////////////

    mraa::Gpio* PowerKey;
    try {
        PowerKey = new mraa::Gpio(10);
    } catch (std::exception& e) {
        std::cout << e.what() << "Invalid GPIO" << std::endl;
    }
    int response = PowerKey->dir(mraa::DIR_OUT);
    if (response != MRAA_SUCCESS)
        mraa_result_print((mraa_result_t) MRAA_SUCCESS);
    PowerKey->write(0);


    mraa::Gpio* RI;
    try {
        RI = new mraa::Gpio(13);
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

////////////////////////INICIALIZO PUERTO SERIE////////////////////////////////////

    SIM908 = new ModuloSIM("/dev/ttyMFD1",115200);

/////////////////////////ENCENDIDO DEL MODULO////////////////////////////////////

    char Continuar;
    cout << "Encender? (S/N)" << endl;
    cin >> Continuar;
    if(Continuar=='S')
    {
    	PowerKey->write(1);
    	sleep(3);
		PowerKey->write(0);
		sleep(15);
		do{
			sleep(1);
			std::cout<<"Iniciando...\n";
			SIM908->WriteATCommand("AT\r");
			SIM908->ReadResponse();
			Respuesta = new DatosRecibidos(SIM908->getDatosSIM());
		}while(strstr(Respuesta->getRespuestaChar(),"OK") == NULL);
		std::cout<<"INICIADO...\n";
		sleep(3);
		SIM908->WriteATCommand("ATE0\r");
		sleep(3);
		SIM908->WriteATCommand("AT+CGPSPWR=1\r");
		sleep(3);
		SIM908->WriteATCommand("AT+CGPSRST=1\r");
		sleep(3);
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
	if(start_timer(500, &Timer_Int))
	  {
	    printf("\n timer error\n");
	    return(1);
	  }

//////////////////////BUCLE DE PROGRAMA/////////////////////////////////////////
	sleep(2);
	SIM908->WriteATCommand("AT\r");

	while(true)
	{

		if(SIM908->getRecibeDato())
		{
			std::cout << "entre"<<"\n";
			SIM908->ResetRecibeDato();
			std::cout <<"RecibeDato: "<< SIM908->getRecibeDato()<<"\n";
			cout <<"DatosSIM: "<< SIM908->getDatosSIM() <<" :DatosSIM"<<endl;
			Respuesta = new DatosRecibidos(SIM908->getDatosSIM());
			std::cout << "sali"<<std::endl;
			std::cout <<"Token: "<< Respuesta->getToken(0)<<"\n";
			std::cout <<"Token1: "<< Respuesta->getToken(1)<<"\n";
			std::cout <<"Token2: "<< Respuesta->getToken(2)<<"\n";
			switch	(Respuesta->getTipoRespuesta()){
				case COMANDO:
								if(strstr(Respuesta->getRespuestaChar(),"+CMTI:") != NULL)
									{
									LeerSMS = "AT+CMGR=" + Respuesta->getIndexSMS() + "\r";

									LeaSMS=1;
									SIM908->WriteATCommand(LeerSMS);
									std::cout <<"Switch1: "<< Respuesta->getToken(0)<<"\n";
									}
								if(strstr(Respuesta->getTokenChar(0),"OK") != NULL || strstr(Respuesta->getTokenChar(0),"ERROR") != NULL  )
									std::cout <<"Switch2: "<< Respuesta->getToken(0)<<"\n";
								break;
				case SMS:	LeaSMS=0;
							MensajeRecibido = new SMSRecibido(SIM908->getDatosSIM());
							std::cout <<"MSJ: "<< MensajeRecibido->getMensajedeTexto(1)<<"\n";
							std::cout <<"MSJ: "<< MensajeRecibido->getMensajedeTexto(0)<<"\n";
							std::cout <<"Tel: "<< MensajeRecibido->getNroTelefono() <<"\n";
							if((strstr(MensajeRecibido->getMensajedeTexto(1), "Ubicacion") != NULL) || (strstr(MensajeRecibido->getMensajedeTexto(0), "Ubicacion") != NULL))
							{
								PideUbicacion=1;
								std::cout<<"PideUbicacion1: " << PideUbicacion << "\n";
								SIM908->WriteATCommand(PedirUbicacion);
								std::cout <<"Switch3"<<"\n";
							}
							if((strstr(MensajeRecibido->getMensajedeTexto(1), "Salud") != NULL) || (strstr(MensajeRecibido->getMensajedeTexto(0), "Salud") != NULL))
								EnviaSalud();
							break;

				case GPS:	PideUbicacion=0;
							std::cout<<"PideUbicacion2: " << PideUbicacion << "\n";
							DatosGPS = new	GPSRecibido(SIM908->getDatosSIM());
							std::cout <<"Switch4"<<"\n";
							DatosGPS->DecoNMEA();
							std::cout <<"Switch5 "<< DatosGPS->getLinkGoogle() <<"\n";
							SIM908->EnviaSMS(DatosGPS->getLinkGoogle(), MensajeRecibido->getNroTelefono());
							std::cout <<"Switch6"<<"\n";
							break;
			}
		}
	}
	delete PowerKey;
	delete DTR;
	delete RI;
	delete SIM908;
	delete Respuesta;
	delete MensajeRecibido;
	delete DatosGPS;
	return response;
}




