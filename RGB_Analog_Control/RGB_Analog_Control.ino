#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C iLCD(0x3f,2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int inRGB[] = { A0,A1,A2 }; // Analog Inputs to reada potentiometer values
int outRGB[] = { 3,5,6 }; // PWM output pins to control brightness of each color in the RGB LED
int tempValue = 0;  // Placeholder
int momentary = 0; //button to generate a random color
char valStg[20];

const int inMinVal = 0, inMaxVal = 1023;  // Values that define the maximum and minimum value returned from the potentiometer reading

void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}

// Set pin 9's PWM frequency to 3906 Hz (31250/8 = 3906)
// Note that the base frequency for pins 3, 9, 10, and 11 is 31250 Hz
//setPwmFrequency(9, 8);

void setup() {
  // Loop on all pins ( 3 values: Red, Green and Blue )
  for (int i = 0; i < 3; i++)
  {
    pinMode(inRGB[i], INPUT); // Prepare those pins to read the potentiometer values
    pinMode(outRGB[i], OUTPUT); // Prepare those pins to output the values of the RGB LED
  }
    {
  Serial.begin(9600);
   iLCD.backlight();
   iLCD.begin ( 20, 4 );
   iLCD.home();
   iLCD.print("test");
   iLCD.setCursor(0,1);
   iLCD.print("AM I better?");
   iLCD.setCursor(0,2);
    }
}


// the loop function runs over and over again until power down or reset
void loop() {
  // Repeat the following for each color
  for (int i = 0; i < 3; i++)
  {
    tempValue = analogRead(inRGB[i]); // Read the potentiometer

    // Scale down the potentiometer reading ( 0 ~ 1023 ) to a valid PWM value
    // 0 ~ 255 represent the range of the Arduino PWM output
    tempValue = map(tempValue, inMinVal, inMaxVal, 0, 255);
    
    // Write the output on the pin
    analogWrite(outRGB[i], tempValue);
  }
  {
    // when characters arrive over the serial port...
    if (Serial.available()) 
    {
      // wait a bit for the entire message to arrive
      delay(100);
      // clear the screen
      iLCD.clear();
      // read all the available characters
      while (Serial.available() > 0) 
         {
        // display each character to the LCD
        iLCD.write(Serial.read());
         }
    }
   }
}   
