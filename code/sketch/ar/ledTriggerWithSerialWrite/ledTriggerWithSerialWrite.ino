#include <stdio.h>
#include <dht.h>

const int ledPin = 13;
const int dht11Pin = 5;
const int doorPin = 3;

unsigned int desiredLedStatus;
unsigned int ledStatus;
int dhtDataReadStatus;
float humidity;
float temp;
unsigned int contact;

dht DHT;

int i;
int f;

void setup() {
  Serial.begin(9600);
  while(!Serial){
    ;
  }
 
  pinMode(ledPin, OUTPUT);
  pinMode(doorPin, INPUT_PULLUP);
  
  feedback();
  i=0;
  f=0;
}

void loop() {
    f++;
    i++;
    
    if (f % 25 == 0) {
      dhtDataReadStatus = DHT.read11(dht11Pin);
      humidity = DHT.humidity;
      temp = DHT.temperature;
      f = 1;
    }
    
    if (digitalRead(doorPin) == HIGH && ledStatus == 0) {
      digitalWrite(ledPin, HIGH);
      feedback();
    }
    
    if (digitalRead(doorPin) == LOW && ledStatus == 1) {
      digitalWrite(ledPin, LOW);
      feedback();
    }
    
    if (i == 100) {
      feedback();
    }
    
    delay(100);
}

void feedback() {
      char buffer [100];
      ledStatus = digitalRead(ledPin);
      contact = digitalRead(doorPin);
      
      sprintf(buffer, "{temp: %d}", temp);
      
      Serial.println(buffer);
          
      i = 0;
}

