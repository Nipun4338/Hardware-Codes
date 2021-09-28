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
using namespace std;

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'7','8','9', '/'},
  {'4','5','6', 'x'},
  {'1','2','3', '-'},
  {'*','0','#', '+'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad
String password="*124";
int currentposition=0;
bool flag=0;
bool operation=0;
int digit=0;
char sign='0';

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
      if (customKey>='0' && customKey<='9' && operation==0){
        digit=customKey-'0';
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(customKey);
      }
      else if (customKey>='0' && customKey<='9' && operation==1){
        lcd.print(customKey);
        if(sign=='+')
        {
          int digit2=customKey-'0';
          int ans=digit+digit2;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(ans);
        }
        else if(sign=='-')
        {
          int digit2=customKey-'0';
          int ans=digit-digit2;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(ans);
        }
        else if(sign=='/')
        {
          int digit2=customKey-'0';
          int ans=digit/digit2;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(ans);
        }
        //Reverse
        operation=0;
      }
      else if(customKey=='+' || customKey=='-' || customKey=='/')
      {
        sign=customKey;
        operation=1;
        lcd.print(customKey);
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
