#include <LiquidCrystal.h>
#include "TinyGPS++.h"
#include "SoftwareSerial.h"
#include<Wire.h>

#include<MPU6050_tockn.h>
SoftwareSerial mySerial(A10, A11);
SoftwareSerial serial_connection(10,11); 
TinyGPSPlus gps;
LiquidCrystal lcd(8, 9, 2, 3, 4, 5);
MPU6050 mpu6050(Wire);

void setup()
{
  mySerial.begin(9600); 
  Serial.begin(9600);//This opens up communications to the Serial monitor in the Arduino IDE
  serial_connection.begin(9600);//This opens up communications to the GPS
  Serial.begin(9600);
  Serial.println("GPS Start");//Just show to the monitor that the sketch has started
  Wire.begin();
  lcd.begin(16, 2);
  Serial.begin(9600);
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
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
 
  float ang_x=mpu6050.getAngleX();
  float ang_y=mpu6050.getAngleY();
  float ang_z=mpu6050.getAngleZ();
  while(serial_connection.available())//While there are characters to come from the GPS
  {
     gps.encode(serial_connection.read());//This feeds the serial NMEA data into the library one char at a time
  }
  if ((abs(ang_x)>30)||(abs(ang_y)>30))
  {
      
     if(gps.location.isUpdated())//This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
     {
        Serial.println("Satellite Count:");
        Serial.println(gps.satellites.value());
        Serial.println("Latitude:");
        Serial.println(gps.location.lat(), 6);
        Serial.println("Longitude:");
        Serial.println(gps.location.lng(), 6);
      }
      lcd.print("Accident Happened At ....");
      delay(2000);
      delay(1000);
      lcd.clear();
      lcd.print("LAT:");lcd.print(gps.location.lat(),6);
      lcd.setCursor(0,1);
      
      lcd.print("LONG:");lcd.print(gps.location.lng(),6);
      delay(5000);
      lcd.clear();
      lcd.print("Are u safe ??");
      lcd.setCursor(0,2);
      lcd.print("If Safe Press R");
      delay(5000);
      lcd.print("Timeout");
      lcd.clear();      
      Serial.println("GSM SIM900A BEGIN"); 
      Serial.println();
      delay(100);
      char ch='s';
      switch(ch)
      {
        case 's':
        SendMessage();
        break;
      }
      if (mySerial.available()>0)
        Serial.write(mySerial.read());
      exit(0);
   }

}
void SendMessage()
{
  float a,b;
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919178672627\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Accident Happened At Location:\n");
  delay(1000);
  mySerial.println("Latitude:");
  mySerial.println(gps.location.lat(), 6);
  delay(100);
  mySerial.println("Longitude:");
  mySerial.println(gps.location.lng(), 6);
  delay(100);
  mySerial.println("http://www.google.com/maps/place/gps.location.lat(),gps.location.lng()");
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}
/*void MakeCall()
{
  mySerial.println("ATD+919178672627;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
  Serial.println("Calling  "); // print response over serial port
  delay(1000);
}*/


/*

* $GPRMC,183729,A,3907.356,N,12102.482,W,000.0,360.0,080301,015.5,E*6F

$GPRMB,A,,,,,,,,,,,,V*71

$GPGGA,183730,3907.356,N,12102.482,W,1,05,1.6,646.4,M,-24.1,M,,*75

$GPGSA,A,3,02,,,07,,09,24,26,,,,,1.6,1.6,1.0*3D

$GPGSV,2,1,08,02,43,088,38,04,42,145,00,05,11,291,00,07,60,043,35*71

$GPGSV,2,2,08,08,02,145,00,09,46,303,47,24,16,178,32,26,18,231,43*77

$PGRME,22.0,M,52.9,M,51.0,M*14

$GPGLL,3907.360,N,12102.481,W,183730,A*33

$PGRMZ,2062,f,3*2D

$PGRMM,WGS 84*06

$GPBOD,,T,,M,,*47

$GPRTE,1,1,c,0*07

$GPRMC,183731,A,3907.482,N,12102.436,W,000.0,360.0,080301,015.5,E*67

$GPRMB,A,,,,,,,,,,,,V*71

*/
