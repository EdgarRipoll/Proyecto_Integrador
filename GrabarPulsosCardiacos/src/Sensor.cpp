/*
 * Sensor.cpp
 *
 *  Created on: 21/05/2015
 *      Author: edgar
 */

#include "Sensor.hpp"

BasicSensor::~BasicSensor(){}

ArrayPC_Sensor::ArrayPC_Sensor(unsigned int pin){
	Analogpin = new mraa::Aio(pin);
	this->pin = pin;
	rangeUpper=0;
	rangeLower=0;
	rawvalue=0;
	value=0;
}


ArrayPC_Sensor::ArrayPC_Sensor(unsigned int pin, float rangeUpper, float rangeLower){
	Analogpin = new mraa::Aio(pin);
	setrangeUpper(rangeUpper);
	setrangeLower(rangeLower);
}

ArrayPC_Sensor::~ArrayPC_Sensor(){
	delete Analogpin;
}

float ArrayPC_Sensor::getCurrentValue(){
	return value = getRawValue() *2.71;
}
int ArrayPC_Sensor::getRawValue(){
	return rawvalue=Analogpin->read();
}
std::string ArrayPC_Sensor::getIdentifier(){
	return SensorId;
}
std::string ArrayPC_Sensor::getMetricUnit(){
	return Unit;
}
float ArrayPC_Sensor::getrangeUpper(){
	return rangeUpper;
}
float ArrayPC_Sensor::getrangeLower(){
	return rangeLower;
}
void ArrayPC_Sensor::setrangeUpper(float rangeUpper){
	this->rangeUpper = rangeUpper;
}
void ArrayPC_Sensor::setrangeLower(float rangeLower){
	this->rangeLower = rangeLower;
}
