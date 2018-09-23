#include "hexapod.h"

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
	int sweeps[] =          {2,  3,  2,  3,  2,  3};
	liftState lifts[] =     {RAISE, LOW, RAISE, LOW, RAISE, LOW};
	setLegs(channels, sweeps, lifts);
	sendLegs();

	// Step 2 - Sweeps only
	sweeps[] = {3,  2,  3,  2,  3,  2};
	setLegs(channels, sweeps);
	sendLegs();

	// Step 3 - Lifts only
	lifts[] = {LOW, RAISE, LOW, RAISE, LOW, RAISE};
	setLegs(channels, lifts);
	sendLegs();

	// Step 4 - Sweeps only
	sweeps[] = {2,  3,  2,  3,  2,  3};
	setLegs(channels, sweeps);
	sendLegs();
}

// Completely untested sequence
void newWave()
{
	// Step 1 - All (initial state)
	legChannel channels[] = {RB, RC, RF, LB, LC, LF};
	int sweeps[] =          {3,  2,  1,  0,  5,  4};
	liftState lifts[] =     {LOW, LOW, LOW, RAISE, LOW, LOW};
	setLegs(channels, sweeps, lifts);
	sendLegs();

	// Step 2 - Lifts only
	lifts[] = {LOW, LOW, LOW, LOW, RAISE, LOW};
	setLegs(channels, lifts);
	sendLegs();

	// Step 3 - Sweeps only
	sweeps[] = {4,  3,  2,  1,  0,  5};
	setLegs(channels, sweeps);
	sendLegs();

	// Step 4 - Lifts only
	lifts[] = {LOW, LOW, LOW, LOW, LOW, RAISE};
	setLegs(channels, lifts);
	sendLegs();

	// Step 5 - Sweeps only
	sweeps[] = {5,  4,  3,  2,  1,  0};
	setLegs(channels, sweeps);
	sendLegs();

	// Step 6 - Lifts only
	lifts[] = {RAISE, LOW, LOW, LOW, LOW, LOW};
	setLegs(channels, lifts);
	sendLegs();

	// Step 7 - Sweeps only
	sweeps[] = {0,  5,  4,  3,  2,  1};
	setLegs(channels, sweeps);
	sendLegs();

	// Step 8 - Lifts only
	lifts[] = {LOW, RAISE, LOW, LOW, LOW, LOW};
	setLegs(channels, lifts);
	sendLegs();

	// Step 9 - Sweeps only
	sweeps[] = {1,  0,  5,  4,  3,  2};
	setLegs(channels, sweeps);
	sendLegs();

	// Step 10 - Lifts only
	lifts[] = {LOW, LOW, RAISE, LOW, LOW, LOW};
	setLegs(channels, lifts);
	sendLegs();

	// Step 11 - Sweeps only
	sweeps[] = {2,  1,  0,  5,  4,  3};
	setLegs(channels, sweeps);
	sendLegs();

	// Step 12 - Lifts only
	lifts[] = {LOW, LOW, LOW, RAISE, LOW, LOW};
	setLegs(channels, lifts);
	sendLegs();
}

// Completely untested sequence
void newRipple()
{
	// Step 1 - All (initial state)
	legChannel channels[] = {RB, RC, RF, LB, LC, LF};
	int sweeps[] =          {0,  5,  3,  3,  5,  0};
	liftState lifts[] =     {RAISE, LOW, LOW, LOW, LOW, RAISE};
	setLegs(channels, sweeps, lifts);
	sendLegs();

	// Step 2 - Lifts only
	lifts[] = {LOW, RAISE, LOW, LOW, RAISE, LOW};
	setLegs(channels, lifts);
	sendLegs();

	// Step 3 - Sweeps only
	sweeps[] = {3,  0,  5,  5,  0,  3};
	setLegs(channels, sweeps);
	sendLegs();

	// Step 4 - Lifts only
	lifts[] = {LOW, LOW, RAISE, RAISE, LOW, LOW};
	setLegs(channels, lifts);
	sendLegs();

	// Step 5 - Sweeps only
	sweeps[] = {5,  3,  0,  0,  3,  5};
	setLegs(channels, sweeps);
	sendLegs();

	// Step 6 - Lifts only
	lifts[] = {RAISE, LOW, LOW, LOW, LOW, RAISE};
	setLegs(channels, lifts);
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
