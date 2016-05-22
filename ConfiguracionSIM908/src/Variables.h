#include <unistd.h>
#include <iostream>
//#include <exception>
//#include <iomanip>
//#include <cstdlib>
//#include <stdio.h>
#include "mraa.hpp"
#include "Timer.hpp"
#include "DatosRecibidos.h"
#include <stdlib.h>
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

char	Msj[]="AT\r";//{'\r','\n','A','T','+','C','M','G','R','=','2','2','\r','\n'};//"AT+CGPSINF=32 \r";//"AT\r";//{'A','T','\r'};
std::string DatosSIM908;
ModuloSIM*	SIM908;
DatosRecibidos*	Respuesta;
SMSRecibido*	MensajeRecibido;
GPSRecibido*	DatosGPS;
int	fd;
struct	sigaction	saio;
int	RecibeDatos=0;
/*const char	SeparadorTrama[] = ',';
//char toks[] = "\t \n ,"; // tabs, spaces and newlines
const char*	Separador = &SeparadorTrama;*/
//char *token;
//int nroTokens=0;
//char	LeerSMS[] = "AT+CMGR=2\r";
std::string	LeerSMS;
char	PedirUbicacion[] = "AT+CGPSINF=32\r";
//char	ModoText[] = "AT+CMGF=1\r\n";
//char	latitud[11];
//char	longitud[11];
//char	linkgoogle[];
//char	telefono[14];
bool delay=0;
int cont=0;
int cont2=0;
bool PideUbicacion=0;
