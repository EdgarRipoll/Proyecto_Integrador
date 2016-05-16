/*
 * ModuloSIM.h
 *
 *  Created on: 20/03/2016
 *      Author: edgar
 */

#ifndef MODULOSIM_H_
#define MODULOSIM_H_

#include <uart.hpp>
#include <iostream>
class ModuloSIM: public mraa::Uart {
public:
	ModuloSIM(std::string ttyPath, int Baudrate);
	virtual ~ModuloSIM();
	int WriteCommand(char Com[]);
	void ReadResponse();
	void EnviaSMS (char sms[], char telefono[]);
	bool getRecibeDato();
	void ResetRecibeDato();
	void setRecibeDato();
	std::string getDatosSIM();
private:
	char	endSMS[2];
	bool	RecibeDato;
	std::string DatosSIM;
};

#endif /* MODULOSIM_H_ */
