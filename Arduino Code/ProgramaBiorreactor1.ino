/*
 for any doubts about the  pressure sensor check the
 https://learn.sparkfun.com/tutorials/mpl3115a2-pressure-sensor-hookup-guide
 
*/

#include <Wire.h>
#include "SparkFunMPL3115A2.h"
#include <LiquidCrystal.h>

#define RELAY1  7 //stes the pin for the light bulb
#define RELAY2  8 //stes the pin for the air pump

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Create an instance of the object
MPL3115A2 myPressure;

float tempC;// defines the tempC virable, it might be down on the loop
int tempPin0 = 0;// assigns the pin to the cero analog input on the arduino
int tempPin1 = 1;// assigns the pin to the one analog input on the arduino
int tempPin2 = 2;// assigns the pin to the two analog input on the arduino

void setup()
{
  Wire.begin();        // Join i2c bus for the mpl3115a2
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:

  
  Serial.begin(9600);  // Start serial for output

  myPressure.begin(); // Get sensor online

  pinMode(RELAY1, OUTPUT); // configures the arduino pin as an output for the light
  pinMode(RELAY2, OUTPUT); // configures the arduino pin as an output for the pump

  // Configure the sensor
  //myPressure.setModeAltimeter(); // Measure altitude above sea level in meters
  
  
  
  myPressure.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa
  
  myPressure.setOversampleRate(7); // Set Oversample to the recommended 128
  myPressure.enableEventFlags(); // Enable all three pressure and temp event flags 
}

void loop()
{
  /*float altitude = myPressure.readAltitude();
  Serial.print("Altitude(m):");
  Serial.print(altitude, 2);

  altitude = myPressure.readAltitudeFt();
  Serial.print(" Altitude(ft):");
  Serial.print(altitude, 2);*/

  float pressure = myPressure.readPressure();//reads pressure from sensor
  pressure= pressure * 0.00750064; // converts from Pa to mmHg

  //if you whant to see the pressure on the computer
  //Serial.print("Pressure(Pa):");
  //Serial.print(pressure, 2);

  
//sets the cursor and prints pressure value on the LCD
  lcd.setCursor(0, 1);
  lcd.print ("Pre(mmHg):");
  lcd.setCursor(10, 1);
  lcd.print(pressure,2);
  

  //reads the analog pin for temperature from the lm35
  tempC = analogRead(tempPin0); 
  tempC = (5.0 * tempC * 100.0)/1024.0;// converts the value to temperature

 //if you whant to see the temperature for the individual lm35 on the computer 
  //Serial.print(tempC);
 // Serial.print(" el 0");

  float tempC1 = analogRead(tempPin1); 
  tempC1 = (5.0 * tempC1 * 100.0)/1024.0;// converts the value to temperature

  //if you want to see the temperature for the individual lm35 on the computer
  //Serial.print(tempC1);
  //Serial.print(" el 1");

  float tempC2 = analogRead(tempPin2); 
  tempC2 = (5.0 * tempC2 * 100.0)/1024.0;// converts the value to temperature

  //if you want to see the temperature for the individual lm35 on the computer
  //Serial.print(tempC2);
  //Serial.print(" el 2");
  
  
//reads temperature from the 
  float temperature = myPressure.readTemp();

  
  //Serial.print(" Temp(c):");
  //Serial.print(temperature, 2);
  
  lcd.setCursor(0, 0);
  lcd.print (" Temp(c):");

  float tempF = ((temperature + tempC2 + tempC1 + tempC)/4);// average of all the temperature sensors
  lcd.print(tempF,2);
  
  Serial.println();


  if (tempF >37.5)
  { 
    digitalWrite(RELAY1,1);          // Turns light Off 
  }

  if (tempF < 36.5)
  {
    digitalWrite(RELAY1,0);           // Turns light on
  
  }

   if (pressure >765)
  { 
    digitalWrite(RELAY2,1);          // Turns light Off 
  }

    else
  {
    digitalWrite(RELAY2,0);           // Turns light on
  
  } 
 
}

