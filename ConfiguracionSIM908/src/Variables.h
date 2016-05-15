//#include <unistd.h>
#include <iostream>
//#include <exception>
//#include <iomanip>
//#include <cstdlib>
//#include <stdio.h>
#include "mraa.hpp"
#include "Timer.hpp"
#include "DatosRecibidos.h"
//#include <stdlib.h>
#include <string.h>
#include "SMSRecibido.h"
#include "GPSRecibido.h"
#include "ModuloSIM.h"
//#include "GPS.h"
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <fcntl.h>
//#include <sys/signal.h>
//#include <errno.h>
//#include <termios.h>

char	Msj[]="AT\r";//{'A','T','\r'};
std::string DatosSIM908;
ModuloSIM*	SIM908;
DatosRecibidos*	Respuesta;
SMSRecibido*	MensajeRecibido;
GPSRecibido*	DatosGPS;
int	fd;
struct	sigaction	saio;
int	RecibeDatos=0;
const char	SeparadorTrama = ',';
const char*	Separador = &SeparadorTrama;
//char *token;
//int nroTokens=0;
char	LeerSMS[] = "AT+CMGR=1\r";
char	PedirUbicacion[] = "AT+CGPSINF=32\r";
//char	ModoText[] = "AT+CMGF=1\r\n";
//char	latitud[11];
//char	longitud[11];
//char	linkgoogle[];
//char	telefono[14];
