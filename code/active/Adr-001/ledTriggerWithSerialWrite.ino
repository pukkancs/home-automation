const int ledPin = 13;
unsigned char desiredLedStatus;
unsigned char ledStatus;
unsigned char serialData;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(13, HIGH);
  ledStatus = 'OFF';
  desiredLedStatus = 'OFF';
}

void loop() {
    
  if (Serial.available()) {
    serialData = Serial.read();
    if (serialData == '1') {
      desiredLedStatus = 'ON';
    }
    if (serialData == '0') {
      desiredLedStatus = 'OFF';
    }
  }
  
  if (digitalRead(13) == LOW) {
    ledStatus = 'OFF';
  }
  
  if (digitalRead(13) == HIGH) {
    ledStatus = 'ON';
  }  
  
  if (desiredLedStatus == 'ON') {
    digitalWrite(13, HIGH); 
  }
 
 if (desiredLedStatus == 'OFF') {
    digitalWrite(13, LOW); 
  } 
 
  delay(1000);
  Serial.println(ledStatus); 
}
