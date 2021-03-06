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
	Divisiones = 0;
	RespuestaCharConstante = NULL;
	RespuestaChar = NULL;
	token = NULL;

	RespuestaCharConstante = RawResponse.c_str();
	RespuestaChar = new char[RawResponse.length() + 1];
	strcpy(RespuestaChar, RespuestaCharConstante);

	OrganizaTrama();
	IdentificarTipoRespuesta();
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
	char *Compare = this->convertString2Char(Particion[0]);

	if(strstr(Compare, "+CMGR:") != NULL)
		tipo = SMS;

	if((strstr(Compare, "+CMTI:") != NULL) || (strstr(Compare, "OK") != NULL) || (strstr(Compare, "ERROR") != NULL))
		tipo = COMANDO;

	if((strstr(Compare, "32") != NULL))
		tipo = GPS;
	std::cout <<"Tipo: "<< tipo<<"\n";
}
void	DatosRecibidos::OrganizaTrama()
{

	token = strtok(RespuestaChar," ,\"\r\n-");
	while(token != NULL)
	{
		Particion[Divisiones]=token;
		token = strtok(NULL, " ,\"\r\n-");
		Divisiones++;
	}
}
std::string	DatosRecibidos::getIndexSMS()
{
	return this->getToken(2);
}
