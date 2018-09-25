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

int getLegMapping(legChannel lc);

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

/*
	Apply multiple changes to legBuff.
	inputs:
		legChannel lc[] => base servo channels for legs to be set
		int sw[]        => sweep positions for legs
		liftState ls[]  => lift positions for legs
*/
void setLegs(legChannel lc[], int sw[], liftState ls[], int num);
void setLegs(legChannel lc[], int sw[], int num);
void setLegs(legChannel lc[], liftState ls[], int num);

/*
	Sends the servo pulse length values stored in legBuff to the servo controller
*/
void sendLegs();

/*
	Gait sequences for hexapod movement
*/
void newTripod();
void newWave();
void newRipple();
void turnRight();
void turnLeft();
void newGait();

#endif
