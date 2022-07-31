/*#include "DHT.h"
#define DHT11_PIN A2
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define DHTTYPE DHT11   // DHT 11
*/
#include <Servo.h>
#define SERVO 6 // Porta Digital 6 PWM
Servo s; // Variável Servo
int pos; // Posição Servo
 

#define SensorPin A3            //pH meter Analog output to Arduino Analog Input 0
#define Offset 42.56   
#define LED 13
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
#define uart  Serial


const int nivelPin = A0;  // Analog input pin that the potentiometer is attached to
const int tempPin = 2;
//DHT dht(DHT11_PIN, DHTTYPE);

int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex = 0;

int nivelValue = 0;        // value read from the pot
int tempValue=0;
 

void setup(void){
   s.attach(SERVO);
   s.write(0); // Inicia motor posição zero
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("pH meter experiment!");    //Test the uart monitor
}
void loop(void)
{
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue, voltage;

for(pos = 0; pos < 90; pos++){
        s.write(pos);
        delay(5);
      }
       delay(1000);
      for(pos = 90; pos >= 0; pos--)
      {
        s.write(pos);
        delay(5);
  }
  if (millis() - samplingTime > samplingInterval)
  {
    pHArray[pHArrayIndex++] = analogRead(SensorPin);
    if (pHArrayIndex == ArrayLenth)pHArrayIndex = 0;
    voltage = avergearray(pHArray, ArrayLenth) * 5.0 / 1024;
    pHValue = -9.185* voltage + Offset;
    samplingTime = millis();
  }
  if (millis() - printTime > printInterval)  //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
    //uart.print("Voltage:");
    //uart.print(voltage, 2);
   
    digitalWrite(LED, digitalRead(LED) ^ 1);
    printTime = millis();

     nivelValue = analogRead(nivelPin);
     nivelValue = map(nivelValue, 0, 1023, 0, 255);
     // nivelValue = map(nivelPin, 0, 1023, 0, 255);
     // map it to the range of the analog out:
     tempValue = analogRead(tempPin);
     tempValue = map(tempValue, 0, 1023, 0, 255);
     //tempValue = tempValue / 1.3667 - 245.116;
      
    /*  //5v
      tempValue = tempValue * (3300 / 1024.0);
      // Converta a tensão na temperatura em graus Celsius:
      float temp = (tempValue - 500) / 10;*/

      // Reading temperature or humidity takes about 250 milliseconds!
      // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
/*      float h = dht.readHumidity();
      // Read temperature as Celsius (the default)
      float t = dht.readTemperature();
      // Read temperature as Fahrenheit (isFahrenheit = true)
      float f = dht.readTemperature(true);*/
      
      //--------------------------------------

      //--------------- ph--------------------
      uart.write('p');//0
      uart.write('h');//1
      int phInt = pHValue;
      //Serial.println(pHValue);
      //Serial.println(phInt);
      Serial.println("pH");
      uart.write(phInt);
     uart.println(pHValue, 2);
      uart.write('f');//3

      //--------------- nivel da agua---------
      Serial.write('n');//4
      Serial.write('v');//4
      Serial.println("nivel");//----
      Serial.write(nivelValue); 
      Serial.println(nivelValue);//----
      Serial.write('f');
      
       //--------------- temperatura da agua--
      Serial.write('t');
      Serial.write('p');
      //----Serial.println("temp");//----
      //int tempInt = temp;
      Serial.write(tempValue); 
      Serial.println(tempValue);//----
      Serial.write('f');

     
  }
  

}


double avergearray(int* arr, int number) {
  int i;
  int max, min;
  double avg;
  long amount = 0;
  if (number <= 0) {
    uart.println("Error number for the array to avraging!/n");
    return 0;
  }
  if (number < 5) { //less than 5, calculated directly statistics
    for (i = 0; i < number; i++) {
      amount += arr[i];
    }
    avg = amount / number;
    return avg;
  } else {
    if (arr[0] < arr[1]) {
      min = arr[0]; max = arr[1];
    }
    else {
      min = arr[1]; max = arr[0];
    }
    for (i = 2; i < number; i++) {
      if (arr[i] < min) {
        amount += min;      //arr<min
        min = arr[i];
      } else {
        if (arr[i] > max) {
          amount += max;  //arr>max
          max = arr[i];
        } else {
          amount += arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount / (number - 2);
  }//if
  return avg;
}
