#include <Wire.h>  // Include the Wire library for I2C communication
#include <LiquidCrystal_I2C.h>  // Include the LiquidCrystal_I2C library
#include <WiFi.h>
#include <HTTPClient.h>
//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>

const char* ssid = "test123";
const char* password = "123456780";
String serverAddr = "https://project.uxeer.org/powertransmission/index.php";

LiquidCrystal_I2C lcd(0x3F, 16, 2);  // Create an LCD object with the I2C address and LCD dimensions

void setup() {
  Serial.begin(9600);
  lcd.init();                      // Initialize the LCD
  lcd.backlight();                 
  lcd.setCursor(0, 0);             
  lcd.print("Transmission Lin");   
  lcd.setCursor(0, 1);             
  lcd.print("Fault Detection.");
  delay(2000);
  connectWiFi();
  delay(2000);  
  //lcd.clear(); 
}

void connectWiFi(){
  lcd.setCursor(0, 0);             
  lcd.print(" Connecting to  ");   
  lcd.setCursor(0, 1);             
  lcd.print("  Internet....  ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected"); 
  lcd.setCursor(0, 0);             
  lcd.print("  Connected to  ");   
  lcd.setCursor(0, 1);             
  lcd.print("   [Internet]   ");
}

void sendData(){
  // Send the GET request
  HTTPClient http;
  String data = "0,0,0,0,0,0";
  String url = serverAddr;
  url += "?data=" + data;

  http.begin(url);
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("HTTP Response code: " + String(httpResponseCode));
    Serial.println("Response: " + response);
  } else {
    Serial.println("Error in HTTP request");
  }

  http.end();
}

void loop() {
  Serial.println("Sending...");
  sendData();
  lcd.setCursor(0, 0);             
  lcd.print(" R:NA Y:NA B:NA ");   
  lcd.setCursor(0, 1);             
  lcd.print(" No Fault Found ");
  delay(2000);
  //lcd.setCursor(0, 0);             
  //lcd.print(" R:RN Y:NA B:NA ");   
  lcd.setCursor(0, 1);             
  lcd.print("Uploading data..");
  delay(2000);
}
