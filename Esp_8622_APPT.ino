
// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings

#define BLYNK_TEMPLATE_ID "TMPLLxirvpvj"
#define BLYNK_DEVICE_NAME "IOT"
#define BLYNK_AUTH_TOKEN "YTVSEfCIw9UmzTgde60lJJPKS0Qe1Iss"

#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "NOWO-44C18";
char pass[] = "zB2X47ny";

// Comment this out to disable prints and save space ----conecção 



/*char ssid[] = "NOWO-44C18";
char pass[] = "zB2X47ny";
char ssid[] = "IPG-Free";
char pass[] = "";*/
BlynkTimer timer;


int nivelestado = 0;
#include <Servo.h>
Servo servo; // Variável Servo

const int LED_PIN = D0;  // Arduino pin connected to LED's pin
//const int ANALOG_THRESHOLD = 500;


void setup(){

  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  Serial.println("** Conexão **");
  Serial.println();
  timer.setInterval(1000L, sendSensor);
   servo.attach(D6); // 15 means D8 pin of ESP8266
  //delay(1000);
}

char recebido ;
int estado=0;

int ph=-1;
int phAUX=-1;

int nivel=-1;
int nivelAUX=-1;

int temp=-1;
int tempAUX=-1;

int luz=-1;
int luzAUX=-1;
bool esado_led=LOW;




BLYNK_WRITE(V3){
  servo.write(param.asInt());
}



void sendSensor(){
//----------------MICRO_SERVO-----------------------------------------------------//


while(Serial.available())
{

  recebido=Serial.read();
  Serial.println("recebido:");
  Serial.write(recebido);
  Serial.print("estado:");
  Serial.println(estado);  

//----------------PH-----------------------------------------------------//
  if(recebido=='p' && estado==0)
  {
    estado++;
  }

  else if(recebido=='h' && estado==1)
  {
    estado++;
  }else if( estado==2)
  {
    phAUX= recebido;
    estado++;
  }
  else if(recebido=='f' && estado==3)
  {
    ph=phAUX;
    estado=4;

   Serial.print("PH:");
   Serial.println(ph);
   Serial.println(estado);
  Blynk.virtualWrite(V2, ph);
  }
//----------------NV-----------------------------------------------------//
   if(recebido=='n' && estado==4)
  {
    estado++;
  }

  else if(recebido=='v' && estado==5)
  {
    estado++;
  }else if( estado==6)
  {
    nivelAUX= recebido;
    estado++;
  }
  else if(recebido=='f' && estado==7)
   
  {
    nivel=nivelAUX;
    estado=8;

   Serial.print("NV:");
   Serial.println(nivel);
   Blynk.virtualWrite(V0, nivel);
   nivelestado = nivel;
  }

  //--------------------TP----------------------------------------------//

   if(recebido=='t' && estado==8)
  {
    estado++;
  }

  else if(recebido=='p' && estado==9)
  {
    estado++;
  }else if( estado==10)
  {
    tempAUX= recebido;
    estado++;
  }
  else if(recebido=='f' && estado==11)
  
  {
     temp=tempAUX;
    estado=0;

   Serial.print("TP:");
   Serial.println(temp);
   Blynk.virtualWrite(V1, temp);
  } 
 }
}

 
void loop() {
// sendSensor();
 Blynk.run();
 timer.run();

//Serial.println("OLA");
}
