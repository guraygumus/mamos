// Set the feeding time and feed your birds without considering the time by using a DS3231 module. Display date, time and temperature as well.
// By using buttons on the breadboard you can set the feeding time, defined as Left, Right, OK and END buttons.
// There are four different screens as menu options you switch using buttons:
// HomeScreen
// It is the interface of RTC Bird Feeder that shows date, time and temperature values.
// The Feeding Time Set Screen
// Set the feeding time in 24hr format.
// The Remaining Time Get Screen
// Get remaining time to the feeding time when it is activated.
// Status Check Screen
// It chacks whether the system is activated or not by using OK button.
//
// CONNECTIONS
// Arduino Uno(CH340):  
//--------------------------------------------------         
// 12 X 6 LCD SCREEN:
// D12---------- LCD RS pin 
// D11---------- LCD Enable pin
// D5---------- LCD D4 pin 
// D4---------- LCD D5 pin
// D3---------- LCD D6 pin 
// D2---------- LCD D7 pin 
// GND---------- LCD R/W pin
// 10K resistor:
// ends to +5V and ground
// wiper to LCD VO pin (pin 3)
//--------------------------------------------------
// SERVO:
// D9---------- Servo SG-90 (Joint_1)

//--------------------------------------------------

// DS3231 RTC circuit:
// A4----------SDA  
// A5---------- SCL
// VIN----------VCC
// GND----------GND

//-------------------------------------------------
// BUTTONS:                               
// A0---------- Left Button                             
// A1---------- OK Button                              
// A2---------- Right Button                               
// A3---------- End Button


#include <DS3231.h>
DS3231  rtc(SDA, SCL);

#include <LiquidCrystal.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Include servo library and define their names.
#include <Servo.h>
Servo Joint_1;


// Create lcd characters from bytes.
byte clocK[8] = {
0b01010,
0b01010,
0b11011,
0b10001,
0b10101,
0b10101,
0b10001,
0b11111,
};

byte X[8] = {
0b00000,
0b10001,
0b01010,
0b00100,
0b01010,
0b10001,
0b00000,
0b00000,
};

byte smile[8] = {
0b00000,
0b01010,
0b00000,
0b00100,
0b10001,
0b10001,
0b10001,
0b11111,  
};




// Define button pins.
#define Left_B A0
#define OK_B A1
#define Right_B A2
#define END A3

// Define button values.
int Left;
int OK;
int Right;
int End;

// Define menu options and variables to adjust the feeding time.
boolean Set_Feed_Time;
boolean Get_Remaining_Time;
boolean Status_Check;
// Check and test the feeding system.
boolean Activated = false;

// Define a time variable to get data from DS3231 properly.
Time t;

// Define feed hour and minute.
int feedHour;
int feedMin;

void setup(){

lcd.begin(16, 2);      // Initial lcd screen.  

rtc.begin();           // Initialize the rtc object

// Attach servo motors to pwm pins.
Joint_1.attach(9); // Attach servo motors to pwm pins.


// Start pimMode();
  pinMode(Left_B, INPUT);
  pinMode(OK_B, INPUT);
  pinMode(Right_B, INPUT);

// The following lines can be uncommented to set the date and time
// rtc.setDOW(FRIDAY);     // Set Day-of-Week to Wednesday
 // rtc.setTime(00, 28, 0);     // Set the time to 12:00:00 (24hr format)
 //rtc.setDate(25, 05, 2019);   // Set the date to October 17st, 2018

} 

void loop(){
// Get the current hour and minute from DS3231. t.hour; and t.min;
t = rtc.getTime();

// Start servo motors.
Joint_1.write(0);


 createLCD(); 

 ReadButtons();

 HomeScreen();

 Set_Feeding_Time(); // OK Button at the homescreen.

 Get_Remaining_Time_(); // Left Button at the homescreen.

 Status_Check_(); // Right Button at the homescreen.

 Feeding_Time();

}

void ReadButtons(){
  // Read button with anolog pins.
   Left = digitalRead(Left_B);
   OK = digitalRead(OK_B);
   Right = digitalRead(Right_B);
   End = digitalRead(END);
  }
  
void createLCD(){
  // Create lcd characters at the beginning of the code above.
  lcd.createChar(1, clocK);
  lcd.createChar(2, X);
  lcd.createChar(3, smile);

  }

 void HomeScreen(){
  // Code a homescreen for RTC Bird Feeder.
  lcd.setCursor(0, 0);
  lcd.print("MAMOS");
  // Write Dow
  lcd.setCursor(8, 1);
  lcd.print(rtc.getDOWStr(FORMAT_SHORT));
  // Write Date
  lcd.setCursor(6, 0);
  lcd.print(rtc.getDateStr(FORMAT_SHORT));
  // Write Time
  lcd.setCursor(0, 1);
  lcd.print(rtc.getTimeStr());

  }

 void Set_Feeding_Time(){
 if(OK == HIGH){
  Set_Feed_Time = true;
  // While OK is HIGH, it turns the homescreen to the feeding time set screen.
  if(Set_Feed_Time == true){
    lcd.clear();
    // Activate the feeding system.
    Activated = true;
    while(Set_Feed_Time == true){
      // Adjust the feeding time by either increasing or decreasing variables through the feeding time set screen.
      ReadButtons();
      lcd.setCursor(0, 0);
      lcd.print("Set Feeding Time");
     // lcd.setCursor(0, 2); EKRANA SIGMAZ CIKART
      // lcd.print("Left"); EKRANA SIGMAZ CIKART
      lcd.setCursor(0, 1);
      lcd.print("Hour:");
      lcd.print(feedHour);
     // lcd.setCursor(10, 2); EKRANA SIGMAZ CIKART
      //lcd.print("Right");  EKRANA SIGMAZ CIKART
      lcd.setCursor(8, 1);
      lcd.print("Min:");
      lcd.print(feedMin);

      // Change feedHour and feedMin by using left and right buttons.
      if(Right == HIGH){
        feedMin++;
        delay(100);
          if(feedMin > 59){
          // It has to be bewtween 0 and 59 in 60 minutes.
          feedMin = 0;
          lcd.clear();
          }
        }
      if(Left == HIGH){
        feedHour++;
        delay(100);
        if(feedHour > 23){
          // It has to be bewtween 0 and 23 in 24hr format.
          feedHour = 0;
          lcd.clear();
          }
        }
      // Control OK button to turn the feeding time set screen to the homescreen.
      if(End == HIGH){
        // End task and turn back the homescreen.
        Set_Feed_Time = false;
        lcd.clear();
        }
      }
    }
  }
  }

 void Get_Remaining_Time_(){
  if(Left == HIGH){
    Get_Remaining_Time = true;
    // While Left is HIGH, it turns the homescreen to the get remaining time screen.
    if(Get_Remaining_Time == true){
      lcd.clear();
      while(Get_Remaining_Time == true){
        ReadButtons();
        // Get the remaining time for the feeding time.
        lcd.setCursor(0, 0);
        lcd.print("Kalan sure ");
        lcd.write(1);
        lcd.setCursor(0, 1);
        if(Activated == false){
           lcd.print("Not Activated-");
           lcd.write(2);
          }else if(Activated == true){
            if(t.hour > feedHour){
               lcd.setCursor(0, 1); //BUNU ARAYA BEN EKLEDIM CIKARIP BIDAHA DENICEM OLMAZSA
             lcd.print(24 - (t.hour - feedHour));
             }else if(t.hour <= feedHour){
              lcd.print(abs(t.hour - feedHour));
              }
          lcd.print(" hours ");
          if(t.min > feedMin){
            lcd.print(60 - (t.min - feedMin));
            }else if(t.min <= feedMin){
              lcd.print(abs(t.min - feedMin));
              }
          lcd.print(" min ");
         }
         
        // Control OK button to turn the feeding time set screen to the homescreen.
        if(End == HIGH){
         // End task and turn back the homscreen.
         Get_Remaining_Time = false;
         lcd.clear();
         } 
        }
      }
    }
  }

  void Status_Check_(){
    if(Right == HIGH){
      Status_Check = true;
      //  While Right is HIGH, it turns the homescreen to the status check screen.
      if(Status_Check == true){
        lcd.clear();
        while(Status_Check == true){
          ReadButtons();
          // Check the system whether it is activated or not.
          lcd.setCursor(0, 0);
          lcd.print("Status Check :");
          lcd.setCursor(0, 1);
          if(Activated == false){
            lcd.print("Not Activated-");
            lcd.write(2);
            }else if(Activated == true){
              lcd.print("Running - ");
              lcd.write(3);
              }

          // Control OK button to turn the feeding time set screen to the homescreen.
          if(End == HIGH){
           // End task and turn back the homscreen.
           Status_Check = false;
           lcd.clear();
          } 
          }
        }
      }
    }

  void Feeding_Time(){
    // Check whether the feeding time is set or not.
    if(Activated == true){
      if(t.hour == feedHour && t.min == feedMin){
        // Activate the feeding systems by adjusting servos.
        Joint_1.write(45);
        delay(300);
        // Return system values after activation.
        Activated = false;
        }
      }
    
    }
