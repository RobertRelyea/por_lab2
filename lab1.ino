#include "hexapod.h"

void setup() {                
	hexapodSetup();
	delay (1000);
	pinMode(13,OUTPUT);
 
}

void loop() {

  waveGait();

    
    
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


