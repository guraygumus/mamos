#include <DS3231.h>
#include <Servo.h>
Servo myservo;

DS3231  rtc(SDA, SCL);  // Init the DS3231 using the hardware interface
Time t;
const int servoPin = 9;

void setup()
{
  
  Serial.begin(115200);
  // Uncomment the next line if you are using an Arduino Leonardo
  //while (!Serial) {}
  
  rtc.begin();  // Initialize the rtc object  
  myservo.attach(servoPin); // Initialize the servo object

  
  myservo.write(0);
  delay(1000);
  myservo.detach();

  //pinMode(13,OUTPUT);  // ledle ekstra kontrol için bu satır aktif hale getirilebilir
  
  // The following lines can be uncommented to set the date and time
  //rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
 // rtc.setTime(13, 37, 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(1, 5, 2019);   // Set the date to January 1st, 2014
}

void loop()
{
  t = rtc.getTime();  //rtc den zaman datasını al
  
  Serial.println(rtc.getTimeStr());  // o anki zamanı seriale yazdır
 
   
  
 if (t.hour==12 && t.min==19 && t.sec==0){
  
   myservo.attach(servoPin);
    myservo.write(42);
    delay(15000);  // kapının acilip yem dökme saniyesi
    myservo.write(0);
    delay(1500);
    myservo.detach(); //servonun stall da harcayacagi voltaji onlemek icin
 
  /*
  digitalWrite(13,HIGH);
  delay(20000);
  digitalWrite(13,LOW);
  delay(500);
  */
    }
    delay(13); // servo kendini toplasın diye ama cıkarılabılır eger hemen tekrar harekete gecırmıceksek 
   
 if (t.hour==12 && t.min==20 && t.sec==0){

  
   myservo.attach(servoPin);
    myservo.write(42);
    delay(10000);
    myservo.write(0);
    delay(100);
    myservo.detach(); //servonun stall da harcayacagı voltajı onlemek ıcın
    

  /*
  digitalWrite(13,HIGH);
  delay(20000);
  digitalWrite(13,LOW);
  delay(500);
   */
    }
      delay(13); // servo kendini toplasın diye ama cıkarılabılır eger hemen tekrar harekete gecırmıceksek 
}
