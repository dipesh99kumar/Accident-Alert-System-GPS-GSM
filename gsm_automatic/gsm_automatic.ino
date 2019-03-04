#include<SoftwareSerial.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
#include "TinyGPS++.h"
SoftwareSerial mySerial(A10, A11);
char msg;
char call;
  boolean ch=false;
MPU6050 mpu6050(Wire);

SoftwareSerial serial_connection(10, 11);
TinyGPSPlus gps;

void setup() {
  mySerial.begin(9600); 
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

}

void loop() {
  mpu6050.update();
  Serial.print("angleX : ");
  Serial.print(mpu6050.getAngleX());
  Serial.print("\tangleY : ");
  Serial.print(mpu6050.getAngleY());
  Serial.print("\tangleZ : ");
  Serial.println(mpu6050.getAngleZ());
 
  float ang_x=mpu6050.getAngleX();
  float ang_y=mpu6050.getAngleY();
  float ang_z=mpu6050.getAngleZ();
  if ((abs(ang_x)>30)||(abs(ang_y)>30))
  {
     // Setting the baud rate of Serial Monitor (Arduino)
   Serial.println("GSM SIM900A BEGIN"); 
    /* while(serial_connection.available())//While there are characters to come from the GPS
    { gps.encode(serial_connection.read());//This feeds the serial NMEA data into the library one char at a time
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
    
  }
  Serial.println();
  */
  delay(100);
    if (ch==false)
    {SendMessage();
      ch=true;
    }
  }
 if (mySerial.available()>0)
 Serial.write(mySerial.read());
 exit(0);
  }




void SendMessage()
{
  Serial.println("Function called");
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+917381765580\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println(gps.location.lat(), 6);
  mySerial.println(gps.location.lng(), 6);// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  exit(0);
}

void ReceiveCall()
{
  mySerial.println("ATA");
  delay(1000);
  {
    call=mySerial.read();
    Serial.print(call);
  }
}


