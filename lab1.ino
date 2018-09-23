#include "SSC32.h"
SSC32 mySSC32;
//Robot 2
bool mybool = true;
int channels[] = {0,1,2,3,4,5,16,17,18,19,20,21};
int drop[] = {1100, 1100, 1100, 1100, 1100, 1100, 1900, 1900, 1900, 1900, 1900, 1900};
int lift[] = {1900, 1900, 1900, 1900, 1900, 1900, 1100, 1100, 1100, 1100, 1100, 1100};
int zero[] = {1900,1400,1900,1500,1750,1500,1100,1500,1100,1300,1100,1500};
int one[] = {1800,1400,1800,1500,1650,1500,1200,1500,1200,1300,1200,1500};
int two[] = {1700,1400,1700,1500,1550,1500,1300,1500,1300,1300,1300,1500};
int three[] = {1450,1400,1500,1500,1350,1500,1500,1500,1550,1200,1500,1400};
int four[] = {1250,1400,1300,1500,1150,1500,1800,1500,1800,1200,1700,1400};
int five[] = {1050,1400,1150,1500,1000,1500,1900,1500,1900,1200,1850,1400};

void setup() {                
	mySSC32.begin(9600);
	mySSC32.enableServos(channels);
	mySSC32.setFrame(three);
 delay (1000);
	pinMode(13,OUTPUT);
 
}

void loop() {

  rippleGait();

    
    
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

void rippleGait()
{
  // Step 1
  int stepOne[] = {three[0], lift[1], two[2], lift[3], one[4], lift[5], zero[6], lift[7], five[8], lift[9], four[10], lift[11]};
  mySSC32.setFrame(stepOne);
  Serial.println(micros());
  delay(5000);
  // Step 3
  int stepThree[] = {four[0], lift[1], three[2], lift[3], two[4], lift[5], one[6], lift[7], zero[8], lift[9], five[10], lift[11]};
  mySSC32.setFrame(stepThree);
  Serial.println(micros());
  delay(5000);
  // Step 5
  int stepFive[] = {five[0], lift[1], four[2], lift[3], three[4], lift[5], two[6], lift[7], one[8], lift[9], zero[10], lift[11]};
  mySSC32.setFrame(stepFive);
  Serial.println(micros());
  delay(5000);
  // Step 7
  int stepSeven[] = {zero[0], lift[1], five[2], lift[3], four[4], lift[5], three[6], lift[7], two[8], lift[9], one[10], lift[11]};
  mySSC32.setFrame(stepSeven);
  Serial.println(micros());
  delay(5000);
  // Step 9
  int stepNine[] = {one[0], lift[1], zero[2], lift[3], five[4], lift[5], four[6], lift[7], three[8], lift[9], two[10], lift[11]};
  mySSC32.setFrame(stepNine);
  Serial.println(micros());
  delay(5000);
  // Step 11
  int stepEleven[] = {two[0], lift[1], one[2], lift[3], zero[4], lift[5], five[6], lift[7], four[8], lift[9], three[10], lift[11]};
  mySSC32.setFrame(stepEleven);
  Serial.println(micros());
  delay(5000);
}

void triGait()
{
  // Tri step 1    
    int triFrame[] = {two[0], lift[1], three[2], drop[3], two[4], lift[5], three[6], drop[7], two[8], lift[9], three[10], drop[11]};

    mySSC32.setFrame(triFrame);
    Serial.println(micros());
    delay(200);

    // Tri step 2   
    int triFrameTwo[] = {three[0], lift[1], two[2], drop[3], three[4], lift[5], two[6], drop[7], three[8], lift[9], two[10], drop[11]};

    mySSC32.setFrame(triFrameTwo);
    Serial.println(micros());
    delay(100);

    // Tri step 3   
    int triFrameThree[] = {three[0], drop[1], two[2], lift[3], three[4], drop[5], two[6], lift[7], three[8], drop[9], two[10], lift[11]};

    mySSC32.setFrame(triFrameThree);
    Serial.println(micros());
    delay(200);

    // Tri step 4   
    int triFrameFour[] = {two[0], drop[1], three[2], lift[3], two[4], drop[5], three[6], lift[7], two[8], drop[9], three[10], lift[11]};
    mySSC32.setFrame(triFrameFour);
    Serial.println(micros());
    delay(100);
}

