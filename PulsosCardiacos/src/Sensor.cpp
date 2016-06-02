/*
 * Sensor.cpp
 *
 *  Created on: 21/05/2015
 *      Author: edgar
 */

#include "Sensor.hpp"

BasicSensor::~BasicSensor(){}

Array_Sensor::Array_Sensor(unsigned int pin){
	Analogpin = new mraa::Aio(pin);
	this->pin = pin;
	rangeUpper=0;
	rangeLower=0;
	rawvalue=0;
	value=0;
}


Array_Sensor::Array_Sensor(unsigned int pin, float rangeUpper, float rangeLower){
	Analogpin = new mraa::Aio(pin);
	setrangeUpper(rangeUpper);
	setrangeLower(rangeLower);
}

Array_Sensor::~Array_Sensor(){
	delete Analogpin;
}

float Array_Sensor::getCurrentValue(){
	return value = this->getRawValue();
}
int Array_Sensor::getRawValue(){
	return rawvalue=Analogpin->read();
}
int Array_Sensor::getPin()
{
	return	pin;
}
std::string Array_Sensor::getIdentifier(){
	return SensorId;
}
std::string Array_Sensor::getMetricUnit(){
	return Unit;
}
float Array_Sensor::getrangeUpper(){
	return rangeUpper;
}
float Array_Sensor::getrangeLower(){
	return rangeLower;
}
void Array_Sensor::setrangeUpper(float rangeUpper){
	this->rangeUpper = rangeUpper;
}
void Array_Sensor::setrangeLower(float rangeLower){
	this->rangeLower = rangeLower;
}
