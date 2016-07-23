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

// This multitouch device can register up to 8 individual contacts.  Each must have its own
// identifier, defined below
#define CONTACT_ONE		(1 << 0)
#define CONTACT_TWO		(1 << 1)
#define CONTACT_THREE	(1 << 2)
#define CONTACT_FOUR	(1 << 3)
#define CONTACT_FIVE	(1 << 4)
#define CONTACT_SIX		(1 << 5)
#define CONTACT_SEVEN	(1 << 6)
#define CONTACT_EIGHT	(1 << 7)

#define TIP_SWITCH		(1 << 0)
#define IN_RANGE		(1 << 1)

// TIP_SWITCH is an activated on a finger press.  Some touch screens have the capability to detect
// when a tool (pen, finger) is in range, hence the IN_RANGE usage.  It must be activated for
// a touch to register. 
#define TOUCH_ALL (TIP_SWITCH | IN_RANGE)


typedef union{
	// MultiTouch report: numContacts, contactId, touch, 2 absolute axis
	uint8_t whole8[];
	uint16_t whole16[];
	uint32_t whole32[];
	struct{
		uint8_t numContacts;	// Number of contacts currently touching the screen
		uint8_t contactId;		// Id of the contact for this particular report
		uint8_t touch;
		int16_t xAxis;
		int16_t yAxis;
	};
} HID_MultiTouchReport_Data_t;


class MultiTouchAPI
{
protected:
	uint16_t xAxis;
	uint16_t yAxis;
	uint8_t _touch;
	uint8_t _contacts;
	uint8_t _numContacts;
	
public:
	inline MultiTouchAPI(void);
	inline void begin(void);
	inline void end(void);

	inline void click(uint8_t id = CONTACT_ONE);
	inline void moveTo(int x, int y, uint8_t id = CONTACT_ONE, uint8_t t = TOUCH_ALL);
	inline void press(uint8_t id = CONTACT_ONE);
	inline void release(uint8_t id = CONTACT_ONE);
	inline void setNumContacts(uint8_t nCts = 1);
	inline bool isPressed(uint8_t c);
	
	// Sending is public in the base class for advanced users.
	virtual void SendReport(void* data, int length) = 0;
};

// Implementation is inline
#include "MultiTouchAPI.hpp"

