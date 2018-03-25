/*
  v0 LED kontrolny
  v1 terminal do wyswietlania co dzieje sie wewnatrz
  v3 recive kod // wyświetlanie odebranego kodu
  v6 term on/off
*/
#define _RED        "#FF0000"
#define _GREEN      "#00FF00"
#define _MAGENTA    "#FF00FF"
#define _YELLOW     "#FFFF00"
#define _BLACK      "#000000"
#define _WHITE      "#FFFFFF"
#define _WBLUE      "#00FFFF"
#define _PINK       "#FFB3B3"
#define _OLIVE      "#808000"
#define _BRAU       "#FF8000"
#define _karmin     "#FF0080"
#define _SEE        "#00FF80"
#define _fiolet     "#8000FF"
#define _BLUE       "#0080FF"

#define ESP01 1
#define D1MINI 2
int procesor = ESP01;
#define led_wew   2

  char auth[] = "xxxxxxxxxx";  
  char ssid[] = "xxxxxxxxxx";
char auth[] = "ce5212f4c6d34eacac865888ab958626";

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define treconnect 60 // czas miedzy kolejnymi testami łaczności z serwerem BLYNK w sek
int liczreconnect = 10; // licnik czasu testów łącznosci
int printon = 0; // flaga wysyłania danych na monitor
int terminalon = 0; // flaga wysyłania danych na terminal BLYNK

WidgetLED led1(V0); // led w aplikacji wskazujący na połacenie mikroprocesor - aplikacja
WidgetTerminal terminal(V1);


void blynksetup() //nie blokująca procedura połączenia z BLYNK
{

  pinMode(led_wew, OUTPUT); //LED na module
  digitalWrite(led_wew, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  //  Blynk.config(auth, "kpr");

  //Blynk.config(auth_local_server, local_server, 8080);
  Blynk.config(auth, IPAddress(192, 168, 2, 111), 8080);
  Blynk.connect();
  if (Blynk.connected()) Blynk.run();  else  Blynk.connect();
  Blynk.setProperty(V0, "color", _BRAU);
  Blynk.virtualWrite(V5, 0);
  Blynk.virtualWrite(V6, 0);
}

void blynkakcja()
{
  if (Blynk.connected()) Blynk.run();
}

int wskrunAr = 0;
void vLED_timer()//miganie vLED dla kontroli połączenia
{
  wskrunAr = !wskrunAr ;
  if (wskrunAr == 0)led1.off(); else led1.on();
}

void testconnect() // test łączności z serwerem BLYNK bez blokowania programu głównego GS
{
  vLED_timer();
  if (Blynk.connected()) {
    digitalWrite(led_wew, HIGH); //wskaźnik łączności z serwerem stan wysoki- wyłączenie LEDa
    if (procesor == D1MINI)  Serial.println("connection OK");
    liczreconnect = treconnect;
  } else {
    digitalWrite(led_wew, LOW);
    liczreconnect--;
    if (procesor == D1MINI)  Serial.println("connection DOWN");
    if (liczreconnect == 0) {
      Blynk.connect();
      liczreconnect = treconnect;
    }
  }
}

void blynk_timer() { //różne rzeczy wykonywane cyklicznie
  testconnect(); // test łączności z serwerem
}

BLYNK_WRITE(V6) {
  terminalon = param.asInt();
}

