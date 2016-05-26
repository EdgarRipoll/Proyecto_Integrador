/*
 * HR.hpp
 *
 *  Created on: 26/05/2016
 *      Author: edgar
 */

#ifndef HR_HPP_
#define HR_HPP_

#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include "Sensor.hpp"

class HR: public Array_Sensor{
public:
	HR(int pin);
	void	getMedicion();
	int		getContadorMediciones();
	bool	getVector();
	virtual ~HR();
private:
	void	Derivative();
	void	Normalizar();
	void	SquaringFunction();
	int	LecturaPulsaciones[2][500];	//Es un vector que guarda los valores del pin analógico. La frecuencia de muestreo es de
									//5ms por lo que 500 valores equivalen a 2.5s de medicion
									//Se divide en dos vectores para poder realizar los calculos necesarios y mientras se siguen registrando
									//nuevas mediciones
	int	ContadorMediciones;		//Va llevando la cuenta de cuantas mediciones se van realizando, cuando llega a 500 cambia de vector de
								//destino
	bool	VectorSeleccionado;	//Es un flag que me indica en que vector guardar los valores medidos
	float	Procesamiento[504];
};

#endif /* HR_HPP_ */
