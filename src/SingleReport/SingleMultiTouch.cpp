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

#include "SingleMultiTouch.h"

static const uint8_t _hidSingleReportDescriptorMultiTouch[] PROGMEM = {
	/*  Multi touch Screen */
    0x05, 0x0D,                      /* USAGE_PAGE (Digitizer)	  54 */
    0x09, 0x04,                      /* USAGE (Touch Screen) */
    0xA1, 0x01,                      /* COLLECTION (Application) */

	/* Maximum contact count */
    0x09, 0x55,                     /*   USAGE(Contact Count Maximum) */
    0x25, 0x08,                     /*   LOGICAL_MAXIMUM (8) */
    0xB1, 0x02,                     /*   FEATURE (Data,Var,Abs) */

	/* Current contact count */
    0x09, 0x54,                     /*   USAGE (Contact count) */
    0x95, 0x01,                     /*   REPORT_COUNT(1) */
    0x75, 0x08,                     /*   REPORT_SIZE (8) */
    0x81, 0x02,                     /*   INPUT (Data,Var,Abs) */

	/* Finger Collection */
    0x09, 0x22,                     /*     Usage (Finger) */
    0xA1, 0x02,                     /*     Collection (Logical) */

	/* Finger identifier */
    0x09, 0x51,                    //     USAGE (Contact Identifier)
    0x75, 0x08,                    //     REPORT_SIZE (8)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)

	0x09, 0x42,                     /*     Usage (Tip Switch) */
	0x09, 0x32,                     /*     USAGE (In Range) */
    0x15, 0x00,                     /*     LOGICAL_MINIMUM (0) */
    0x25, 0x01,                     /*     LOGICAL_MAXIMUM (1) */
    0x75, 0x01,                     /*     REPORT_SIZE (1) */
    0x95, 0x02,                     /*     REPORT_COUNT (2) */
    0x81, 0x02,                     /*     INPUT (Data,Var,Abs) */
	0x75, 0x01,                     /*     REPORT_SIZE (1) */
    0x95, 0x06,                     /*     REPORT_COUNT (6) */
    0x81, 0x01,                     /*     INPUT (Cnst,Ary,Abs) */

	/* X, Y */
    0x05, 0x01,                      /*     USAGE_PAGE (Generic Desktop) */
    0x09, 0x30,                      /*     USAGE (X) */
    0x09, 0x31,                      /*     USAGE (Y) */
	0x16, 0x00, 0x00,				 /* 	Logical Minimum (0) */
	0x26, 0x10, 0x27,				 /* 	Logical Maximum (10000) */
	0x36, 0x00, 0x00,                /*     Physical Minimum (0) */
    0x46, 0x10, 0x27,                /*     Physical Maximum (10000) */
	0x66, 0x00, 0x00,                /*     UNIT (None) */
	0x75, 0x10,						 /* 	Report Size (16), */
	0x95, 0x02,						 /* 	Report Count (2), */
	0x81, 0x02,						 /* 	Input (Data, Variable, Absolute) */
	0xc0,                            /* END_COLLECTION */ 
	
	/* End */
    0xc0                            /* END_COLLECTION */  
};


SingleMultiTouch_::SingleMultiTouch_(void) : PluggableUSBModule(1, 1, epType), protocol(HID_REPORT_PROTOCOL), idle(1)
{
	epType[0] = EP_TYPE_INTERRUPT_IN;
	PluggableUSB().plug(this);
}

int SingleMultiTouch_::getInterface(uint8_t* interfaceCount)
{
	*interfaceCount += 1; // uses 1
	HIDDescriptor hidInterface = {
		D_INTERFACE(pluggedInterface, 1, USB_DEVICE_CLASS_HUMAN_INTERFACE, HID_SUBCLASS_NONE, HID_PROTOCOL_NONE),
		D_HIDREPORT(sizeof(_hidSingleReportDescriptorMultiTouch)),
		D_ENDPOINT(USB_ENDPOINT_IN(pluggedEndpoint), USB_ENDPOINT_TYPE_INTERRUPT, USB_EP_SIZE, 0x01)
	};
	return USB_SendControl(0, &hidInterface, sizeof(hidInterface));
}

int SingleMultiTouch_::getDescriptor(USBSetup& setup)
{
	// Check if this is a HID Class Descriptor request
	if (setup.bmRequestType != REQUEST_DEVICETOHOST_STANDARD_INTERFACE) { return 0; }
	if (setup.wValueH != HID_REPORT_DESCRIPTOR_TYPE) { return 0; }

	// In a HID Class Descriptor wIndex cointains the interface number
	if (setup.wIndex != pluggedInterface) { return 0; }

	// Reset the protocol on reenumeration. Normally the host should not assume the state of the protocol
	// due to the USB specs, but Windows and Linux just assumes its in report mode.
	protocol = HID_REPORT_PROTOCOL;

	return USB_SendControl(TRANSFER_PGM, _hidSingleReportDescriptorMultiTouch, sizeof(_hidSingleReportDescriptorMultiTouch));
}

bool SingleMultiTouch_::setup(USBSetup& setup)
{
	if (pluggedInterface != setup.wIndex) {
		return false;
	}

	uint8_t request = setup.bRequest;
	uint8_t requestType = setup.bmRequestType;

	if (requestType == REQUEST_DEVICETOHOST_CLASS_INTERFACE)
	{
		if (request == HID_GET_REPORT) {
			// TODO: HID_GetReport();
			return true;
		}
		if (request == HID_GET_PROTOCOL) {
			// TODO: Send8(protocol);
			return true;
		}
	}

	if (requestType == REQUEST_HOSTTODEVICE_CLASS_INTERFACE)
	{
		if (request == HID_SET_PROTOCOL) {
			protocol = setup.wValueL;
			return true;
		}
		if (request == HID_SET_IDLE) {
			idle = setup.wValueL;
			return true;
		}
		if (request == HID_SET_REPORT)
		{
		}
	}

	return false;
}

void SingleMultiTouch_::SendReport(void* data, int length)
{
	USB_Send(pluggedEndpoint | TRANSFER_RELEASE, data, length);
}

SingleMultiTouch_ SingleMultiTouch;


