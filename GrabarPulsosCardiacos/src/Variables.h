#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include "mraa.hpp"
#include "Timer.hpp"
#include "Sensor.hpp"
#include <iostream>
#include <fstream>
ArrayPC_Sensor*	ArraySensor;
int adc_value;
// writing on a text file
#include <iostream>
#include <fstream>
std::ofstream myfile ("PulsosCardiacos.txt");
