#include <Wire.h>
#include <L3G4200D.h>

/*
 Random RGB Color Generator
 */

//Create Gyro object
L3G4200D gyro;

//Initiate pins
int blue = 11;
int red = 10;
int green = 9;

//Pots setup for manual potentiometer changes
//int potRed = A0;
//int potBlue = A1;
//int potGreen = A2;
//int val
//connections to button to use as a switch
int buttonin = 8;
int buttonout = 2;//the out must have a pullup/pulldown resistor

//instantiate a byte object for color (0-255)
byte randRed;
byte randGreen;
byte randBlue;

//Instantiate gyro axes
int x,y,z;
// the setup routine runs once when you press reset:
void setup() {
  
  Wire.begin();
  gyro.initialize(500);
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(buttonin,OUTPUT);
  digitalWrite(buttonin, HIGH);
  pinMode(buttonout,INPUT); //make sure buttonin is measuring input
  Serial.begin(9600); //so that we can read the output
  randomSeed(analogRead(0)); //makes sure colors are wellrandomized if using random color generation
 
}

// the loop routine runs over and over again forever:
void loop() {
  
/*
Change this to a function that will create a random color on a separate LED
*/
//This is to generate a random color
//  if (digitalRead(buttonout) == HIGH){
//    randGreen = random(256);
//    randRed = random(256);
//    randBlue = random(256);


//Sets up axis values
    x = gyro.getX();
    y = gyro.getY();
    z = gyro.getZ();
//    if (randGreen == 0 || randGreen == 255):
// The gyro measures degrees/second so we need to figure out how much of a turn we want to be fromm 0-255
    randGreen += byte(x/180);
    randBlue += byte(y/180);
    randRed += byte(z/180);
    
    
   //Output things for debugging
    Serial.println("Green:");
    Serial.println(randGreen);
    Serial.println("Red:");
    Serial.println(randRed);
    Serial.println("Blue:");
    Serial.println(randBlue);
    Serial.println("-------------");
//  valB = analogRead(potBlue;
//  analogWrite(blue, valB/4); //Shows control with a external source
//  valB = analogRead(potRed);
//  analogWrite(red, valR/4); //Shows control with a external source
//  valB = analogRead(potGreen);
//  analogWrite(green, valG/4); //Shows control with a external source
//subtract 255 since the LED is common cathode
  analogWrite(blue, 255 - randBlue);
  analogWrite(red, 255 - randRed);
  analogWrite(green, 255- randGreen);
 
}

