#include "Variables.h"

void Timer_Int();
int WriteCommand(char Com[]);
std::string ReadResponse();
void signal_handler_IO (int status);   /* definition of signal handler */
//void InterpretaDatos();
void EnviaSalud();
void EnviaSMS(char sms[], char telefono[]);
//void DecoNMEA();
//void OrganizaTrama(std::string Respuesta);

void Timer_Int(){
	WriteCommand(Msj);
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
void signal_handler_IO (int status)
{
	DatosSIM908 = ReadResponse();
/*	Respuesta = new DatosRecibidos();
	Respuesta->setRawResponse(ReadResponse());
	//Respuesta=ReadResponse();
	std::cout << Respuesta->getRawResponse();
*/
	RecibeDatos=1;
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
*/
void EnviaSMS (char sms[], char telefono[]){
	char	Destino[24];
    char	end[2];
    end[0] = 0x1a;
    end[1] = '\0';
	WriteCommand(ModoText);            //modo texto
	sprintf(&Destino[0],"AT+CMGS=\"%s\"\r\n",telefono);  //numero de destino
	WriteCommand(Destino);
	WriteCommand(sms);  //mensaje a enviar
	WriteCommand(end);                  //crl-z para enviar el mensaje
}
void EnviaSalud()
{

}
