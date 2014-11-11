/*
    The main control flow for YunHome, it read, parse, and display data from
    a data file located in /tmp/yun_home.data, which is created by Linux Python
    script.
 */

#include <FileIO.h>
#include <stdint.h>
#include <TFTv2.h>
#include <SPI.h>

void setup() {
  
    
  //initSerial();
  //printToSerial("Sketch start");
  
//
  TFT_BL_ON;      // turn on the TFT background light
  Tft.TFTinit();  // init TFT library
  Tft.fillScreen();
  Tft.drawString("Hello", 60, 100, 2, WHITE);
  
  // Setup Bridge (needed every time we communicate with the Arduino Yún)
  Bridge.begin();
//  // Setup File IO
//  FileSystem.begin();

}

void initSerial() {

    // Initialize the Serial
    Serial.begin(9600);

    while (!Serial); // wait for Serial port to connect.
}

void printToSerial(String text) {
//    Serial.println(text);
//    Serial.flush();
}

void loop() {
  
//  printToSerial("");
//  printToSerial("Loop begin...");
  
   String content = readWeatherData();
//  printToSerial(content);
  
   displayToScreen(content);
  
//  printToSerial("Loop end");

    
  delay(5000);
}

String readWeatherData() {
//    File dataFile = FileSystem.open("/tmp/yun_home.data", FILE_READ);
//  
//    if(dataFile) {
//        printToSerial("File read OK.");
//        String dataContent = "";
//        int counter = 0;
//        while (dataFile.available() && counter < 15) {
//            dataContent += (char)dataFile.read();
//            counter ++;
//        }
//        dataFile.close();
//        return dataContent;
//    } else {
//        printToSerial("File read Error!");
//        return "";
//    }
    return "abcde";
}

void displayToScreen(String text) {
    char textCh[text.length() + 1];
    strcpy(textCh, text.c_str());
    Tft.fillScreen();
    Tft.drawString(textCh, 60, 220, 2, WHITE);
    delay(1000);
    Tft.drawString(textCh, 60, 220, 2, RED);
}


