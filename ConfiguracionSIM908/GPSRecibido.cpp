/*
 * GPSRecibido.cpp
 *
 *  Created on: 20/03/2016
 *      Author: edgar
 */

#include <GPSRecibido.h>

GPSRecibido::GPSRecibido(std::string Datos) : DatosRecibidos(Datos) {
	// TODO Auto-generated constructor stub

}

GPSRecibido::~GPSRecibido() {
	// TODO Auto-generated destructor stub
}
char*	GPSRecibido::getRawLatitud()
{
	return	this->getTokenChar(3);
}
char*	GPSRecibido::getRawLongitud()
{
	return	this->getTokenChar(5);
}
std::string	GPSRecibido::getN_SIndicator()
{
	return this->getToken(4);
}
std::string	GPSRecibido::getE_WIndicator()
{
	return this->getToken(6);
}
void	GPSRecibido::DecoNMEA()//char latitud[], char longitud[])
{
	char* Lat2;// = convertString2Char(Particion[4]);	//token[4];
	char* Lon2;// = convertString2Char([6]);	//token[6];
	char latim[9];
	char longm[9];
	float	latimf;
	float	longmf;

	 if(getN_SIndicator() == "N") //Particion[4]
		 latitud[0]=' ';
	 if(getN_SIndicator() == "S")
		 latitud[0]='-';

	 if(getE_WIndicator() == "E") //Particion[6]
		 longitud[0]=' ';
	 if(getE_WIndicator() == "W")
		 longitud[0]='-';

	 //strcpy(Lat2,convertString2Char(this->Particion[4]));
	 Lat2 = getRawLatitud();//this->getTokenChar(3);
	 //strcpy(Lon2,convertString2Char(this->Particion[6]));
	 Lon2 = getRawLongitud();//this->getTokenChar(5);
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
char*	GPSRecibido::getLinkGoogle()//char latitud[], char longitud[])
{
	sprintf(linkgoogle,"https://maps.google.com/maps?q=%s,%s\r",latitud,longitud);
	return	linkgoogle;
}
