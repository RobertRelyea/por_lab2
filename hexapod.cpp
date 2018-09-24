#include "hexapod.h"

// Servo control object
SSC32 mySSC32;

// Channel mappings for each servo
int channels[] = {0,1,2,3,4,5,16,17,18,19,20,21};

// Calibrated sweep positions for each leg
int drop[]  = {1100,1100,1100,1100,1100,1100,1900,1900,1900,1900,1900,1900};
int lift[]  = {1900,1900,1900,1900,1900,1900,1100,1100,1100,1100,1100,1100};
int zero[]  = {1900,1400,1900,1500,1750,1500,1100,1500,1100,1300,1100,1500};
int one[]   = {1800,1400,1800,1500,1650,1500,1200,1500,1200,1300,1200,1500};
int two[]   = {1700,1400,1700,1500,1550,1500,1300,1500,1300,1300,1300,1500};
int three[] = {1450,1400,1500,1500,1350,1500,1500,1500,1550,1200,1500,1400};
int four[]  = {1250,1400,1300,1500,1150,1500,1800,1500,1800,1200,1700,1400};
int five[]  = {1050,1400,1150,1500,1000,1500,1900,1500,1900,1200,1850,1400};

// Reorganized sweeps  RB   RC   RF   LB   LC   LF
int leg_sw_zero[]  =  {1900,1900,1750,1100,1100,1100};
int leg_sw_one[]   =  {1800,1800,1650,1200,1200,1200};
int leg_sw_two[]   =  {1700,1700,1550,1300,1300,1300};
int leg_sw_three[] =  {1450,1500,1350,1500,1550,1500};
int leg_sw_four[]  =  {1250,1300,1150,1800,1800,1700};
int leg_sw_five[]  =  {1050,1150,1000,1900,1900,1850};
int *leg_sw[] = {leg_sw_zero, leg_sw_one, leg_sw_two, leg_sw_three, leg_sw_four, leg_sw_five};

// Reorganized lifts   RB   RC   RF   LB   LC   LF
int leg_raise[]    =  {1900,1900,1900,1100,1100,1100};
int leg_neutral[]  =  {1400,1500,1500,1500,1200,1400};
int leg_low[]      =  {1100,1100,1100,1900,1900,1900};
int *leg_lift[] = {leg_raise, leg_neutral, leg_low};

int legBuff[] = {0,0,0,0,0,0,0,0,0,0,0,0};

void hexapodSetup()
{
	mySSC32.begin(9600);
	mySSC32.enableServos(channels);
	mySSC32.setFrame(three);
	delay (1000);
	pinMode(13,OUTPUT);
}

void setLeg(legChannel lc, int sw, liftState ls)
{
	legBuff[lc] = leg_sw[sw][lc/2];
	legBuff[lc+1] = leg_lift[ls][lc/2];
}

void setLeg(legChannel lc, int sw)
{
	legBuff[lc] = leg_sw[sw][lc/2];
}

void setLeg(legChannel lc, liftState ls)
{
	legBuff[lc+1] = leg_lift[ls][lc/2];
}

// TODO
void setLegs(legChannel lc[], int sw[], liftState ls[], int num)
{
	for(int i = 0; i < num; ++i)
	{
		setLeg(lc[i], sw[i], ls[i]);
	}
}

void setLegs(legChannel lc[], int sw[], int num)
{
	for(int i = 0; i < num; ++i)
	{
		setLeg(lc[i], sw[i]);
	}
}

void setLegs(legChannel lc[], liftState ls[], int num)
{
	for(int i = 0; i < num; ++i)
	{
		setLeg(lc[i], ls[i]);
	}
}

void sendLegs()
{
	mySSC32.setFrame(legBuff);
	Serial.println(micros());
	delay(200);
}

// Tested sequence, untested implementation
void newTripod()
{
	// Step 1 - All (initial state)
	legChannel channels[] = {RB, RC, RF, LB, LC, LF};
	int sweeps1[] =          {2,  3,  2,  3,  2,  3};
	liftState lifts1[] =     {RAISE, LOWER, RAISE, LOWER, RAISE, LOWER};
	setLegs(channels, sweeps1, lifts1, 6);
	sendLegs();

	// Step 2 - Sweeps only
	int sweeps2[] = {3,  2,  3,  2,  3,  2};
	setLegs(channels, sweeps2, 6);
	sendLegs();

	// Step 3 - Lifts only
	liftState lifts3[] = {LOWER, RAISE, LOWER, RAISE, LOWER, RAISE};
	setLegs(channels, lifts3, 6);
	sendLegs();

	// Step 4 - Sweeps only
	int sweeps4[] = {2,  3,  2,  3,  2,  3};
	setLegs(channels, sweeps4, 6);
	sendLegs();
}

// Completely untested sequence
void newWave()
{
	// Step 1 - All (initial state)
	legChannel channels[] = {RB, RC, RF, LB, LC, LF};
	int sweeps1[] =          {3,  2,  1,  0,  5,  4};
	liftState lifts1[] =     {LOWER, LOWER, LOWER, RAISE, LOWER, LOWER};
	setLegs(channels, sweeps1, lifts1, 6);
	sendLegs();

	// Step 2 - Lifts only
	liftState lifts2[] = {LOWER, LOWER, LOWER, LOWER, RAISE, LOWER};
	setLegs(channels, lifts2, 6);
	sendLegs();

	// Step 3 - Sweeps only
	int sweeps3[] = {4,  3,  2,  1,  0,  5};
	setLegs(channels, sweeps3, 6);
	sendLegs();

	// Step 4 - Lifts only
	liftState lifts4[] = {LOWER, LOWER, LOWER, LOWER, LOWER, RAISE};
	setLegs(channels, lifts4, 6);
	sendLegs();

	// Step 5 - Sweeps only
	int sweeps5[] = {5,  4,  3,  2,  1,  0};
	setLegs(channels, sweeps5, 6);
	sendLegs();

	// Step 6 - Lifts only
	liftState lifts6[] = {RAISE, LOWER, LOWER, LOWER, LOWER, LOWER};
	setLegs(channels, lifts6, 6);
	sendLegs();

	// Step 7 - Sweeps only
	int sweeps7[] = {0,  5,  4,  3,  2,  1};
	setLegs(channels, sweeps7, 6);
	sendLegs();

	// Step 8 - Lifts only
	liftState lifts8[] = {LOWER, RAISE, LOWER, LOWER, LOWER, LOWER};
	setLegs(channels, lifts8, 6);
	sendLegs();

	// Step 9 - Sweeps only
	int sweeps9[] = {1,  0,  5,  4,  3,  2};
	setLegs(channels, sweeps9, 6);
	sendLegs();

	// Step 10 - Lifts only
	liftState lifts10[] = {LOWER, LOWER, RAISE, LOWER, LOWER, LOWER};
	setLegs(channels, lifts10, 6);
	sendLegs();

	// Step 11 - Sweeps only
	int sweeps11[] = {2,  1,  0,  5,  4,  3};
	setLegs(channels, sweeps11, 6);
	sendLegs();

	// Step 12 - Lifts only
	liftState lifts12[] = {LOWER, LOWER, LOWER, RAISE, LOWER, LOWER};
	setLegs(channels, lifts12, 6);
	sendLegs();
}

// Completely untested sequence
void newRipple()
{
	// Step 1 - All (initial state)
	legChannel channels[] = {RB, RC, RF, LB, LC, LF};
	int sweeps1[] =          {0,  5,  3,  3,  5,  0};
	liftState lifts1[] =     {RAISE, LOWER, LOWER, LOWER, LOWER, RAISE};
	setLegs(channels, sweeps1, lifts1, 6);
	sendLegs();

	// Step 2 - Lifts only
	liftState lifts2[] = {LOWER, RAISE, LOWER, LOWER, RAISE, LOWER};
	setLegs(channels, lifts2, 6);
	sendLegs();

	// Step 3 - Sweeps only
	int sweeps3[] = {3,  0,  5,  5,  0,  3};
	setLegs(channels, sweeps3, 6);
	sendLegs();

	// Step 4 - Lifts only
	liftState lifts4[] = {LOWER, LOWER, RAISE, RAISE, LOWER, LOWER};
	setLegs(channels, lifts4, 6);
	sendLegs();

	// Step 5 - Sweeps only
	int sweeps5[] = {5,  3,  0,  0,  3,  5};
	setLegs(channels, sweeps5, 6);
	sendLegs();

	// Step 6 - Lifts only
	liftState lifts6[] = {RAISE, LOWER, LOWER, LOWER, LOWER, RAISE};
	setLegs(channels, lifts6, 6);
	sendLegs();
}

// Old, untested
void waveGait()
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

// Old, tested
void tripodGait()
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
