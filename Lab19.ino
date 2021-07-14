SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
#include "WatchDog_WCL.h"
#include "oled-wing-adafruit.h"

WatchDog wd;

OledWingAdafruit display;



void printToDisplay(String output)
{
  //reset display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  //output to display
  display.println(output);
  display.display();
}

void setup() {
    pinMode(D5, INPUT);

    display.setup();
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("");
    display.display();
    Serial.begin(9600);

    //check for reset reason
    if  (System.resetReason() == RESET_REASON_WATCHDOG) 
    {
        printToDisplay("SLATT!");
        delay(CONCURRENT_WAIT_FOREVER);
    } 

    //init timer
    wd.initialize(5000);
    wd.pet();
}

void loop() {
    //pet if button not pressed
    if (digitalRead(D5) == LOW) 
    {
        wd.pet();
    }
}
