/*
 * ModuloSIM.cpp
 *
 *  Created on: 20/03/2016
 *      Author: edgar
 */

#include <ModuloSIM.h>

ModuloSIM::ModuloSIM(std::string ttyPath, int Baudrate) : mraa::Uart(ttyPath) {
	// TODO Auto-generated constructor stub
/*    try {
        SIM908 = new mraa::Uart("/dev/ttyMFD1");
    } catch (std::exception& e) {
        std::cout << "Error while setting up raw UART, do you have a uart?" << std::endl;
        std::terminate();
    }
*/
    if (this->setBaudRate(Baudrate) != mraa::SUCCESS) {
        std::cout << "Error setting parity on UART" << std::endl;
    }
    if (this->setMode(8, mraa::UART_PARITY_NONE, 1) != mraa::SUCCESS) {
        std::cout << "Error setting parity on UART" << std::endl;
    }
    if (this->setFlowcontrol(false, false) != mraa::SUCCESS) {
        std::cout << "Error setting flow control UART" << std::endl;
    }

    endSMS[0] = 0x1a;
    endSMS[1] = '\0';
    RecibeDato = 0;
}

ModuloSIM::~ModuloSIM() {
	// TODO Auto-generated destructor stub
}
/*
int ModuloSIM::WriteCommand(char Com[])
{
	char* Punt;
	for(unsigned int i=0;i<=sizeof(Com)-1;i++)
	{
		Punt=&Com[i];
		this->write(Punt,1);
	}
	return sizeof(Com);
}*/
void	ModuloSIM::WriteATCommand(std::string Datos)
{
	bool ATdeshabilitado1=1;
	do
		{
		if(!this->dataAvailable(200))
			{
			ATdeshabilitado1=0;
			this->writeStr(Datos);
			}
		}while(ATdeshabilitado1);
}
//std::string ModuloSIM::ReadResponse()
void ModuloSIM::ReadResponse()
{
	std::string Resp;
	if(this->dataAvailable(1000))
		Resp = this->readStr(100);
	//return Resp;
	//if(Resp.compare("") || Resp.compare("\n") || Resp.compare("\r"))//Resp != "" )
	if((Resp != "\0") && (Resp.compare(2, 1, ">") != 0))//(Resp != ">"))//||(Resp != "")||(Resp != " ")||(Resp != "\r")||(Resp != "\n"))
	{
		DatosSIM = Resp;
		RecibeDato = 1;
		std::cout<<"Hola: " << DatosSIM <<"\n";
	}
	else{
		std::cout<<"Era un 0";
	}
	/*
	DatosSIM = Resp;
	this->setRecibeDato();

	std::cout<<"Hola: " << Resp <<"\n";*/
}
void ModuloSIM::EnviaSMS (char sms[], char telefono[])
{
	char	Destino[24];
/*	char	ModoText[] = "AT+CMGF=1\r\n";
	WriteCommand(ModoText);            //modo texto*/
	std::cout<< "SMS: " <<sms<<"\n";
	sprintf(Destino,"AT+CMGS=\"%s\"\r\n",telefono);  //numero de destino
	//WriteCommand(Destino);
	//WriteCommand(sms);  //mensaje a enviar
	//WriteCommand(endSMS);                  //crl-z para enviar el mensaje
/*	this->writeStr(Destino);
	this->writeStr(sms);  //mensaje a enviar
	this->writeStr(endSMS);//crl-z para enviar el mensaje*/
	this->WriteATCommand(Destino);
	this->WriteATCommand(sms);
	this->WriteATCommand(endSMS);
}
bool ModuloSIM::getRecibeDato()
{
	return RecibeDato;
}
void ModuloSIM::ResetRecibeDato()
{
	RecibeDato = 0;
}
void ModuloSIM::setRecibeDato()
{
	RecibeDato = 1;
}
std::string ModuloSIM::getDatosSIM()
{
	return DatosSIM;
}
