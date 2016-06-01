/*
 * HR.cpp
 *
 *  Created on: 26/05/2016
 *      Author: edgar
 */

#include <src/HR.hpp>

HR::HR(int pin) : Array_Sensor(pin) {
	// TODO Auto-generated constructor stub
	ContadorMediciones=0;
	VectorSeleccionado=0;
	CambioVector=0;
	sampleCounter=0;
	lastBeatTime = 0;
	P = 512;
	T = 512;
	thresh = 525;
	amp = 100;
	firstBeat = 1;
	secondBeat = 0;
	Pulse = 0;
	QS = 0;
	BPM = 0;
	IBI = 600;
	indexTotal = 0;
	contador2 = 0;
}

HR::~HR() {
	// TODO Auto-generated destructor stub
}

void	HR::getMedicion(){

	LecturaPulsaciones[VectorSeleccionado][ContadorMediciones] = 1023 - this->getRawValue();
	ContadorMediciones++;
	if(ContadorMediciones >= 500)
		{
		ContadorMediciones=0;
		VectorSeleccionado = !VectorSeleccionado;
		CambioVector=1;
		}
}

int		HR::getContadorMediciones()
{
	return	ContadorMediciones;
}

bool	HR::getVector()
{
	return	VectorSeleccionado;
}

/*
 * Derivative filter H(z) = (1/8T)(-z^(-2) - 2z^(-1) + 2z + z^(2))
 * Luego se normaliza el array.
 */
/*
void	HR::FiltroPB()
{
	float	DerivativeTF[5]={-0.2 , -0.4 , 0 , 0.4 , 0.2 };	//Five-pont derivative H(z)= (1/8 T)*(-z^-2 - 2z^-1 + 2z + z^2)
	size_t n;

	for (n = 0; n < 504; n++)
	{
	size_t kmin, kmax, k;

	Procesamiento[n] = 0;

	kmin = (n >= 4) ? n - 4 : 0;	//4 es el (sizeof(DerivativeTF)-1)
	kmax = (n < 499) ? n : 499;		//499 es el (sizeof(LecturaPulsaciones)-1)

	for (k = kmin; k <= kmax; k++)
		Procesamiento[n] += LecturaPulsaciones[!VectorSeleccionado][k] * DerivativeTF[n - k];
	}
}
*/

/*
 * %% Low Pass Filter  H(z) = ((1 - z^(-6))^2)/(1 - z^(-1))^2
 * b = [1 0 0 0 0 0 -2 0 0 0 0 0 1];
 * a = [1 -2 1];
 * h_l = filter(b,a,[1 zeros(1,12)]);
 */

void	HR::FiltroPB()
{
	int	FiltroPB[11]={1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1};	//Respuesta al impulso del Filtro pasa bajo

	int i1 , tmp;
	//convolution process
	for (int i=0; i<510; i++)
	{
		i1 = i;
		tmp = 0;
		for (int j=0; j<500; j++)
		{
			if(i1>=0 && i1<11)
				tmp += (LecturaPulsaciones[!VectorSeleccionado][j]*FiltroPB[i1]);
			i1 = i1-1;
			Procesamiento[i] = tmp;
		}
	}




	/*
	size_t n;

	for (n = 0; n < 510; n++)
	{
		size_t kmin, kmax, k;

		if(!n)
			Procesamiento[n] = Procesamiento[509];
		else
			Procesamiento[n] = 0;

		kmin = (n >= 10) ? (n - 10) : 0;	//10 es el (sizeof(FiltroPB)-1)
		kmax = (n < 499) ? n : 499;		//499 es el (sizeof(LecturaPulsaciones)-1)

		for (k = kmin; k <= kmax; k++)
			Procesamiento[n] += LecturaPulsaciones[!VectorSeleccionado][k] * FiltroPB[n - k];
	}
	*/
}
/*
void	HR::Normalizar()
{
	/*
	float max_value=0.0;
	max_value = *std::max_element(Procesamiento,Procesamiento+504); //504 es el (sizeof(Procesamiento))
	for(int i=0 ; i<=503 ; i++) //503 es el (sizeof(Procesamiento)-1)
		Procesamiento[i] /= max_value;
	*/
/*
	float average = 0.0, sum = 0.0;
	for(int i = 0; i <= 503; i++){ //503 es el (sizeof(Procesamiento)-1)
	    sum += Procesamiento[i];
	}
	average = sum / 503;
	for(int j=0 ; j<=503 ; j++) //503 es el (sizeof(Procesamiento)-1)
		if(Procesamiento[j]!=0)
			Procesamiento[j] /= average;
}
*/
/*
void	HR::SquaringFunction()
{
	for(int i=0 ; i<=503 ; i++) //503 es el (sizeof(Procesamiento)-1)
		Procesamiento[i] = pow(Procesamiento[i],2.0);
}
*/
bool	HR::getCambioVector()
{
	if(CambioVector)
	{
		CambioVector=0;
		return 1;
	}else
		return 0;
}

void	HR::ProcesarSenal()
{
	//this->FiltroPB();
	this->BuscarHB();
	//this->Normalizar();
//	this->SquaringFunction();
}

int		HR::getProcesamiento(int index)
{
	return	Procesamiento[index];
}

int		HR::getRaw(int index)
{
	return	LecturaPulsaciones[!VectorSeleccionado][index];
}

int		HR::getIndex(int index)
{
	return	this->index[index];
}

int		HR::getContador()
{
	return	contador2;
}

void	HR::BuscarHB()
{
	std::cout<<"SampleCounter: "<< sampleCounter<<"\n";
	std::cout<<"IBI: "<< IBI<<"\n";
	contador2=0;
	bool aumento_senal=0;
	bool PosiblePulso=0;
	int	indexPicos=0;
	for(int i=0 ; i<=499 ; i++)
		{
		sampleCounter += 5;	// keep track of the time in mS with this variable
		int N = sampleCounter - lastBeatTime;	// monitor the time since the last beat to avoid noise

		//  find the peak and trough of the pulse wave
		if(LecturaPulsaciones[!VectorSeleccionado][i] < thresh && N > ((IBI*3)/5))	// avoid dichrotic noise by waiting 3/5 of last IBI
			if (LecturaPulsaciones[!VectorSeleccionado][i] < T)	// T is the trough
				T = LecturaPulsaciones[!VectorSeleccionado][i];	// keep track of lowest point in pulse wave

		if(LecturaPulsaciones[!VectorSeleccionado][i] < 0.95*P && aumento_senal==1)
		{
			PosiblePulso=1;
			aumento_senal = 0;
		}

		if(LecturaPulsaciones[!VectorSeleccionado][i] > thresh && LecturaPulsaciones[!VectorSeleccionado][i] > P){	// thresh condition helps avoid noise
			P = LecturaPulsaciones[!VectorSeleccionado][i];	// P is the peak
			aumento_senal=1;
			indexPicos = indexTotal;
			}                                     			// keep track of highest point in pulse wave


		//  NOW IT'S TIME TO LOOK FOR THE HEART BEAT
		// signal surges up in value every time there is a pulse
		if(N > (IBI/5)*3)	// avoid high frequency noise
			{
			if ( (PosiblePulso == 1) && (Pulse == 0))
				{
				Pulse = 1;                               // set the Pulse flag when we think there is a pulse
				index[contador2] = indexPicos;
				contador2++;
				IBI = sampleCounter - lastBeatTime;         // measure time between beats in mS
				lastBeatTime = sampleCounter;               // keep track of time for next pulse

				if(secondBeat)                        // if this is the second beat, if secondBeat == TRUE
					{
					secondBeat = 0;                  // clear secondBeat flag
					for(int i=0; i<=9; i++)             // seed the running total to get a realisitic BPM at startup
						rate[i] = IBI;
					}

				if(firstBeat)                        // if it's the first time we found a beat, if firstBeat == TRUE
					{
					firstBeat = 0;                  // clear firstBeat flag
					secondBeat = 1;                  // set the second beat flag
					}						// IBI value is unreliable so discard it

				// keep a running total of the last 10 IBI values
				int runningTotal = 0;                  // clear the runningTotal variable

				for(int k=0; k<=8; k++)                // shift data in the rate array
					{
					rate[k] = rate[k+1];                  // and drop the oldest IBI value
					runningTotal += rate[k];              // add up the 9 oldest IBI values
					}

				rate[9] = IBI;                          // add the latest IBI to the rate array
				runningTotal += rate[9];                // add the latest IBI to runningTotal
				runningTotal /= 10;                     // average the last 10 IBI values
				BPM = 60000/runningTotal;               // how many beats can fit into a minute? that's BPM!
				std::cout<<"BPM: "<< BPM<<"\n";
				}
			}else{
				PosiblePulso=0;
			}

			if (LecturaPulsaciones[!VectorSeleccionado][i] < thresh && Pulse == 1)   // when the values are going down, the beat is over
			{
				PosiblePulso=0;
				Pulse = 0;                         // reset the Pulse flag so we can do it again
				amp = P - T;                           // get amplitude of the pulse wave
				thresh = amp/2 + T;                    // set thresh at 50% of the amplitude
				P = thresh;                            // reset these for next time
				T = thresh;
			}

			if (N > 2500)                           // if 2.5 seconds go by without a beat
			{
				thresh = 525;                          // set thresh default
				P = 512;                               // set P default
				T = 512;                               // set T default
				lastBeatTime = sampleCounter;          // bring the lastBeatTime up to date
				firstBeat = 1;                      // set these to avoid noise
				secondBeat = 0;                    // when we get the heartbeat back
			}
			indexTotal++;
		}
}
