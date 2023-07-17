/*
 * Copyright (c) 2023 CONTROLLINO GmbH.
 *
 * SPDX-License-Identifier: MIT
 */
 
#ifndef NEO_CORE_PIN_H
#define NEO_CORE_PIN_H
 
/**
 * \file controlino_pin_driver.h
 *
 * Arduino pins API for Controllino RP2040 boards
 * Based on https://github.com/arduino/ArduinoCore-mbed/tree/master/variants/NANO_RP2040_CONNECT
 *
 * \author Pedro Marquez @pmmarquez, CONTROLLINO Firmware Team
 */
 
#include "Arduino.h"
 
#include "cy8c95xx.h"
#include "mcp356x.h"
#include "ad56x4.h"
#include "bts71220.h"
#include "wsen_temp.h"
 
/**
 * \brief Controllino Rp2040 pin class
 */
class ControllinoRp2040Pin{
public:
	typedef enum { CY8C95XX_PIN, MCP356X_PIN, AD56X4_PIN, RP2040_PIN} _pin_type_t;
	ControllinoRp2040Pin(int pin, _pin_type_t type): _pin(pin), _type(type)
	{
		setMode(INPUT);
		_setDigitalThreshold(~0U);
	};

	bool operator== (ControllinoRp2040Pin const& other) const { return _pin == other._pin; };

	pin_size_t getPin(void) { return _pin; };
	_pin_type_t getType(void) { return _type; };

	void setMode(PinMode mode) { _mode = mode; };
	PinMode getMode(void) { return _mode; };

	void _setDigitalThreshold(uint32_t threshold) { _digitalThreshold = threshold; };
	uint32_t _getDigitalThreshold(void) { return _digitalThreshold; };
private:
	pin_size_t _pin;
	_pin_type_t _type;
	PinMode _mode;
	uint32_t _digitalThreshold;
};

/**
 *\brief Get the ControllinoRp2040Pin* from integer pin definition
 * 
 * \param pin Integer pin definition
 * \return ControllinoRp2040Pin* or nullptr
 */
ControllinoRp2040Pin* getControllinoRp2040Pin(int pin);

/**
 *\brief Similar to Arduino API functions for compatibility with ControllinoRp2040Pin*
 */
void pinMode(ControllinoRp2040Pin* pin, PinMode mode);
PinStatus digitalRead(ControllinoRp2040Pin* pin);
void digitalWrite(ControllinoRp2040Pin* pin, PinStatus value);
int analogRead(ControllinoRp2040Pin* pin);
void analogWrite(ControllinoRp2040Pin* pin, int value);
 
/**
 *\brief Digital threshold API to implement a digital input with an analog input only pin 
 */
void setDigitalThreshold(ControllinoRp2040Pin* pin, uint32_t threshold);
uint32_t getDigitalThreshold(ControllinoRp2040Pin* pin);
extern "C" void setDigitalThreshold(pin_size_t pin, uint32_t threshold); // From integer pin definition
extern "C" uint32_t getDigitalThreshold(pin_size_t pin); // From integer pin definition

/**
 * \brief User can access peripherals interfaces
 */
extern cy8c95xx_t* neo_cy8c95xx;
extern mcp356x_t* neo_mcp356x;
extern ad56x4_t* neo_ad56x4;
extern bts71220_t* neo_bts71220;
extern wsen_temp_t* neo_wsen_temp;

#endif  // NEO_CORE_PIN_H