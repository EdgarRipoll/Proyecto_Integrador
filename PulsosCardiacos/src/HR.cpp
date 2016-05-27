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
}

HR::~HR() {
	// TODO Auto-generated destructor stub
}

void	HR::getMedicion(){

	LecturaPulsaciones[VectorSeleccionado][ContadorMediciones] = this->getRawValue();
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

void	HR::Derivative()
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

void	HR::Normalizar()
{
	float max_value=0;
	max_value = *std::max_element(Procesamiento,Procesamiento+504); //504 es el (sizeof(Procesamiento))
	for(int i=0 ; i<=503 ; i++) //503 es el (sizeof(Procesamiento)-1)
	{
		Procesamiento[i] /= max_value;

	}
}

void	HR::SquaringFunction()
{
	for(int i=0 ; i<=503 ; i++) //503 es el (sizeof(Procesamiento)-1)
		Procesamiento[i] = pow(Procesamiento[i],2.0);
}

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
	this->Derivative();
	this->Normalizar();
	this->SquaringFunction();
}
/*
void	HR::Guardar()
{
	if (myfile.is_open())
		for(int j; j<=503 ; j++)
			myfile << Procesamiento[j] <<"\n";
	else std::cout << "Unable to open file";
}
*/
float	HR::getProcesamiento(int index)
{
	return	Procesamiento[index];
}

float	HR::getRaw(int index)
{
	return	LecturaPulsaciones[!VectorSeleccionado][index];
}
