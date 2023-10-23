// Sensor pins pin D6 LED output, pin A0 analog Input
#define ledPin 6
#define pumpPin 7
#define lvlSensorPin A0
#define moistureSensorPin A1 // Arduino pin that connects to AOUT pin of moisture sensor
#define THRESHOLD 100 // CHANGE YOUR THRESHOLD HERE


// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;  // will store last time LED was updated
unsigned long lastPumpMillis = 0;

// constants won't change:
const long interval = 1000;  // interval at which to blink (milliseconds)
const long intervalP = 60000;  // 1min


int ledState = LOW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(lvlSensorPin);
  unsigned long currentMillis = millis();

  if (sensorValue < 570)  {
    if (currentMillis - previousMillis >= interval) {
      // save the last time you blinked the LED
      previousMillis = currentMillis;

      // if the LED is off turn it on and vice-versa:
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
      //int outputValue = map(sensorValue, 570, 800, 0, 255);
      //Serial.println(outputValue);
      digitalWrite(ledPin, ledState); // generate PWM signal
    }  
  }else{
    digitalWrite(ledPin, LOW); // turn off
  }

  int value = analogRead(moistureSensorPin); // read the analog value from sensor

  if (value < THRESHOLD){
    Serial.print("The soil is DRY (");
    if (currentMillis - lastPumpMillis >= intervalP) {
      digitalWrite(pumpPin, HIGH);
      delay(2000);
      digitalWrite(pumpPin, LOW);
      lastPumpMillis = currentMillis;
    }else{
      Serial.print("Waiting : ");
      Serial.print((currentMillis - lastPumpMillis - intervalP)/1000);
      Serial.print(" sec") ;
    }
  } else {
    Serial.print("The soil is WET (");
  }
  Serial.println(value);
}
