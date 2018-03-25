#define pirpompa 14013757
#define pompaoff 4478227 
#define pompaon  4478225
#define czasobiegu  18  // ilość sek włączenia pompy x 10
#define pompapilot 7730437 //

int obieg = -3; 

void pompasetup() {
  Blynk.setProperty(V15, "color", _YELLOW);
  Blynk.setProperty(V15, "offLabel", "POMPA");
}
void pompazal() //wysyłanie kodu do załączenia pompy
{
  sendkodpilot(pompaon);
  Blynk.setProperty(V15, "onLabel", String(obieg));

}
void pompastop() //wysyłanie kodu do wyłączenia pompy
{
  Blynk.virtualWrite(V15, 0);
  Blynk.setProperty(V15, "color", _YELLOW);
  Blynk.setProperty(V15, "offLabel", "POMPA");
  akcja.updateInterval(2, 2000);
}
void pompaakcja() {
  if ((o_kod == pirpompa) || (o_kod == pompapilot)) {
    obieg = czasobiegu;
//    pompazal();
    o_kod =  0;
    akcja.updateInterval(2, 300);
    Blynk.setProperty(V15, "color", _BRAU);
    Blynk.virtualWrite(V15, 1);
    //   Serial.println(pompaon);
  }
}

void pompa_timer() {
  if (obieg < -2) obieg = -3; else {
    if (obieg < 1) {
      if (obieg == 0)   pompastop();
      sendkodpilot(pompaoff);
    }  else {
      pompazal();
    }
  }
  obieg--;
}

BLYNK_WRITE(V15) //zalaczenie pompy recznie
{
  o_kod = pirpompa;
}

int oldtimeronoff;
void pomparunpir() { //sprawdzenie czy mozna włączyć pompę w odpowiednim przedziale czasu
  if (oldtimeronoff == 1) {
    obieg = czasobiegu;
    pompazal();
  }
}


