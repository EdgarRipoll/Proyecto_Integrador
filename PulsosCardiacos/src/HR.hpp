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
	bool	getCambioVector();
	void	ProcesarSenal();
	int		getProcesamiento(int index);
	int		getRaw(int index);
	int		getIndex(int index);
	int		getContador();
	virtual ~HR();
private:
	void	FiltroPB();
	void	BuscarHB();
//	void	Normalizar();
//	void	SquaringFunction();
	int	LecturaPulsaciones[2][500];	//Es un vector que guarda los valores del pin analógico. La frecuencia de muestreo es de
									//5ms por lo que 500 valores equivalen a 2.5s de medicion
									//Se divide en dos vectores para poder realizar los calculos necesarios y mientras se siguen registrando
									//nuevas mediciones
	int	ContadorMediciones;		//Va llevando la cuenta de cuantas mediciones se van realizando, cuando llega a 500 cambia de vector de
								//destino
	bool	VectorSeleccionado;	//Es un flag que me indica en que vector guardar los valores medidos
	int		Procesamiento[510];
	bool	CambioVector;		//Es un flag que me indica el momento en que se produce el cambio del vector
	unsigned long	sampleCounter;	// used to determine pulse timing
	int	rate[10];	// array to hold last ten IBI values
	unsigned long	lastBeatTime;	// used to find IBI
	int	P;	// used to find peak in pulse wave, seeded
	int	T;	// used to find trough in pulse wave, seeded
	int	thresh;	// used to find instant moment of heart beat, seeded
	int	amp;	// used to hold amplitude of pulse waveform, seeded
	bool	firstBeat;	// used to seed rate array so we startup with reasonable BPM
	bool	secondBeat;	// used to seed rate array so we startup with reasonable BPM
	int IBI;	// int that holds the time interval between beats! Must be seeded!
	bool Pulse;	// "True" when User's live heartbeat is detected. "False" when not a "live beat"
	int BPM;	// int that holds raw Analog in 0. updated every 5mS
	bool QS;	// becomes true when finds a beat.
	int	index[500];
	int indexTotal;
	int contador2;
};

#endif /* HR_HPP_ */
