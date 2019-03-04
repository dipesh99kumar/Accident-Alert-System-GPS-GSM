#include <MPU6050_tockn.h>
#include <Wire.h>
#include "TinyGPS++.h"

#include <SoftwareSerial.h>

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 2, 3, 4, 5);
MPU6050 mpu6050(Wire);
SoftwareSerial serial_connection(10, 11); //RX=pin 10, TX=pin 11

TinyGPSPlus gps;//This is the GPS object that will pretty much do all the grunt work with the NMEA data

void setup()

{
      Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
      lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Arduino ");
  Serial.begin(9600);//This opens up communications to the Serial monitor in the Arduino IDE

  serial_connection.begin(9600);//This opens up communications to the GPS

  Serial.println("GPS Start");//Just show to the monitor that the sketch has started

}

void loop()

{
  mpu6050.update();
  Serial.print("angleX : ");
  Serial.print(mpu6050.getAngleX());
  Serial.print("\tangleY : ");
  Serial.print(mpu6050.getAngleY());
  Serial.print("\tangleZ : ");
  Serial.println(mpu6050.getAngleZ());
  
  boolean var=false;
  float ang_x,ang_y,ang_z;
  ang_x=mpu6050.getAngleX();
  ang_y=mpu6050.getAngleY();
  ang_z=mpu6050.getAngleZ();
  int f=0;
  if((abs(ang_x)>30)||(abs(ang_y)>30))
  {
  while(serial_connection.available())//While there are characters to come from the GPS
  {

    gps.encode(serial_connection.read());//This feeds the serial NMEA data into the library one char at a time

  }
  if(gps.location.isUpdated())//This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in

  {

    //Get the latest info from the gps object which it derived from the data sent by the GPS unit

    Serial.println("Satellite Count:");

    Serial.println(gps.satellites.value());

    Serial.println("Latitude:");

    Serial.println(gps.location.lat(), 6);
   

    Serial.println("Longitude:");

    Serial.println(gps.location.lng(), 6);

    Serial.println("Speed MPH:");

    Serial.println(gps.speed.mph());

    Serial.println("Altitude Feet:");

    Serial.println(gps.altitude.feet());

    Serial.println("");
  
  f=1;
  while(f==1)
    {
      lcd.clear();
      lcd.print("LAT:");lcd.print(gps.location.lat(),6);
      lcd.setCursor(0,1);
      
      lcd.print("LONG:");lcd.print(gps.location.lng(),6);
      delay(2000);
      
      f++;
    }
    
  }
  lcd.clear();
}
}

