/*
 * SMSRecibido.cpp
 *
 *  Created on: 20/03/2016
 *      Author: edgar
 */

#include <SMSRecibido.h>

SMSRecibido::SMSRecibido(std::string Datos) : DatosRecibidos(Datos) {
	// TODO Auto-generated constructor stub
	NumerodeTelefono = this->getTokenChar(3);
	MensajeSMS = this->getTokenChar(8);
	//MensajeSMS = this->getToken(4);
}

SMSRecibido::~SMSRecibido() {
	// TODO Auto-generated destructor stub
}
char*	SMSRecibido::getNroTelefono()
{
	return	NumerodeTelefono;
}
//std::string	SMSRecibido::getMensajedeTexto()
char*	SMSRecibido::getMensajedeTexto()
{
	return	MensajeSMS;
}
