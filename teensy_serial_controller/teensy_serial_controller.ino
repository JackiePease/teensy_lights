/*  OctoWS2811 BasicTest.ino - Basic RGB LED Test
    http://www.pjrc.com/teensy/td_libs_OctoWS2811.html
    Copyright (c) 2013 Paul Stoffregen, PJRC.COM, LLC

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

  Required Connections
  --------------------
    pin 2:  LED Strip #1    OctoWS2811 drives 8 LED Strips.
    pin 14: LED strip #2    All 8 are the same length.
    pin 7:  LED strip #3
    pin 8:  LED strip #4    A 100 ohm resistor should used
    pin 6:  LED strip #5    between each Teensy pin and the
    pin 20: LED strip #6    wire to the LED strip, to minimize
    pin 21: LED strip #7    high frequency ringining & noise.
    pin 5:  LED strip #8
    pin 15 & 16 - Connect together, but do not use
    pin 4 - Do not use
    pin 3 - Do not use as PWM.  Normal use is ok.

  This test is useful for checking if your LED strips work, and which
  color config (WS2811_RGB, WS2811_GRB, etc) they require.
*/

//#include <OctoWS2811.h>

const int ledsPerStrip = 100;

//DMAMEM int displayMemory[ledsPerStrip*6];
//int drawingMemory[ledsPerStrip*6];

//const int config = WS2811_GRB | WS2811_800kHz;

//OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

void setup() {
  Serial.begin(115200);

  // use arduino built in LED
  pinMode(LED_BUILTIN, OUTPUT);
  
  //leds.begin();
  //leds.show();
}


int messageOffset;
long nextColour = 0;

int buf[512];

void loop() { 

  if (Serial.available() > 0) {
    
    String input = Serial.readStringUntil('\n');
    hexstr_to_char((char*)input.c_str());

    messageOffset = buf[1] | buf[0] << 8;

    for(int x = 0, j = 2, l = messageOffset; x < 170; x++, j+=3, l++)
    {      
      nextColour = buf[j] * 256L;
      nextColour = (nextColour + buf[j+1]) * 256L;
      nextColour += buf[j+2];

      //leds.setPixel(l, nextColour);
      
      // use built in LED as light number 0
      if(l == 0)
      {
        if(nextColour == 0)
          digitalWrite(LED_BUILTIN, LOW);
        else
          digitalWrite(LED_BUILTIN, HIGH);
      }
    }
    //leds.show();
    
  }
}

void hexstr_to_char(char* hexstr)
{
    size_t len = strlen(hexstr);
    size_t final_len = len / 2;

    for (size_t i=0, j=0; j<final_len; i+=2, j++)
    {

        buf[j] = (((hexstr[i] <= '9') ? (hexstr[i] - '0') : (hexstr[i] - 'A' + 10)) * 16 )
          + ((hexstr[i+1] <= '9') ? (hexstr[i+1] - '0') : (hexstr[i+1] - 'A' + 10));

    }
    
}
  
