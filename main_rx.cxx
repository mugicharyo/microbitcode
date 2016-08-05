/*
 The MIT License (MIT)
 
 Permission is hereby granted, free of charge, to any person obtaining a
 copy of this software and associated documentation files (the "Software"),
 to deal in the Software without restriction, including without limitation
 the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 DEALINGS IN THE SOFTWARE.
 */

#include "MicroBit.h"

MicroBit uBit;

//
// Print details of all events received to the serial port.
// Default settings are 115200 baud, 8N1 over the USB interface.
//

#define ARR_LEN 25
#define THRESHOLD 700
#define HIGH 200

uint8_t kostas;
uint8_t last_mode;

MicroBitPin P0(MICROBIT_ID_IO_P0, MICROBIT_PIN_P0, PIN_CAPABILITY_ANALOG);
//initialise P0 as an ADC


MicroBitImage img(5,5);

//Rx event - triggered by '1' from from the Tx micrbit
void receive_image()
{
	uint16_t count;
	uint8_t x,y;
	uBit.sleep(500);//250ms delay before branching + 500ms =750ms
	
    for( int i = 0 ; i < ARR_LEN ; i++ )
    {
        //x and y track coordinates to draw LEDs
		x = i%5;
		y = i/5;

        //This loop reduces noise by sampling each '1' 5 times
		for(int i=0;i<5;i++)
		{
			kostas=P0.getAnalogValue();
			count += kostas;
			uBit.sleep(50);
            //50 * 5 = 250ms delay - critical to time with Tx
		}
		if(count<THRESHOLD)
			uBit.display.image.setPixelValue(x, y, 255);//set the bit to 1
		else
			uBit.display.image.setPixelValue(x, y, 0);//else set the bit to 0
		count = 0;
		uBit.sleep(500);//250 + 500 = 750ms delay per bit
    }
}


int main()
{


    uBit.init();
	uint16_t count=0;

    while(1)
    {

		kostas = P0.getAnalogValue();
        //if the value is high enter checking loop
		if( kostas < HIGH )
		{

            //sample 5 times to reduce noise
            ////TODO - remove duplicate code (bad)
		    for( int i = 0 ; i < 5 ; i++ )
		    {
		    	count += kostas;
		    	uBit.sleep(50);
		    	kostas=P0.getAnalogValue();
		    }
        
            //give a '1'
		    if( count < THRESHOLD )
		    	receive_image();
		
		count = 0;//reset count

		}
	}
}
