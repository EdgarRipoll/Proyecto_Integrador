/*
 * DatosRecibidos.cpp
 *
 *  Created on: 19/03/2016
 *      Author: edgar
 */

#include <DatosRecibidos.h>
#include <iostream>
#include <string>
DatosRecibidos::DatosRecibidos(std::string Datos){//: RawResponse(Datos) {
	// TODO Auto-generated constructor stub
	RawResponse = Datos;
	/*
	 * La trama devuelta por el módulo divide los mensajes a través de comas (",").
	 * Para decodificar la trama se necesita convertir el string en un array de char.
	 * La funcion c_str() returns a const char *; you aren't allowed to change the C-style string returned by c_str().
	 * To process it you'll have to copy it first:
	 */
	RespuestaCharConstante = RawResponse.c_str();
	RespuestaChar = new char[RawResponse.length() + 1];
	strcpy(RespuestaChar, RespuestaCharConstante);
	std::cout << RawResponse<<std::endl;
	tipo = NO_DECLARADO;
	IdentificarTipoRespuesta();
	Divisiones = 0;
	RespuestaCharConstante = NULL;
	RespuestaChar = NULL;
	token = NULL;
}

DatosRecibidos::~DatosRecibidos() {
	// TODO Auto-generated destructor stub
}

void	DatosRecibidos::setTipoRespuesta(tipo_de_Respuesta TipoMsj)
{
	tipo = TipoMsj;
}
tipo_de_Respuesta	DatosRecibidos::getTipoRespuesta()
{
	return tipo;
}
void	DatosRecibidos::setNroDivisiones(int nroTokens)
{
	Divisiones = nroTokens;
}
int	DatosRecibidos::getNroDivisiones()
{
	return Divisiones;
}
std::string	DatosRecibidos::getRawResponse()
{
	return RawResponse;
}
void	DatosRecibidos::setRawResponse(std::string& Msj)
{
	RawResponse = Msj;
}
const char*	DatosRecibidos::getRespuestaCharConstante()
{
	return	RespuestaCharConstante;
}
char*	DatosRecibidos::getRespuestaChar()
{
	return	RespuestaChar;
}
std::string	DatosRecibidos::getToken(int NroParticion)
{
	return Particion[NroParticion];
}
char*	DatosRecibidos::convertString2Char(std::string& texto)
{
	char *Charconvertido = new char[texto.length() + 1];
	strcpy(Charconvertido, texto.c_str());
	return Charconvertido;
}
char*	DatosRecibidos::getTokenChar(int NroParticion)
{
	return convertString2Char(Particion[NroParticion]);
}
void	DatosRecibidos::IdentificarTipoRespuesta()
{
	//std::string comparar = Respuesta->getToken(0);
	token = strtok(RespuestaChar, ",");
	Particion[0]=token;
	if(Particion[0] == "+CMGR: \"REC UNREAD\"")
		tipo = SMS;
	if((Particion[0] == "+CMTI: \"SM\"")||(Particion[0]=="OK")||(Particion[0]=="ERROR"))
		tipo = COMANDO;
	if(Particion[0] == "32")
		tipo = GPS;
	std::cout << tipo<<std::endl;
}
void	DatosRecibidos::OrganizaTrama(const char* Separador)
{
	token = strtok(RespuestaChar, Separador);
	while(token != NULL)
	{
		Particion[Divisiones]=token;
		token = strtok(NULL, Separador);
		Divisiones++;
	}
}

