#include <stdio.h>
#include <dht.h>

unsigned int armed = 1;

const int doorLedPin = 2;
const int motionLedPin = 4;
const int alarmLedPin = 7;

const int motionPin = 9;
const int dht11Pin = 10;
const int doorPin = 11;
const int alarmPin = 6;

dht DHT;

unsigned int doorStatus;
unsigned int motionStatus;
unsigned int alarmStatus;

int dhtDataReadStatus;
char humidityData[8];
char temperatureData[8];

unsigned int doorData;
unsigned int motionData;
unsigned int alarmData;

int change = 0;

int dhtReadDelay = 25;
int feedBackDelay = 100;
int alarmShutDownDelay = 25;

int dhtReadCounter = 1;
int feedbackDelayCounter = 1;
int alarmShutDownCounter = 1;

void setup() {
  Serial.begin(9600);
  while(!Serial){
    ;
  }
 
  pinMode(doorLedPin, OUTPUT);
  pinMode(motionLedPin, OUTPUT);
  pinMode(alarmLedPin, OUTPUT); 
 
  pinMode(doorPin, INPUT_PULLUP);
  pinMode(motionPin, INPUT);
  pinMode(alarmPin, OUTPUT);
  
  digitalWrite(alarmLedPin, armed);
  
  dhtDataReadStatus = DHT.read11(dht11Pin);
  dtostrf(DHT.humidity, 4, 2, humidityData);
  dtostrf(DHT.temperature, 4, 2, temperatureData);
      
  feedback();
}

void loop() {
    mesure();
    
    if (doorData == HIGH && doorStatus == LOW) {
      doorStatus = doorData;
      digitalWrite(doorLedPin, HIGH);
      change = 1; 
    }
    
    if (doorData == LOW && doorStatus == HIGH) {
      doorStatus = doorData;
      digitalWrite(doorLedPin, LOW);
      change = 1;
    }
    
    if (motionData == HIGH && motionStatus == LOW) {
      motionStatus = motionData;
      digitalWrite(motionLedPin, HIGH);
      change = 1; 
    }
    
    if (motionData == LOW && motionStatus == HIGH) {
      motionStatus = motionData;
      digitalWrite(motionLedPin, LOW);
      change = 1;
    }
    
    if (armed == 1 && (motionStatus == HIGH || doorStatus == HIGH)) {
      alarmStart();  
    } else if (alarmStatus == 1) {
      alarmStop();
    }
    
    if (feedbackDelayCounter == 100 || change == 1) {
      feedback();
    }
}

void mesure() {
    delay(100);
  
    if (dhtReadCounter % dhtReadDelay == 0) {
      dhtDataReadStatus = DHT.read11(dht11Pin);
      dtostrf(DHT.humidity, 4, 2, humidityData);
      dtostrf(DHT.temperature, 4, 2, temperatureData);
      dhtReadCounter = 0;
    }

    doorData = digitalRead(doorPin);
    motionData = digitalRead(motionPin);
    alarmData = digitalRead(alarmPin);
    
    feedbackDelayCounter++;
    dhtReadCounter++;
}

void feedback() {
      char buffer [100];
      
      sprintf(buffer, "{"
            "\"alarmStatus\": %d,"
            "\"motionStatus\": %d,"
            "\"doorStatus\": %d, "
            "\"temperature\": %s, "
            "\"humidity\": %s "
          "}", armed, motionStatus, doorStatus, temperatureData, humidityData);
      
      Serial.println(buffer);
      change = 0;    
      feedbackDelayCounter = 1;
}

void alarmStart() {
  alarmStatus = 1;
  digitalWrite(alarmPin, HIGH);
  alarmShutDownCounter = 1;
}

void alarmStop() {
  if (alarmShutDownCounter == alarmShutDownDelay) {
    digitalWrite(alarmPin, LOW);
    alarmStatus = 0;
  }
  alarmShutDownCounter++;
}

