#include "hexapod.h"

// Servo control object
SSC32 mySSC32;

// Channel mappings for each servo
int channels[] = {0,1,2,3,4,5,16,17,18,19,20,21};

// Reorganized sweeps  RB   RC   RF   LB   LC   LF
int leg_sw_zero[]  =  {1900,1900,1750,1100,1100,1100};
int leg_sw_one[]   =  {1800,1800,1650,1200,1200,1200};
int leg_sw_two[]   =  {1700,1700,1550,1300,1300,1300};
int leg_sw_three[] =  {1450,1500,1350,1500,1550,1500};
int leg_sw_four[]  =  {1250,1300,1150,1800,1800,1700};
int leg_sw_five[]  =  {1050,1150,1000,1900,1900,1850};
int *leg_sw[] = {leg_sw_zero, leg_sw_one, leg_sw_two, leg_sw_three, leg_sw_four, leg_sw_five};

// Reorganized lifts   RB   RC   RF   LB   LC   LF
int leg_low[]    =  {2000,2000,2000,1000,1000,1000};
int leg_neutral[]  =  {1400,1500,1500,1500,1200,1400};
int leg_raise[]      =  {1000,1000,1000,2000,2000,2000};
int *leg_lift[] = {leg_raise, leg_neutral, leg_low};

int legBuff[] = {0,0,0,0,0,0,0,0,0,0,0,0};

void hexapodSetup()
{
	mySSC32.begin(9600);
	mySSC32.enableServos(channels);

  legChannel channels[] = {RB, RC, RF, LB, LC, LF};
  int sweeps1[] =          {3,  3,  3,  3,  3,  3};
  liftState lifts1[] =     {NEUTRAL, NEUTRAL, NEUTRAL, NEUTRAL, NEUTRAL, NEUTRAL};
  setLegs(channels, sweeps1, lifts1, 6);
  sendLegs();

 
	//mySSC32.setFrame(three);
	delay (1000);
	pinMode(13,OUTPUT);
}

int getLegMapping(legChannel lc)
{
  if(lc == RB)
    return 0;
  else if(lc == RC)
    return 2;
  else if(lc == RF)
    return 4;
  else if(lc == LB)
    return 6;
  else if(lc == LC)
    return 8;
  else if(lc == LF)
    return 10;
}

void setLeg(legChannel lc, int sw, liftState ls)
{
	legBuff[getLegMapping(lc)] = leg_sw[sw][getLegMapping(lc)/2];
	legBuff[getLegMapping(lc)+1] = leg_lift[ls][getLegMapping(lc)/2];
}

void setLeg(legChannel lc, int sw)
{
	legBuff[getLegMapping(lc)] = leg_sw[sw][getLegMapping(lc)/2];
}

void setLeg(legChannel lc, liftState ls)
{
	legBuff[getLegMapping(lc)+1] = leg_lift[ls][getLegMapping(lc)/2];
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

void printBuff()
{
  for(int i = 0; i < 12; ++i)
  {
    Serial.println(legBuff[i]);
  }
}


void sendLegs()
{
  //printBuff();
	mySSC32.setFrame(legBuff);
	Serial.println(micros());
	delay(50);
}

// Tested sequence, untested implementation
void newTripod()
{
	// Step 1 - All (initial state)
	legChannel channels[] = {RB, RC, RF, LB, LC, LF};
	int sweeps1[] =          {2,  3,  2,  3,  2,  3};
	liftState lifts1[] =     {LOWER, RAISE, LOWER, RAISE, LOWER, RAISE};
	setLegs(channels, sweeps1, lifts1, 6);
	sendLegs();

  //Serial.println("here1");

	// Step 2 - Sweeps only
	int sweeps2[] = {3,  2,  3,  2,  3,  2};
	setLegs(channels, sweeps2, 6);
	sendLegs();

  //Serial.println("here2");

	// Step 3 - Lifts only
	liftState lifts3[] = {RAISE, LOWER, RAISE, LOWER, RAISE, LOWER};
	setLegs(channels, lifts3, 6);
	sendLegs();

 //Serial.println("here3");

	// Step 4 - Sweeps only
	int sweeps4[] = {2,  3,  2,  3,  2,  3};
	setLegs(channels, sweeps4, 6);
	sendLegs();

 //Serial.println("here4");
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

// Completely untested sequence
void turnRight()
{
  // Step 1 - All (initial state)
  legChannel channels[] = {RB, RC, RF, LB, LC, LF};
  int sweeps1[] =          {4,  1,  4,  4,  1,  4};
  liftState lifts1[] =     {RAISE, LOWER, RAISE, LOWER, RAISE, LOWER};
  setLegs(channels, sweeps1, lifts1, 6);
  delay(100);
  sendLegs();
  

  // Step 2 - Lifts only
  liftState lifts2[] = {LOWER, RAISE, LOWER, RAISE, LOWER, RAISE};
  setLegs(channels, lifts2, 6);
  delay(100);
  sendLegs();

  // Step 3 - Sweeps only
  int sweeps3[] = {1,  4,  1,  1,  4,  1};
  setLegs(channels, sweeps3, 6);
  delay(100);
  sendLegs();

  // Step 4 - Lifts only
  liftState lifts4[] = {RAISE, LOWER, RAISE, LOWER, RAISE, LOWER};
  setLegs(channels, lifts4, 6);
  delay(100);
  sendLegs();

}
