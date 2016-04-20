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

#include "Digitizer.h"


static const uint8_t _hidMultiReportDescriptorDigitizer[] PROGMEM = {
	/*  Digitizer */
    0x05, 0x0d,                      /* USAGE_PAGE (Digitizer)	  54 */
    0x09, 0x02,                      /* USAGE (Pen) */
    0xA1, 0x01,                      /* COLLECTION (Application) */
    0x85, HID_REPORTID_DIGITIZER,	 /*     REPORT_ID */

	/* Finger tool */
    0x09, 0x20,                     /*     Usage (Stylus) */
    0xA1, 0x00,                     /*     Collection (Physical) */
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
	0x09, 0x01,                      /*     Usage (Pointer) */
	0xA1, 0x00,                      /*     Collection (Physical) */
    0x09, 0x30,                      /*     USAGE (X) */
    0x09, 0x31,                      /*     USAGE (Y) */
	0x16, 0x00, 0x00,				 /* 	Logical Minimum (0) */
	0x26, 0xFF, 0x27,				 /* 	Logical Maximum (10000) */
	0x66, 0x00, 0x00,                /*     UNIT (None) */
	0x75, 0x10,						 /* 	Report Size (16), */
	0x95, 0x02,						 /* 	Report Count (2), */
	0x81, 0x02,						 /* 	Input (Data, Variable, Absolute) */
	0xc0,                            /* END_COLLECTION */ 
	0xc0,                            /* END_COLLECTION */ 
	
	/* End */
    0xc0                            /* END_COLLECTION */ 
};

Digitizer_::Digitizer_(void) 
{
	static HIDSubDescriptor node(_hidMultiReportDescriptorDigitizer, sizeof(_hidMultiReportDescriptorDigitizer));
	HID().AppendDescriptor(&node);
}


void Digitizer_::SendReport(void* data, int length)
{
	HID().SendReport(HID_REPORTID_DIGITIZER, data, length);
}

Digitizer_ Digitizer;

