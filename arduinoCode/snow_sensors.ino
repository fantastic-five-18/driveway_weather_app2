#define LED 8
#define WATER_SENSOR 7
#define BUZZER 2
#define SERVO 4

#include <Servo.h>
#include <math.h>

Servo steering;

char receivedChar;
boolean newData = false;

const int ultrasonicTrigPin = 5;
const int ultrasonicEchoPin = 6;
const int B = 4275;
const int R0 = 100000;
const int pinTempSensor = A0;

int ultrasonicDistance;
int ultrasonicDuration;
int water;

float temperature;
//float dataMatrix [2];

void setup() {
  
  Serial.begin(9600);
  pinMode(WATER_SENSOR, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(ultrasonicTrigPin, OUTPUT);
  pinMode(ultrasonicEchoPin, INPUT);
  pinMode(8, OUTPUT);
  
}

void loop() {
  
  recvInfo();
  printStuff();
  readUltrasonicSensors();
  getTemp();
  if(isExposedToWater()) water = 1;
  else water = 0;
  //dataMatrix[0] = water;
  //dataMatrix[1] = ultrasonicDistance;
  //dataMatrix[2] = temperature;
  Serial.println(water);
  Serial.println(ultrasonicDistance);
  Serial.println(temperature);
  delay(1000);
  
}

void recvInfo() {
  
  if (Serial.available() > 0) {
    
    receivedChar = Serial.read();
    newData = true;
    
    
    
  }
  
}

void getTemp() {
  
  int a = analogRead(pinTempSensor);
  
  float R = 1023.0/a-1.0;
  R = R0*R;
  
  temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15;
  
  //Serial.println(temperature);
  
  delay(1000);
  
}

void printStuff() {
  
  //int led = (receivedChar - '0');
  
  while(newData == true) {
  
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);
    delay(100);
    
    newData = false;
  
  }
}

void soundAlarm()
{
    for(uint8_t i = 0;i < 10;i ++)
    {
        digitalWrite(BUZZER, HIGH);
        delay(50);
        digitalWrite(BUZZER, LOW);
        delay(50);
    }
}

void readUltrasonicSensors()
{
  digitalWrite(ultrasonicTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicTrigPin, LOW);
  
  ultrasonicDuration = pulseIn(ultrasonicEchoPin, HIGH);
  ultrasonicDistance = (ultrasonicDuration/2)/3;
  //Serial.println(ultrasonicDistance);
 // if(ultrasonicDistance < 400 && ultrasonicDistance > 0) soundAlarm();
  
}

boolean isExposedToWater()
{
    if(digitalRead(WATER_SENSOR) == LOW)
    return true;
    else return false;
}
