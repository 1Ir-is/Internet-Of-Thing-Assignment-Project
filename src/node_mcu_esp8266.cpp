#define BLYNK_TEMPLATE_ID "TMPLrsDs6VSC"
#define BLYNK_DEVICE_NAME "CarParking"
#define BLYNK_AUTH_TOKEN "iWVkPfxZajXAcXFdIcv_r7N5PkI_F6xE"


#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#include <SimpleTimer.h>
#include <Firebase_ESP_Client.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
char ssid[] = "Greenwich-Student";
char pass[] = "12345678";

SimpleTimer timer;

String myString; // complete message from arduino, which consists of sensors data
char rdata; // received characters

int firstVal, secondVal,thirdVal; // sensors 
int led1,led2,led3,led4,led5,led6;
// This function sends Arduino's up time every second to Virtual Pin (1).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.


// firebase
#define DATABASE_URL "https://asm2-iot-4d758-default-rtdb.firebaseio.com/" // Firebase host
#define API_KEY "AIzaSyBJxKEnG8oDBmf4i7VFK_5HA-sSwWSvp5o" //Firebase Auth code
int fireStatus = 0;


FirebaseData control_data;

FirebaseAuth AUTH;
FirebaseConfig config;
bool signupOK = false;


//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, millis() / 1000);
  
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  timer.setInterval(1000L,sensorvalue1); 
  timer.setInterval(1000L,sensorvalue2); 
  timer.setInterval(1000L,sensorvalue3);
  timer.setInterval(1000L,sensorvalue4);
  timer.setInterval(1000L,sensorvalue5);
  timer.setInterval(1000L,sensorvalue6);
  


  // firebase
  WiFi.begin(ssid, pass);
   Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &AUTH, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &AUTH);
  Firebase.reconnectWiFi(true);
}

void loop()
{
  if (Serial.available() == 0 ) 
  {
    Blynk.run();
    timer.run(); // Initiates BlynkTimer
  }
   
  if (Serial.available() > 0 ) 
  {
    rdata = Serial.read(); 
    myString = myString+ rdata; 
    //Serial.print(rdata);
    if( rdata == '\n')
    {
      Serial.println(myString); 
      // Serial.println("fahad");
      // new code
      String l = getValue(myString, ',', 0);
      String m = getValue(myString, ',', 1);
      String n = getValue(myString, ',', 2);
      String o = getValue(myString, ',', 3);
      String p = getValue(myString, ',', 4);
      String q = getValue(myString, ',', 5);


      // these leds represents the leds used in Blynk application
      led1 = l.toInt();
      led2 = m.toInt();
      led3 = n.toInt();
      led4 = o.toInt();
      led5 = p.toInt();
      led6 = q.toInt();

        myString = "";
      // end new code
    }
  }

  if (Firebase.ready() && signupOK ) {
    Serial.print("Connect successfuly!");
    // implement
    if (Serial.available() > 0 ) 
  {
    rdata = Serial.read(); 
    myString = myString+ rdata; 
    //Serial.print(rdata);
    if( rdata == '\n')
    {
      Serial.println(myString); 
      // Serial.println("fahad");
      // new code
      String l = getValue(myString, ',', 0);
      String m = getValue(myString, ',', 1);
      String n = getValue(myString, ',', 2);
      String o = getValue(myString, ',', 3);
      String p = getValue(myString, ',', 4);
      String q = getValue(myString, ',', 5);


      // these leds represents the leds used in Blynk application
      Firebase.RTDB.setInt(&control_data, "SLOT 1 is actived", led1);
      Firebase.RTDB.setInt(&control_data, "SLOT 2 is actived", led2);
      Firebase.RTDB.setInt(&control_data, "SLOT 3 is actived", led3);
      Firebase.RTDB.setInt(&control_data, "SLOT 4 is actived", led4);
      // led1 = l.toInt();
      // led2 = m.toInt();
      // led3 = n.toInt();
      // led4 = o.toInt();
      // led5 = p.toInt();
      // led6 = q.toInt();

        myString = "";
      // end new code
    }
  }
  }
}

void sensorvalue1()
{
  int sdata = led1;
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V10, sdata);
}
void sensorvalue2()
{
  int sdata = led2;
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V11, sdata);

}

void sensorvalue3()
{
  int sdata = led3;
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V12, sdata);

}

void sensorvalue4()
{
  int sdata = led4;
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V13, sdata);

}

void sensorvalue5()
{
  int sdata = led5;
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V14, sdata);

}

void sensorvalue6()
{
  int sdata = led6;
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V15, sdata);

}


String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}