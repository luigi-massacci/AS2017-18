#include <Wire.h>
#include <VL6180X.h>

VL6180X sensor;
VL6180X sensor2;

void setup()
{  
//  pinMode(4, OUTPUT);
//  pinMode(5, OUTPUT);
//  digitalWrite(4, LOW);
//  digitalWrite(5, LOW);
  
  
  pinMode(5, INPUT_PULLUP); 
  pinMode(4, INPUT_PULLUP);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);


  delay(500);
  Wire.begin();


  Serial.begin (9600);

  pinMode(4, INPUT);
  delay(150);
  Serial.println("00");
  sensor.init();

  Serial.println("01");
  delay(100);
  sensor.setAddress((uint8_t)22);
  Serial.println("02");

  pinMode(5, INPUT);
    delay(150);
  sensor2.init();
  Serial.println("03");
  delay(100);
  sensor2.setAddress((uint8_t)25);
  Serial.println("04");

  Serial.println("addresses set");

  sensor.configureDefault();
  sensor.setTimeout(500);

  sensor2.configureDefault();
  sensor2.setTimeout(500);




}


void loop()
{
  Serial.println ("I2C scanner. Scanning ...");
  byte count = 0;

  for (byte i = 1; i < 120; i++)
  {
  

    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
    {
      Serial.print("Found address: ");
      Serial.print(i, DEC);
      Serial.print(" (0x");
      Serial.print(i, HEX);
      Serial.println(")");
      count++;
      delay (1);  // maybe unneeded?
    } // end of good response
  } // end of for loop
  Serial.println ("Done.");
  Serial.print ("Found ");
  Serial.print (count, DEC);
  Serial.println (" device(s).");

Serial.print("Sensor1: ");
   Serial.print(sensor.readRangeSingleMillimeters());
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  Serial.println();

 Serial.print("Sensor2: ");
   Serial.print(sensor2.readRangeSingleMillimeters());
  if (sensor2.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
 
  Serial.println();


  delay(3000);
 

 Serial.println("over");

  
}


