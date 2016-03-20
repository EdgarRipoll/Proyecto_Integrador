/*
 * DatosRecibidos.h
 *
 *  Created on: 19/03/2016
 *      Author: edgar
 */

#ifndef DATOSRECIBIDOS_H_
#define DATOSRECIBIDOS_H_

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
/**
 * Enum representing different possible tipos de Respuestas.
 */
typedef enum {
    NO_DECLARADO = 0,
	COMANDO = 1,     //
    SMS	=	2,
    GPS	=	3,
    FINAL_tipo_de_Respuesta_ENTRY = 4
} tipo_de_Respuesta;

class DatosRecibidos {
public:
	DatosRecibidos(std::string Datos);
	virtual ~DatosRecibidos();
	void	setTipoRespuesta(tipo_de_Respuesta TipoMsj);
	void	setNroDivisiones(int nroTokens);
	void	setRawResponse(std::string Msj);
	void	OrganizaTrama(const char* Separador);
	void	IdentificarTipoRespuesta();
	int		getNroDivisiones();
	const char*	getRespuestaCharConstante();
	char*	getRespuestaChar();
	char*	getTokenChar(int NroParticion);
	tipo_de_Respuesta getTipoRespuesta();
	std::string		getRawResponse();
	std::string		getToken(int NroParticion);
private:
	char*	convertString2Char(std::string texto);
	tipo_de_Respuesta tipo;
	int Divisiones; //cantidad de tokens que tiene la trama recibida
	std::string RawResponse;
	const char *RespuestaCharConstante;
	char *RespuestaChar;
	char *token;
	std::string Particion[15];
};

#endif /* DATOSRECIBIDOS_H_ */
