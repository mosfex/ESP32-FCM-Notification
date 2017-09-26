/*
* Written by Mosfex : www.mosfex.com
* www.fb.com/mosfex 
* plese refer to this when using the code
*/
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
WiFiMulti mwifi;
const char *ssid = "mosfex.com"; //wifi ssid
const char *pass = "123456789";  //password for wifi
const String device = "...."; //device token key
const String key = "key=AAAASwElybY:APA91bFaTT_zKLcLYqB0soW8PJmFFG7x1F3wiR0MGta9lLsU22uAVa0VD_3zzz-OremJKDEWEf52OD554byamcwAmZldgrQKfwAjjbhZz_5DYT-z1gcflUBFSWVQQ9lSE9KwDBNHULvfVKmQwxa7xNwuPHz-VfdTbw"; //you should create youself

int sendNotification(String title,String message)
{
  HTTPClient http;        
  http.begin("http://fcm.googleapis.com/fcm/send");
  http.addHeader("Authorization",key);
  http.addHeader("Content-Type","application/json");
  Serial.print("Sending notification ! ==> ");  
  String data = String("{\"to\":\"")+device+"\",\"time_to_live\":60,\"priority\":\"high\",\"data\":{\"text\":{\"title\":\""+title+"\",\"message\":\""+message+"\",\"clipboard\":false}}}";
  int httpCode = http.POST(data);
  if(httpCode == HTTP_CODE_OK){
    Serial.println("OK");
  }else{
    Serial.println("Failed");
  }
  http.end();
  return httpCode;
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  pinMode(0,INPUT_PULLUP);
  for(uint8_t t = 4; t > 0; t--) {
      Serial.printf("[SETUP] WAIT %d...\n", t); Serial.flush(); delay(1000);
  }
  mwifi.addAP(ssid,pass);
}

void loop() {    
  if((mwifi.run() == WL_CONNECTED)) {        
    if(digitalRead(0) == LOW){
      sendNotification("Test send message","Message send from ESP32");
    }
    delay(2000);
  }
  delay(100);
}
