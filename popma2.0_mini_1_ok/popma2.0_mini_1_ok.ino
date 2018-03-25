#define BLYNK_MSG_LIMIT 0
//#define BLYNK_DEFAULT_PORT 8080
#include <Timers.h> //  my favorite timer 
Timers <7> akcja; //

#include "blynk.h" //obsługa BLYNKa
#include "led.h"
#include "NO433.h" // obsługa transmisji 433 MHz
#include "pompa.h" // 

void setup()
{
  ledsetup();
  if (procesor == D1MINI) {
    Serial.begin(115200);  delay(100);
    Serial.println();  Serial.println(F(__FILE__));  //BLYNK 0.5.1 Arduino IDE.cc 1.8.3
  }
  akcja.attach(0, 3000, blynk_timer); //
  akcja.attach(2, 2000, led_timer);
  akcja.attach(3, 10000, pompa_timer); //
  
  blynksetup(); // setup biblioteki BLYNK
  no433setup();  //setup 433 MHz
  pompasetup();

}
void loop()
{
  akcja.process(); // timer
  blynkakcja();    //BLYNK
  no433akcja();
  pompaakcja();
}








