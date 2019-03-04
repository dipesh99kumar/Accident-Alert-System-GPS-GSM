# Accident-Alert-System-GPS-GSM
In this project, an IOT based vehicle accident detection and the rescue information system is developed in order to detect the vehicle accident and send the location data to vehicle owner,nearest hospital

Requirements -
1. Arduino 
2. GPS Module 
3. GSM MODULE - SIM 800L
4. Accelerometer/Gyroscope MPU6050
5. LCD Display

The Micro Controller Arduino detects if any accident happens via the gyroscope mpu6050 that measures the change in axis of the vehicle.

 If any changes occurs then Arduino reads from GPS module data and sends SMS to the predefined number, to the police and nearest hospital with the location coordinates of accident place.  In case of any minor incident, the driver can himself handle at the situation and avoid the sending of details to the hospital or guardian by pressing the button.If the driver is not in a condition to press it within 60 sec. then oly the details will be sent.  The message also contains a Google Map link to the accident location, so that location can be easily tracked.

The vehicle is provided with a button.If the button is pressed within 60 sec. then no message will be sent,since it is a minor one and no need to inform at home or the hospital. If the button is not pressed, then it implies a severe accident and action must be taken to save him/her.

The code is divided and checked for individual connections with GPS,GSM,Gyroscope.And after verifying All.ino contains the final code for the system
