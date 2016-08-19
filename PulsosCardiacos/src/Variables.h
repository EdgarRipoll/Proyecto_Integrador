#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include "mraa.hpp"
#include "Timer.hpp"
#include "Sensor.hpp"
#include "HR.hpp"
Array_Sensor*	ArraySensor;
HR*	Radial;
HR*	Ulnar;
int adc_value;
// writing on a text file
#include <iostream>
#include <fstream>
std::ofstream Procesado ("PulsosCardiacosProc.txt");
std::ofstream RawR ("PulsosCardiacosRawR.txt");
std::ofstream IndexR ("PulsosCardiacosIndexR.txt");
std::ofstream RawU ("PulsosCardiacosRawU.txt");
std::ofstream IndexU ("PulsosCardiacosIndexU.txt");
bool toggle=0;
//mraa::Gpio* PowerKey;
