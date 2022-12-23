#include <SoftwareSerial.h>

// Connect nodeMCU with Arduino R3 
SoftwareSerial nodemcu(2,3);

// Parking slot1 infrared sensor connected with pin number 4 of arduino
int parking1_slot1_ir_s = 4; 
int parking1_slot2_ir_s = 5;
int parking1_slot3_ir_s = 6;
int parking1_slot4_ir_s = 7;

// Data for each IR sensor
String sensor1; 
String sensor2; 
String sensor3; 
String sensor4; 

// Total Parking Car Slot
int countSlot = 4;

// Complete data, consisting of sensors values
String cdata ="";

void setup()
{
  Serial.begin(9600); 
  nodemcu.begin(9600);

  pinMode(parking1_slot1_ir_s, INPUT);
  pinMode(parking1_slot2_ir_s, INPUT);
  pinMode(parking1_slot3_ir_s, INPUT);
  pinMode(parking1_slot4_ir_s, INPUT);
}

void loop()
{
// Call the function below for each parking slot
  p1slot1(); 
  p1slot2();
  p1slot3(); 
  p1slot4();

// Comma will be used a delimeter
  cdata = cdata + sensor1 +"," + sensor2 + ","+ sensor3 +","+ sensor4 + ","; 
  Serial.println(cdata); 

// Send data to nodeMCU
  nodemcu.println(cdata);
  delay(6000); // 100 milli seconds

// Resert data in loop()
  cdata = ""; 

  digitalWrite(parking1_slot1_ir_s, HIGH); 
  digitalWrite(parking1_slot2_ir_s, HIGH); 
  digitalWrite(parking1_slot3_ir_s, HIGH);
  digitalWrite(parking1_slot4_ir_s, HIGH);
}


void p1slot1() // parkng 1 slot1
{
  if( digitalRead(parking1_slot1_ir_s) == LOW) 
  {
    sensor1 = "255";
    delay(200); 
  } 
  if( digitalRead(parking1_slot1_ir_s) == HIGH)
  {
    sensor1 = "0";  
    delay(200);  
  }
}

void p1slot2() // parking 1 slot2
{
  if( digitalRead(parking1_slot2_ir_s) == LOW) 
  {
    sensor2 = "255"; 
    delay(200); 
  }
  if( digitalRead(parking1_slot2_ir_s) == HIGH)  
  {
    sensor2 = "0";  
    delay(200);
  } 
}


void p1slot3() // parking 1 slot3
{
  if( digitalRead(parking1_slot3_ir_s) == LOW) 
  {
    sensor3 = "255"; 
    delay(200); 
  }
  if( digitalRead(parking1_slot3_ir_s) == HIGH)  
  {
    sensor3 = "0";  
    delay(200);
  } 
}

void p1slot4() // parking 1 slot4
{
  if( digitalRead(parking1_slot4_ir_s) == LOW) 
  {
    sensor4 = "255"; 
    delay(200); 
  }
  if( digitalRead(parking1_slot4_ir_s) == HIGH)  
  {
    sensor4 = "0";  
    delay(200);
  } 
}