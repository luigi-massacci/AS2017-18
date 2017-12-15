#include <Wire.h>
#include <VL6180X.h>
#define reset1 x    //pins for hardware reset of sensors, attached to transistors to let 3.3V flow to the GPIO0 on the board 
#define reset2 x

VL6180X sensore1;   //creating objects for both sensors
VL6180X sensore2;   


void setup(){
  
    Serial.begin(9600);
    Wire.begin();
    pinMode(reset1, OUTPUT);    //setting both reset pins in OUTPUT mode
    pinMode(reset2, OUTPUT);    
    digitalWrite(reset2, HIGH); //disabling boot on chip #2
    sensore1.setAddress(0x22);
    digitalWrite(reset1, HIGH);
    digitalWrite(reset2, LOW);
    sensore2.setAddress(0x25);
    
    sensore1.init();          
    sensore1.configureDefault();
    sensore1.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
    sensore1.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 50);  //initialization of sensor #1
    sensore1.setTimeout(500);
    sensore1.stopContinuous();
    delay(300);
    sensore1.startInterleavedContinuous(100);
    
    sensore2.init();          
    sensore2.configureDefault();
    sensore2.writeReg(VL6180X::SYSRANGE__MAX_CONVERGENCE_TIME, 30);
    sensore2.writeReg16Bit(VL6180X::SYSALS__INTEGRATION_PERIOD, 50);  //initialization of sensor #2
    sensore2.setTimeout(500);
    sensore2.stopContinuous();
    delay(300);
    sensore2.startInterleavedContinuous(100);

}

void loop()
{
    Serial.print("Range sensor 1: ");
    Serial.print(sensore1.readRangeContinuousMillimeters());
    if (sensore1.timeoutOccurred()){
        Serial.println(" TIMEOUT");
    }
    Serial.print("Range sensor 2: ");
    Serial.print(sensore2.readRangeContinuousMillimeters());
    if (sensore2.timeoutOccurred()) {
        Serial.println(" TIMEOUT"); 
    }

  Serial.println();
}
