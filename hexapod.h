#ifndef HEXAPOD_h
#define HEXAPOD_h

#include "SSC32.h"

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
int leg_sw[][] = {leg_sw_zero, leg_sw_one, leg_sw_two, leg_sw_three, leg_sw_four, leg_sw_five};

// Reorganized lifts   RB   RC   RF   LB   LC   LF
int leg_raise[]    =  {1900,1900,1900,1100,1100,1100};
int leg_neutral[]  =  {1400,1500,1500,1500,1200,1400};
int leg_low[]      =  {1100,1100,1100,1900,1900,1900};
int leg_lift[][] = {leg_raise, leg_neutral, leg_low};

int legBuff[] = {0,0,0,0,0,0,0,0,0,0,0,0};

typedef enum{
	RAISE = 0,
	NEUTRAL,
	LOW
}liftState;

typedef enum{
	RB = 0,
	RC = 2,
	RF = 4,
	LB = 16,
	LC = 18,
	LF = 20
}legChannel;

void hexapodSetup();

/*
	Apply change to legBuff.
	inputs:
		legChannel lc => base servo channel for leg
		int sw        => sweep position for leg
		liftState ls  => lift position for leg
*/
void setLeg(legChannel lc, int sw, liftState ls);
void setLeg(legChannel lc, int sw);
void setLeg(legChannel lc, liftState ls);

// TODO
void setLegs(legChannel lc[], int sw[], liftState ls[], int num);
void setLegs(legChannel lc[], int sw[], int num);
void setLegs(legChannel lc[], liftState ls[], int num);

void sendLegs();


// Old
void rippleGait();
void tripodGait();

#endif