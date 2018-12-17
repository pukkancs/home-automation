const int ledPin = 13;
unsigned char desiredLedStatus;
unsigned char ledStatus;
int i;

void setup() {
  Serial.begin(9600);
  while(!Serial){
    ;
  }
 
  pinMode(ledPin, OUTPUT);
  feedback();
  i=0; 
}

void loop() {
    i++;
    if (Serial.available()){
      desiredLedStatus = Serial.read();
    }
    
    if (ledStatus == HIGH && desiredLedStatus == '0'){
      digitalWrite(13, LOW);
      feedback();
    }
    
    if (ledStatus == LOW && desiredLedStatus == '1'){
      digitalWrite(13, HIGH);
      feedback();
    }
    
    if (i == 100) {
      feedback();
    }
    delay(100);
}

void feedback() { 
    delay(100);
    ledStatus = digitalRead(13);
    
    if (ledStatus == LOW) {
      Serial.println('OFF');
    }
    
    if (ledStatus == HIGH) {
      Serial.println('ON');
    }
    
    i = 0; 
}
