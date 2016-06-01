#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include "mraa.hpp"
#include "Timer.hpp"
#include "Sensor.hpp"
#include "HR.hpp"
Array_Sensor*	ArraySensor;
HR*	Radial;
int adc_value;
// writing on a text file
#include <iostream>
#include <fstream>
std::ofstream Procesado ("PruebaPulsosCardiacosProc.txt");
std::ofstream Raw ("PruebaPulsosCardiacosRaw.txt");
std::ofstream Index ("PruebaPulsosCardiacosIndex.txt");
//bool toggle=0;
//mraa::Gpio* PowerKey;
