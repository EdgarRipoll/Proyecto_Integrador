#include <unistd.h>
#include <iostream>
#include "mraa.hpp"
#include "Timer.hpp"
#include "DatosRecibidos.h"
#include <stdlib.h>
#include <string.h>
#include "SMSRecibido.h"
#include "GPSRecibido.h"
#include "ModuloSIM.h"

#include "Sensor.hpp"
#include "HR.hpp"
#include <signal.h>
#include <iomanip>


char	Msj[]="AT\r";
std::string DatosSIM908;
ModuloSIM*	SIM908;
DatosRecibidos*	Respuesta;
SMSRecibido*	MensajeRecibido;
GPSRecibido*	DatosGPS;
int	fd;
struct	sigaction	saio;
int	RecibeDatos=0;
std::string	LeerSMS;
char	PedirUbicacion[] = "AT+CGPSINF=32\r";
bool delay=0;
int cont=0;
int cont2=0;
bool PideUbicacion=0;
bool LeaSMS=0;



HR*	Radial;
HR*	Ulnar;
bool toggle=0;
