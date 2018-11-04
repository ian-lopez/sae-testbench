#include "SparkFunLIS3DH.h"
#include "Wire.h"
#include "SPI.h"
#include "Pushbutton.h"

#define accelSen1 10
#define killPin 5

int PKILL = 5;
float maxAccel = 6;

LIS3DH myIMU(SPI_MODE, accelSen1); // constructed with parameters for SPI and cs pin number

Pushbutton killSwitch(killPin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000); //relax...
  Serial.println("Processor came out of reset.\n");

  myIMU.settings.accelRange = 8; //Testing
  //Call .begin() to configure the IMU
  myIMU.begin();

}

void loop()
{
  delay(250);

 float gX = myIMU.readFloatAccelX();
 float gY = myIMU.readFloatAccelY();
 float gZ = myIMU.readFloatAccelZ();

 if(isnan(gX)||isnan(gY)||isnan(gZ)){
  Serial.println("Failed to read from Sensor"); //Change depending on how many we have
 }

 if(gX > maxAccel||gY > maxAccel || gZ > maxAccel || killSwitch.isPressed()){
  Serial.println("SHUTTING DOWN");
  digitalWrite(killPin, HIGH);
  return PKILL;
 }
  
  //Get all parameters
  Serial.print("\nAccelerometer:\n");
  Serial.print(" X = ");
  Serial.println(myIMU.readFloatAccelX(), 8);// 8 was a 4, but why? Could be the number of decimals
  Serial.print(" Y = ");
  Serial.println(myIMU.readFloatAccelY(), 8);
  Serial.print(" Z = ");
  Serial.println(myIMU.readFloatAccelZ(), 8);

  Serial.println("------------------------------------------");
  
}
