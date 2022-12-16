#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define LED_R 4 //define red LED pin 
#define LED_B 5 //define blue LED
#define BUZZER 2 //buzzer pin
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
Servo myServo; //define servo name

int ir = 7;
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  myServo.attach(3); //servo pin
  myServo.write(0); //servo start position
  pinMode(LED_R, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(ir, INPUT);
  noTone(BUZZER);
  Serial.println("Put your card to the reader...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], DEC);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], DEC));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (digitalRead(ir) == LOW)
  {
    if (content.substring(1) == "91 120 87 00") //change here the UID of the card/cards that you want to give access
    {
      Serial.println("Authorized access");
      delay(500);
      digitalWrite(LED_R, HIGH);
      tone(BUZZER, 500);
      delay(300);
      noTone(BUZZER);
      myServo.write(90);
      Serial.println("Gate Opened");
      delay(2500);
      if (digitalRead(ir) == HIGH)
      {
        myServo.write(0);
        Serial.println("Gate Closed");
        Serial.println();
        digitalWrite(LED_R, LOW);
      }
    }  
    else
    {
      Serial.println(" Access denied");
      Serial.println();
      digitalWrite(LED_B, HIGH);
      tone(BUZZER, 300);
      delay(1000);
      digitalWrite(LED_B, LOW);
      noTone(BUZZER);
    }
  } 
}