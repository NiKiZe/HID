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

#include "MultiTouch.h"


static const uint8_t _hidMultiReportDescriptorMultiTouch[] PROGMEM = {
	/*  Multi touch Screen */
    0x05, 0x0D,                      /* USAGE_PAGE (Digitizer)	  54 */
    0x09, 0x04,                      /* USAGE (Touch Screen) */
    0xA1, 0x01,                      /* COLLECTION (Application) */
    0x85, HID_REPORTID_MULTITOUCH,	 /*     REPORT_ID */

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

MultiTouch_::MultiTouch_(void) 
{
	static HIDSubDescriptor node(_hidMultiReportDescriptorMultiTouch, sizeof(_hidMultiReportDescriptorMultiTouch));
	HID().AppendDescriptor(&node);
}


void MultiTouch_::SendReport(void* data, int length)
{
	HID().SendReport(HID_REPORTID_MULTITOUCH, data, length);
}

MultiTouch_ MultiTouch;

