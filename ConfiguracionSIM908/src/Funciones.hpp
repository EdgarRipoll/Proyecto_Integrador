#include "Variables.h"
#include <stdlib.h>
void Timer_Int();
//int WriteCommand(char Com[]);
//std::string ReadResponse();
void signal_handler_IO (int status);   /* definition of signal handler */
//void InterpretaDatos();
void EnviaSalud();
//void EnviaSMS(char sms[], char telefono[]);
//void DecoNMEA();
//void OrganizaTrama(std::string Respuesta);

void Timer_Int(){
	if(delay)
	{
		cont++;
		if(cont>2)
		{
			delay=0;
			cont=0;
		}
	}/*
	cont2++;
	if(cont2>3)
	{
		cont=0;
		SIM908->WriteCommand(Msj);
		//puts("AT+CGPSINF=32");
		//SIM908->WriteCommand(Msj2);
		delay=0;
	}*/

	//SIM908->WriteCommand(Msj);
}
/*
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
*/
void signal_handler_IO (int status)
{
	if(!delay)
	{
		SIM908->ReadResponse();
		//std::cout <<"DatosSIM1: "<< SIM908->getDatosSIM() <<" :DatosSIM1"<<std::endl;
		delay=1;
	}
	//SIM908->setRecibeDato();
/*	Respuesta = new DatosRecibidos();
	Respuesta->setRawResponse(ReadResponse());
	//Respuesta=ReadResponse();
	std::cout << Respuesta->getRawResponse();
*/
	//RecibeDatos=1;
	//std::cout << DatosSIM908;
}
/*
void InterpretaDatos()
{
	std::string comparar = Respuesta->getToken(0);
	if(comparar == "+CMGR: \"REC UNREAD\"")
	{
		Respuesta->setTipoRespuesta(SMS);
	}
	if((comparar == "+CMTI: \"SM\"")||(comparar=="OK")||(comparar=="ERROR"))
	{
		Respuesta->setTipoRespuesta(COMANDO);
	}
	if(comparar == "32")
	{
		Respuesta->setTipoRespuesta(GPS);
	}
}

void EnviaSMS (char sms[], char telefono[]){
	char	Destino[24];
    char	end[2];
    end[0] = 0x1a;
    end[1] = '\0';
	WriteCommand(ModoText);            //modo texto
	sprintf(Destino,"AT+CMGS=\"%s\"\r\n",telefono);  //numero de destino
	WriteCommand(Destino);
	WriteCommand(sms);  //mensaje a enviar
	WriteCommand(end);                  //crl-z para enviar el mensaje
}
*/
void EnviaSalud()
{

}
