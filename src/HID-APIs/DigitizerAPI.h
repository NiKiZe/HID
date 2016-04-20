/*
Copyright (c) 2014-2015 NicoHood
See the readme for credit to other people.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

// Include guard
#pragma once

#include <Arduino.h>
#include "HID-Settings.h"

#define TIP_SWITCH		(1 << 0)
#define IN_RANGE		(1 << 1)

// TIP_SWITCH is an activated on a finger press.  Some digitizers have the capability to detect
// when a tool (pen, finger) is in range, hence the IN_RANGE usage.  It must be activated for
// a touch to register. 
#define TOUCH_ALL (TIP_SWITCH | IN_RANGE)


typedef union{
	// Digitizer report: touch, 2 absolute axis
	uint8_t whole8[];
	uint16_t whole16[];
	uint32_t whole32[];
	struct{
		uint8_t touch;
		int16_t xAxis;
		int16_t yAxis;
	};
} HID_DigitizerReport_Data_t;


class DigitizerAPI
{
protected:
	uint16_t xAxis;
	uint16_t yAxis;
	uint8_t _touch;
	
public:
	inline DigitizerAPI(void);
	inline void begin(void);
	inline void end(void);

	inline void click(uint8_t t = TOUCH_ALL);
	inline void moveTo(int x, int y, uint8_t t = TOUCH_ALL);
	inline void press();
	inline void release();
	inline bool isPressed();
	
	// Sending is public in the base class for advanced users.
	virtual void SendReport(void* data, int length) = 0;
};

// Implementation is inline
#include "DigitizerAPI.hpp"

