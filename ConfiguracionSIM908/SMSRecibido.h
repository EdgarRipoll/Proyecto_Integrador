/*
 * SMSRecibido.h
 *
 *  Created on: 20/03/2016
 *      Author: edgar
 */

#ifndef SMSRECIBIDO_H_
#define SMSRECIBIDO_H_

#include <DatosRecibidos.h>

class SMSRecibido: public DatosRecibidos {
public:
	SMSRecibido(std::string Datos);
	char*	getNroTelefono();
	//std::string	getMensajedeTexto();
	char*	getMensajedeTexto(int nroSMS);
	virtual ~SMSRecibido();
private:
	char*	NumerodeTelefono;
	//std::string	MensajeSMS;
	char*	MensajeSMS;
	char*	MensajeSMS2;
};

#endif /* SMSRECIBIDO_H_ */
