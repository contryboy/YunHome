#include <Bridge.h>
#include <SpacebrewYun.h>
#include <FileIO.h>
#include <stdint.h>
#include <TFTv2.h>
#include <SPI.h>

SpacebrewYun sb = SpacebrewYun("YunHome", "yunHome project!");

// variable that holds the last potentiometer value
int last_value = 0;

// create variables to manage interval between each time we send a string
void setup() { 

	// start the serial port
	Serial.begin(57600);

	// for debugging, wait until a serial console is connected
	delay(4000);
	while (!Serial) { ; }

	// start-up the bridge
	Bridge.begin();

	// configure the spacebrew object to print status messages to serial
	sb.verbose(true);

	// configure the spacebrew publisher and subscriber
	sb.addPublish("physical button", "boolean");
	sb.addSubscribe("virtual button", "boolean");
	sb.onBooleanMessage(handleBoolean);

        sb.addPublish("speak", "string");
	sb.addSubscribe("listen", "string");
	sb.onStringMessage(handleString);

	sb.connect("sandbox.spacebrew.cc"); 

	pinMode(3, INPUT);
	digitalWrite(3, HIGH);

        TFT_BL_ON;      // turn on the TFT background light
        Tft.TFTinit();  // init TFT library
        Tft.fillScreen();
        Tft.drawString("Hello World! ", 60, 100, 2, WHITE);
} 


void loop() { 
	// monitor spacebrew connection for new data
	sb.monitor();

	// connected to spacebrew then send a new value whenever the pot value changes
	if ( sb.connected() ) {
		int cur_value = digitalRead(3);
		if ( last_value != cur_value ) {
			if (cur_value == HIGH) sb.send("physical button", false);
			else sb.send("physical button", true);
			last_value = cur_value;
		}
	}
} 

void handleString (String route, String value) {
	// print the message that was received
	Serial.print("From ");
	Serial.print(route);
	Serial.print(", received msg: ");
	Serial.println(value);
        displayToScreen(value, BLUE);
}

// handler method that is called whenever a new string message is received 
void handleBoolean (String route, boolean value) {
	// print the message that was received
	Serial.print("From ");
	Serial.print(route);
	Serial.print(", received msg: ");
	Serial.println(value ? "true" : "false");
        
        
        if(value) {
            displayToScreen("ON", GREEN);
        } else {
            displayToScreen("OFF", RED);
        }
}

void displayToScreen(String text, INT16U color) {
    char textCh[text.length() + 1];
    strcpy(textCh, text.c_str());
    Tft.fillScreen();
    Tft.drawString(textCh, 60, 220, 2, color);
}

