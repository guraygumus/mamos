// DS3231_Serial_Easy
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// A quick demo of how to use my DS3231-library to 
// quickly send time and date information over a serial link
//
// To use the hardware I2C (TWI) interface of the Arduino you must connect
// the pins as follows:
//
// Arduino Uno/2009:
// ----------------------
// DS3231:  SDA pin   -> Arduino Analog 4 or the dedicated SDA pin
//          SCL pin   -> Arduino Analog 5 or the dedicated SCL pin
//
// Arduino Leonardo:
// ----------------------
// DS3231:  SDA pin   -> Arduino Digital 2 or the dedicated SDA pin
//          SCL pin   -> Arduino Digital 3 or the dedicated SCL pin
//
// Arduino Mega:
// ----------------------
// DS3231:  SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA pin
//          SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL pin
//
// Arduino Due:
// ----------------------
// DS3231:  SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA1 (Digital 70) pin
//          SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL1 (Digital 71) pin
//
// The internal pull-up resistors will be activated when using the 
// hardware I2C interfaces.
//
// You can connect the DS3231 to any available pin but if you use any
// other than what is described above the library will fall back to
// a software-based, TWI-like protocol which will require exclusive access 
// to the pins used, and you will also have to use appropriate, external
// pull-up resistors on the data and clock signals.
//

#include <DS3231.h>
#include <Servo.h>
Servo myservo;

// Init the DS3231 using the hardware interface
DS3231  rtc(SDA, SCL);
Time t;
const int servoPin = 8;

void setup()
{
  // Setup Serial connection
  Serial.begin(115200);
  // Uncomment the next line if you are using an Arduino Leonardo
  //while (!Serial) {}
  
  // Initialize the rtc object
  rtc.begin();
  // Initialize the servo object
  myservo.attach(servoPin);
  myservo.write(180);
  delay(1000);
  myservo.detach();
  
  // The following lines can be uncommented to set the date and time
 // rtc.setDOW(SUNDAY);     // Set Day-of-Week to SUNDAY
  // rtc.setTime(10, 10, 0);     // Set the time to 12:00:00 (24hr format)
 //rtc.setDate(28, 4, 2019);   // Set the date to January 1st, 2014
}

void loop()
{
  t = rtc.getTime();  //rtc den zaman datasını al
  
  Serial.println(rtc.getTimeStr());  // o anki zamanı seriale yazdır
  
 if (t.hour==12 && t.min==4 && t.sec==0){
  
   //myservo.attach(servoPin);
    myservo.write(90);
    delay(575);
    myservo.write(180);
    delay(1500);
    myservo.detach();
    delay(5000);

  digitalWrite(13,HIGH);
  delay(20000);
  digitalWrite(13,LOW);
  delay(500);
    }
    delay(13); // servo kendini toplasın diye ama cıkarılabılır eger hemen tekrar harekete gecırmıceksek 
   
 if (t.hour==12 && t.min==5 && t.sec==0){

  
   myservo.attach(servoPin);
    myservo.write(42);
    delay(575);
    myservo.write(0);
    delay(1500);
    myservo.detach();
    delay(5000);


  digitalWrite(13,HIGH);
  delay(20000);
  digitalWrite(13,LOW);
  delay(500);
    }
      delay(13); // servo kendini toplasın diye ama cıkarılabılır eger hemen tekrar harekete gecırmıceksek 
}
