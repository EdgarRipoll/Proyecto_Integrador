/*
 * Sensor.hpp
 *
 *  Created on: 21/05/2015
 *      Author: edgar
 */

#ifndef SENSOR_HPP_
#define SENSOR_HPP_

#include <string>
#include <mraa/aio.hpp>

/**
 * @brief library for basic sensors
 */
class BasicSensor{
public:
	//BasicSensor(){};
	virtual ~BasicSensor();
	virtual float getCurrentValue()=0;
	virtual int getRawValue()=0;
	virtual std::string getIdentifier()=0;
	virtual std::string getMetricUnit()=0;
	virtual float getrangeUpper()=0;
	virtual float getrangeLower()=0;
private:
};

/**
 * @brief C++ API for Pressure Sensor
 *
 * Basic module for analog Pressure sensor on analog pin
 *
 */
class Array_Sensor : public BasicSensor{
public:
    /**
     * Analog Pressure sensor constructor
     *
     * @param pin analog pin to use
     */
	Array_Sensor(unsigned int pin);
    /**
     * Analog Pressure sensor constructor
     *
     * @param pin analog pin to use, maximum and minimum value possible that this sensor can measure [kPa]
     */
	Array_Sensor(unsigned int pin, float rangeUpper, float rangeLower);
    /**
     * ArrayPC_Sensor destructor
     */
	virtual ~Array_Sensor();
    /**
     * Get the Pressure in kPa from the sensor
     *
     * @return the normalized Pressure in kPa
     */
	float getCurrentValue();
    /**
     * Get raw value from AIO pin
     *
     * @return the raw value from the ADC
     */
	int getRawValue();
    /**
     * Get name of sensor
     *
     * @return the name of this sensor
     */
	std::string getIdentifier();
    /**
     * Get unit of measure
     *
     * @return the unit of the measure
     */
	std::string getMetricUnit();
    /**
     * Get maximum value possible that this sensor can measure
     *
     * @return the maximum value possible
     */
	float getrangeUpper();
    /**
     * Get minimum value possible that this sensor can measure
     *
     * @return the minimum value possible
     */
	float getrangeLower();
    /**
     * Set maximum value possible that this sensor can measure
     *
     */
	void setrangeUpper(float rangeUpper);
    /**
     * Set minimum value possible that this sensor can measure
     *
     */
	void setrangeLower(float rangeLower);


private:
	unsigned int	pin;
	std::string	SensorId;// = "Pressure Sensor";
	std::string	Unit;
	float	rangeUpper;
	float	rangeLower;
	mraa::Aio* Analogpin;
	int rawvalue;
	float value;
};

#endif /* SENSOR_HPP_ */
