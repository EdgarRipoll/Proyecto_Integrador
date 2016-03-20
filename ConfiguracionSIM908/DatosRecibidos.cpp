/*
 * DatosRecibidos.cpp
 *
 *  Created on: 19/03/2016
 *      Author: edgar
 */

#include <DatosRecibidos.h>

DatosRecibidos::DatosRecibidos(std::string Datos) {
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
void	DatosRecibidos::setRawResponse(std::string Msj)
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
char*	DatosRecibidos::convertString2Char(std::string texto)
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
void	DatosRecibidos::DecoNMEA(char latitud[], char longitud[])
{
	char Lat2[11];// = convertString2Char(Particion[4]);	//token[4];
	char Lon2[11];// = convertString2Char(Particion[6]);	//token[6];
	char latim[9];
	char longm[9];
	float	latimf;
	float	longmf;
	 switch(token[4]){
		   case 'N':	latitud[0]=' ';
						break;
		   case 'S':	latitud[0]='-';
						break;
	 }
	 switch(token[6]){
		   case 'E':longitud[0]=' ';
					break;
		   case 'W':longitud[0]='-';
					break;
	 }
	 strcpy(Lat2,convertString2Char(Particion[4]));
	 strcpy(Lon2,convertString2Char(Particion[6]));
	 strncpy(latim,&Lat2[2],9);
	 strncpy(longm,&Lon2[2],9);
	 latimf=(atof(latim))/60;
	 longmf=(atof(longm))/60;

	 sprintf(&latitud[2],"%.6f",latimf);;
	 latitud[1]=Lat2[0];
	 latitud[2]=Lat2[1];

	 sprintf(&longitud[2],"%.6f",longmf);
	 longitud[1]=Lon2[0];
	 longitud[2]=Lon2[1];
}
char*	DatosRecibidos::getLinkGoogle(char latitud[], char longitud[])
{
	char	linkgoogle[54];
	sprintf(linkgoogle,"https://maps.google.com/maps?q=%s,%s\r",latitud,longitud);
	return	linkgoogle;
}
