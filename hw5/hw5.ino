int servoPin = 7;    
int maxPin = 6;
int minPin = 5;

int maxPinValue = 0;
int minPinValue = 0;
int maxStartFlag = 0;
int minStartFlag = 0;

int pulseWidth = 0;
long lastPulse = 0;
int refreshTime = 20; 

int minPulse = 600;   // minimum pulse width
int maxPulse = 2250;  // maximum pulse width

void setup() {
  pinMode(servoPin, OUTPUT);
  pulseWidth = minPulse; 
  Serial.begin(9600);      
  Serial.println("Servo control program ready");
}

void loop() {
  maxPinValue = digitalRead(maxPin);
  minPinValue = digitalRead(minPin);
  

  if (maxPinValue==HIGH && maxStartFlag==0) {
    Serial.println("max high");
    maxStartFlag = 1;
    pulseWidth = maxPulse;
  }
  else if (maxPinValue==LOW && maxStartFlag==1){
    Serial.println("max low");
    maxStartFlag = 0;
  }
  
  if (minPinValue==HIGH && minStartFlag==0) {
    Serial.println("min high");
    minStartFlag = 1;
    pulseWidth = minPulse;
  }
  else if (minPinValue==LOW && minStartFlag==1){
    Serial.println("min low");
    minStartFlag = 0;
  }
  
  updateServo();
}


void updateServo() {
  //Serial.println(pulseWidth);
  // pulse the servo again if rhe refresh time (20 ms) have passed:
  if (millis() - lastPulse >= refreshTime) {
    digitalWrite(servoPin, HIGH);   // Turn the motor on
    delayMicroseconds(pulseWidth);  // Length of the pulse sets the motor position
    digitalWrite(servoPin, LOW);    // Turn the motor off
    lastPulse = millis();           // save the time of the last pulse
  }
}


