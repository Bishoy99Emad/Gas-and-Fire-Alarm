//FIRE , GAS & Smoke ALARM with Action 

//4/5/22: start
//4/18/22: first full trial with servo
//4/19/22: putting push button
//4/30/22: updated servo stop func.
//5/6/22: futaba s3003 is not the good choice for the project
//5/17/22: SG90 180deg servo is working smoothly with push button

//Libararies
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Set the LCD address to 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myservo;

//Power LED
int Power = 3;

//Servo
#define servoPin 9
#define PushButton 2 

// angles for servo control
int angle = 90;
// initial angle = 90 degree
int Angle = 90;    
// Angle of servo moves every 10 degree
int Angle_Movement = 10;
// initial Minimum Distance
const int MinimumAngle = 0;
// Initial Maximum distance
const int MaximumAngle = 180;

//Gas
int buzzergas = 12;
int GASA0 = A0;
int LEDgas = 10;
int gasvalue;

//Flame
int LEDfire = 7;
int flame_sensor = 4;
int buzzerfire = 13;
int flame_detected;

void setup() {

 //Power
 pinMode(Power, OUTPUT);

 //Servo
 myservo.attach(servoPin); 
 pinMode(PushButton,INPUT_PULLUP);

 //Gas
 pinMode(buzzergas, OUTPUT); 
 pinMode(LEDgas, OUTPUT); 
 
 //Flame
 pinMode(LEDfire, OUTPUT);
 pinMode(flame_sensor, INPUT);
 pinMode(buzzerfire, OUTPUT); 
 
 //LCD
 lcd.begin();               
 lcd.backlight(); 
 Serial.begin(9600);
 lcd.setCursor(3,0);
 lcd.print("welcome to"); 
 lcd.setCursor(1,1);
 lcd.print("BISMO  PROJECT");
 
 delay(4000);
}

void loop() 
{
  
  //MQ-2 
  int analogSensor = analogRead(GASA0);      //in PPM
  //int gasvalue=(analogSensor-50)/35;       //gas module sensitivity in percentage
  int gasvalue=analogSensor;
  digitalWrite(Power, HIGH);
  lcd.setCursor(0,0);
  lcd.print("GAS Level:");
  lcd.setCursor(10,0);
  lcd.print(gasvalue);
  lcd.setCursor(13,0);
  lcd.print("PPM");           //PPM
  //lcd.print("%");           //%

  if (gasvalue >= 530)              //gas PPM alert
  //if (gasvalue >= 10)              //gas percentage alert
  {
    lcd.setCursor(0,1);
    lcd.print("DANGER");       
    lcd.setCursor(9,1);
    lcd.print("GAS-SMK");                          
    tone(buzzergas, 10000, 400);
    digitalWrite(LEDgas, HIGH);
    delay(200);
    digitalWrite(LEDgas, LOW);
    delay(200);
  }

  else if (gasvalue < 530)
  //else if (gasvalue < 10)
  {
  lcd.setCursor(0,1);
  lcd.print("NORMAL");
  noTone(buzzergas);
  digitalWrite(LEDgas, LOW);
  }
  
  delay(500);

  //Flame
  flame_detected = digitalRead(flame_sensor);
  if (flame_detected == 1)
  {
    lcd.setCursor(0,1);
    lcd.print("DANGER"); 
    lcd.setCursor(9,1);
    lcd.print("FIRE!!!"); 
    tone(buzzerfire, 10000, 10000);
    digitalWrite(LEDfire, HIGH);
    delay(100);
    digitalWrite(LEDfire, LOW);
    delay(100);
  }
  
  else if (flame_detected != 1)
  {
    noTone(buzzerfire);
    digitalWrite(LEDfire, LOW);
  }
    if (flame_detected == 1 || gasvalue >= 580) 
    //if (flame_detected == 1 || gasvalue >= 12) {
    {

      while (angle<180)
      {

       for (angle = 0; angle <= 180; angle += 1) 
       {
         myservo.write(angle);
         tone(buzzergas, 100000, 100);
         delay(30);
       }
          if (angle==180)
          {
            break;
          }
      } 
    }

   while(digitalRead(PushButton) == LOW)
   {
    
    if(angle>=90)
    {
    
    for (angle = 180; angle >= 0; angle -= 1) 
     {
     myservo.write(angle);
     delay(30);
     }
    }
    
    else if (angle==0)
      break;
      
   } 
   
  lcd.clear();
  
}
