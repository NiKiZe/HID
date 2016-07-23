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



MultiTouchAPI::MultiTouchAPI(void): 
xAxis(0), yAxis(0), _touch(0), _contacts(0), _numContacts(1)
{
	// Empty
}

void MultiTouchAPI::begin(void){
	// release all buttons
	end();
}

void MultiTouchAPI::end(void){
	_touch = 0;
	moveTo(xAxis, yAxis, CONTACT_ONE, 0);
}

void MultiTouchAPI::click(uint8_t id){
	_touch = TOUCH_ALL;
	moveTo(xAxis, yAxis, id, TOUCH_ALL);
	_touch = 0;
	moveTo(xAxis, yAxis, id, 0);
}

void MultiTouchAPI::moveTo(int x, int y, uint8_t id, uint8_t t){
	xAxis = x;
	yAxis = y;
	_touch = t;
	if (_touch == TOUCH_ALL) {
		_contacts = _contacts | id;
	} else {
		_contacts = _contacts & ~id;
	}
	HID_MultiTouchReport_Data_t report;
	report.numContacts = _numContacts;  // initial testing will limit to one contact
	report.contactId = id;
	report.touch = t;
	report.xAxis = x;
	report.yAxis = y;
	SendReport(&report, sizeof(report));
}

void MultiTouchAPI::press(uint8_t id){
	_touch = TOUCH_ALL;
	moveTo(xAxis, yAxis, id, _touch);
}

void MultiTouchAPI::release(uint8_t id){
	_touch = 0;
	moveTo(xAxis, yAxis, id, _touch);
}

void MultiTouchAPI::setNumContacts(uint8_t nCts) {
	_numContacts = nCts;
}

bool MultiTouchAPI::isPressed(uint8_t id){
	if ((_contacts && id) > 0)
		return true;
	return false;
}
