#include <LiquidCrystal.h>
#include <Servo.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

// Replace these with your network credentials
const char* ssid = ".....";
const char* password = "qwertyuiop";

// Replace these with your Firebase project credentials
#define FIREBASE_HOST "https://vehicle-parking-49b89-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "AIzaSyCi7K-FC94sSGF0VRkS53MLesV_beyKwoM"

FirebaseData firebaseData;
Servo servo_in;
Servo servo_out;
LiquidCrystal lcd(13, 12, 14, 27, 26, 25); //RS, EN, D4, D5, D6, D7

int total = 3;
int space;
int flag1 = 0;
int flag2 = 0;

void setup() 
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  pinMode(5, INPUT); //ENTRY IR
  pinMode(4, INPUT); //EXIT IR
  pinMode(3, INPUT); //P1
  pinMode(2, INPUT); //P2
  pinMode(1, INPUT); //P3

  lcd.begin(16, 2);
  servo_in.attach(23); //ENTRY SERVO
  servo_out.attach(22); //EXIT SERVO
  servo_in.write(90);
  servo_out.write(90);
  space = total;

  // Initialize Firebase with total and space values
  Firebase.setInt(firebaseData, "/parking/total", total);
  Firebase.setInt(firebaseData, "/parking/space", space);
}

void loop() 
{
  lcd.setCursor(0, 0);
  lcd.print("  Car Parking");
  lcd.setCursor(0, 1);
  lcd.print("    System");
  delay(1000);

  if (digitalRead(5) == 0 && flag1 == 0)
  {
    if (space > 0 && space <= total)
    {
      flag1 = 1; // Space is there
      servo_in.write(0);
      space = space - 1;
      Firebase.setInt(firebaseData, "/parking/space", space);
      delay(500);
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Sorry no space");
      lcd.setCursor(0, 1);
      lcd.print("Available");
      delay(1000);
      lcd.clear();
    }
  }

  if (digitalRead(4) == 0 && flag2 == 0 && space < total)
  {
    flag2 = 1;
    if (flag1 == 0)
    {
      servo_out.write(0);
      space = space + 1;
      Firebase.setInt(firebaseData, "/parking/space", space);
      delay(500);
    }
  }

  if (flag1 == 1) 
  {
    delay(3000);
    servo_in.write(90);
    flag1 = 0; 
  }

  if (flag2 == 1)
  {
    delay(3000);
    servo_out.write(90);
    flag2 = 0;
  }

  // Display total and available space on LCD and Serial Monitor
  lcd.setCursor(0, 0);
  lcd.print("Total Space: ");
  lcd.print(total);
  lcd.setCursor(0, 1);
  lcd.print("Left Space: ");
  lcd.print(space);
  
  Serial.print("Total Space: ");
  Serial.println(total);
  Serial.print("Left Space: ");
  Serial.println(space);

  // Update Firebase with total and available space
  Firebase.setInt(firebaseData, "/parking/total", total);
  Firebase.setInt(firebaseData, "/parking/space", space);

  // Display parked slots on LCD and Serial Monitor
  lcd.setCursor(0, 0);
  lcd.print("Parked Slots:");
  if (digitalRead(3) == 0)
  {
    lcd.setCursor(0, 1);
    lcd.print("P1");
    Serial.println("P1 is parked");
  }
  else
  {
    Serial.println("P1 is empty");
  }
  if (digitalRead(2) == 0)
  {
    lcd.setCursor(3, 1);
    lcd.print("P2");
    Serial.println("P2 is parked");
  }
  else
  {
    Serial.println("P2 is empty");
  }
  if (digitalRead(1) == 0)
  {
    lcd.setCursor(6, 1);
    lcd.print("P3");
    Serial.println("P3 is parked");
  }
  else
  {
    Serial.println("P3 is empty");
  }

  // Update Firebase with the parking status of each slot
  Firebase.setBool(firebaseData, "/parking/P1", digitalRead(3) == 0);
  Firebase.setBool(firebaseData, "/parking/P2", digitalRead(2) == 0);
  Firebase.setBool(firebaseData, "/parking/P3", digitalRead(1) == 0);

  delay(1000);
  lcd.clear();
}
