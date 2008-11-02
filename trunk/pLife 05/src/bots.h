/*
 *  bots.h
 *  openFrameworks
 *
 *  Created by cw wang on 6/4/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _BOTS
#define _BOTS

#include "ofMain.h"

//#include "ofTrueTypeFont.h"
//#include "testApp.h"


class Bots{
public:
	//bot vars
	float x;
	float y;
	float size;
	float vx;
	float vy;
	float accel;
	bool falling, uphill, downhill;
	float px, py;
	float angle;
	float pAngle[5];
	int pAngleNumber;
	float totalAngle;
	//float ppx, ppy;
	float vmin, vmax;
	float velocity;
	float g, gmin,gmax;
	float dir;
	float normalAngle;
	int fallCount;
	bool alive;
	int deathCount;
	bool graveBound;
	float nFeetUnder;
	int rotCount;
	bool rotting;
	bool ashes;
	float growth;
	bool isTree;
	bool eating;
	bool beingEaten;
	int maxSize;
	int isBeingEatenBy;
	int aliveCount;
	int lifeLength;
	float maxDepth;
	
	//bots func
	void setup(string botNum, string botPrefs, string botSize);
	void draw();
	void update();	
	void fallingSetFalse();
	void fallingSetTrue();
	void die();
	void fallingToDeath();
	void shiftPos(float dx, float dy);
	void drawTree();
	
	string number;
	string prefs;
	int		curImage;
	int rightCount;
	int leftCount;
	ofImage imageSeq[11];
	float degrees;
	float framesPerStep;
	string state;
	
	
};
#endif