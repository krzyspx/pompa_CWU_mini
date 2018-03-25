#include <RCSwitch.h> // biblioteka obsługi nadawania i odbioru 433 MHz
RCSwitch mySwitch = RCSwitch();

unsigned long o_kod = 0;
void pompaakcja();

void no433setup()
{
  if (procesor == D1MINI) {
    mySwitch.enableReceive(12);  // port odbiornika
    mySwitch.enableTransmit(14); // nadajnika
  }
  if (procesor == ESP01) {
    mySwitch.enableReceive(3);  //
    mySwitch.enableTransmit(1); //
  }
}

void no433akcja()
{
  if (mySwitch.available()) {

    if (procesor == D1MINI) { //przełącznik wysyłania info o odebranym kodzie na monitor
      Serial.println("Kod " + String(mySwitch.getReceivedValue()) + " / " + String(mySwitch.getReceivedBitlength()) + " IMP " + String(mySwitch.getReceivedDelay())
                     + " Prot  "  + " / " + String(mySwitch.getReceivedProtocol()) );
    }
    if (terminalon) {// przełącznik wysyłania info na terminal BLYNK
      terminal.println("Kod " + String(mySwitch.getReceivedValue()) + " / " + String(mySwitch.getReceivedBitlength()) + " IMP " + String(mySwitch.getReceivedDelay())
                       + " Prot " + " / " + String(mySwitch.getReceivedProtocol()) );
      terminal.flush();
      String str = String(mySwitch.getReceivedValue()) + " / " + String (mySwitch.getReceivedDelay());
      Blynk.virtualWrite(V3, str);
    }

    o_kod = mySwitch.getReceivedValue();

    mySwitch.disableReceive();
    pompaakcja();
    mySwitch.resetAvailable();
    no433setup();
  }
}

void sendkod(unsigned long code, int impuls, byte bity, byte prot) { // wysłanie kodu z routera
  mySwitch.disableReceive();

  mySwitch.setPulseLength(impuls);
  mySwitch.setRepeatTransmit(10);
  mySwitch.send(code, bity);
  
  no433setup();
}

void sendkodpilot (unsigned long code) {
  sendkod(code, 340, 24, 1);
}




