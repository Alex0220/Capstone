//  Controls RGB LED using potentiometers for each color

// the setup function runs once when you press reset or power the board

int inRGB[] = { A0,A1,A2 }; // Analog Inputs to reada potentiometer values
int outRGB[] = { 9,10,11 }; // PWM output pins to control brightness of each color in the RGB LED
int tempValue = 0;  // Placeholder

const int inMinVal = 0, inMaxVal = 1023;  // Values that define the maximum and minimum value returned from the potentiometer reading

void setup() {

  // Loop on all pins ( 3 values: Red, Green and Blue )
  for (int i = 0; i < 3; i++)
  {
    pinMode(inRGB[i], INPUT); // Prepare those pins to read the potentiometer values
    pinMode(outRGB[i], OUTPUT); // Prepare those pins to output the values of the RGB LED
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
}
