/* @file CustomKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates changing the keypad size and key values.
|| #
*/
#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8}; //connect to the column pinouts of the keypad
String password="*124";
int currentposition=0;
bool flag=0;

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Loading/Initializing");
  lcd.clear();
  lcd.setCursor(0, 0);
}
  
void loop(){
  int l ;
  String check="";
  char customKey = customKeypad.getKey();
  if (customKey){
    lcd.print(customKey);
    currentposition++;
    if(customKey==password[currentposition-1] && currentposition==4 && flag==0)
    {
      flag=1;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Welcome!");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      currentposition=0;
      customKey='0';
    }
    if(flag==1)
    {
      int LeftMotorForward=7;
      int LeftMotorReverse=6;
      pinMode(LeftMotorForward, OUTPUT);
      pinMode(LeftMotorReverse, OUTPUT);
      if (customKey=='4'){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Clockwise direction");
        //Reverse
        digitalWrite(LeftMotorForward, HIGH);
        digitalWrite(LeftMotorReverse, LOW);
        delay(3000);
        customKey='0';
      }
      if(customKey=='5')
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("anti-Clockwise direction");
        //Reverse
        digitalWrite(LeftMotorReverse, HIGH);
        digitalWrite(LeftMotorForward, LOW);
        delay(3000);
        customKey='0';
      }
      if(customKey=='6')
      {
        //STOP
        digitalWrite(LeftMotorReverse, LOW);
        digitalWrite(LeftMotorForward, LOW);
        delay(3000);
        customKey='0';
      }
      currentposition=0;
    }
    else if(customKey!=password[currentposition-1] && flag==0)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Incorrect Password");
      delay(2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      currentposition=0;
    }
  }
}

void motor()
{
  int LeftMotorForward=7;
  int LeftMotorReverse=6;
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorReverse, OUTPUT);
  while(true)
  {
    lcd.print("Clockwise direction");
    lcd.clear();
  char customKey = customKeypad.getKey();
  if (customKey=="4"){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Clockwise direction");
      delay(3000);
      //Reverse
      digitalWrite(LeftMotorForward, HIGH);
      digitalWrite(LeftMotorReverse, LOW);
      delay(3000);
    }
    if(customKey=="5")
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("anti-Clockwise direction");
      //Reverse
      digitalWrite(LeftMotorReverse, HIGH);
      digitalWrite(LeftMotorForward, LOW);
      delay(3000);
    }
    if(customKey=="6")
    {
      //STOP
      digitalWrite(LeftMotorReverse, LOW);
      digitalWrite(LeftMotorForward, LOW);
      delay(3000);
    }
  }
}
