/*
 * GPSRecibido.h
 *
 *  Created on: 20/03/2016
 *      Author: edgar
 */

#ifndef GPSRECIBIDO_H_
#define GPSRECIBIDO_H_

#include <DatosRecibidos.h>

class GPSRecibido: public DatosRecibidos {
public:
	GPSRecibido(std::string Datos);
	virtual ~GPSRecibido();
	void	DecoNMEA();//char latitud[], char longitud[]);
	char*	getLinkGoogle();//char latitud[], char longitud[]);
	char*	getRawLatitud();
	char*	getRawLongitud();
	std::string	getN_SIndicator();
	std::string	getE_WIndicator();
private:
	char	linkgoogle[54];
	char	latitud[11];
	char	longitud[11];
};

#endif /* GPSRECIBIDO_H_ */
