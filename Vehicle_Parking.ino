#include<LiquidCrystal.h>
#include<Servo.h>
Servo servo_in;
Servo servo_out;
LiquidCrystal lcd(13,12,11,10,9,8);
int total=3;
int space;
int flag1=0;
int flag2=0;

void setup() 
{
  pinMode(5,INPUT);//A0
  pinMode(4,INPUT);
  pinMode(3,INPUT);
  pinMode(2,INPUT);
  pinMode(1,INPUT);
  lcd.begin(16,2);
  servo_in.attach(7);
  servo_out.attach(6);
  servo_in.write(90);
  servo_out.write(90);
  space=total;
}

void loop() 
{
  lcd.setCursor(0,0);
  lcd.print("  Car Parking");
  lcd.setCursor(0,1);
  lcd.print("    System");
  delay(1000);
  if(digitalRead(5)==0 && flag1==0)
  {
    if(space>0 && space<=total)
    {
      flag1=1; //Space is there
      //if(flag2==0)
      {
        servo_in.write(0);
        space=space-1;
        delay(500);
      }
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Sorry no space");
      lcd.setCursor(0,1);
      lcd.print("Available");
      delay(1000);
      lcd.clear();
    }
  }
  if(digitalRead(4)==0 && flag2==0 && space<total)
  {
    flag2=1;
    if(flag1==0)
    {
      servo_out.write(0);
      space=space+1;
      delay(500);
    }
  }
  
  if(flag1==1) 
  {
    delay(3000);
    servo_in.write(90);
    flag1=0; 
   }
  if(flag2==1)
  {
    delay(3000);
    servo_out.write(90);
    flag2=0;
  }
  lcd.setCursor(0,0);
  lcd.print("Total Space: ");
  lcd.print(total);
  lcd.setCursor(0,1);
  lcd.print("Left Space: ");
  lcd.print(space);
  delay(1000);
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Parked Slots:");
  if(digitalRead(3)==0)
  {
    lcd.setCursor(0,1);
    lcd.print("P1");
  }
  if(digitalRead(2)==0)
  {
    lcd.setCursor(3,1);
    lcd.print("P2");
  }
  if(digitalRead(1)==0)
  {
    lcd.setCursor(6,1);
    lcd.print("P3");
  }
  delay(1000);
  lcd.clear();
  //Serial.println(analogRead(A1));
}
