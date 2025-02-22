#include <LiquidCrystal.h>
LiquidCrystal lcd(13,12,11,10,9,8);

void setup() 
{
  pinMode(7,INPUT);
  pinMode(6,INPUT);
  pinMode(5,INPUT);
  pinMode(4,INPUT);
  lcd.begin(16,2);
}

void loop() 
{
  lcd.setCursor(0,0);
  lcd.print("Street Parking");
  lcd.setCursor(0,1);
  lcd.print("System");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Parked slots:");
  
  if(digitalRead(7)==0) 
  {
    lcd.setCursor(0,1);
    lcd.print("P1");
  }
  
  if(digitalRead(6)==0) 
  {
    lcd.setCursor(3,1);
    lcd.print("P2"); 
  }
  
  if(digitalRead(5)==0) 
  {
    lcd.setCursor(6,1);
    lcd.print("P3");
  }
  if(digitalRead(4)==0) 
  {
    lcd.setCursor(9,1);
    lcd.print("P4");
  }
  
  
delay(1000);
lcd.clear();
}
