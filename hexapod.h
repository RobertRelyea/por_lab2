#ifndef HEXAPOD_h
#define HEXAPOD_h

#include "SSC32.h"

typedef enum{
	RAISE = 0,
	NEUTRAL,
	LOWER
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
void waveGait();
void tripodGait();

#endif
