#include "hexapod.h"

void setup() {                
	hexapodSetup();
	delay (1000);
	pinMode(13,OUTPUT);
 
}

void loop() {

  long measure = pingMeasure();
  if(measure < 40)
  {
    turnRight();
    turnRight();
  }
  else
    newRipple();
    
    
	/*for(int i = 0;i<12;i++)
	{
		Serial.print(channels[i]);
		Serial.print("\t");
		}
		Serial.println();*/
	/*mybool = mySSC32.moveStatus();
	if(mybool == false)
	{
		digitalWrite(13,HIGH);
	}
	delay(500);
	mybool = true;
	digitalWrite(13,LOW);
	delay(500);*/
}


// this constant won't change. It's the pin number of the sensor's output:
const int pingPin = 7;

long pingMeasure() {
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);

  return cm;
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

