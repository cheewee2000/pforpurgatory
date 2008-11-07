/*
 *  bots.cpp
 *  openFrameworks
 *
 *  Created by cw wang on 6/4/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "bots.h"
#include "testApp.h"

void Bots::setup(string botNum, string botPrefs, string botSize, string botState, int xp, int yp, int d, int bs, float v)
{
	number=botNum;
	prefs=botPrefs;
	state=botState;
	x=xp;
	y=yp;
	dir=d;
	size=bs;
	velocity=v;
	
	maxSize=250.0;	
	
	framesPerStep=size/15.0;
	
	//curImage=ofRandom(0,9);
	curImage=0;
	
	px=x;
	py=y;
	angle=0;
	pAngleNumber=0;
	totalAngle=0;
	vx=0;
	vy=0;
	//size=3;
	
	maxDepth=size*2.0;
	g=1;

	
	vmin=1.2;
	vmax=12.0;//speed tested at iac
	
	downward=false;//**********
	uphill=false;//***********
	
	falling=true;
	downhill=false;
	normalAngle=PI;
	fallCount=0;
	alive=true;
	aliveCount=0;
	
	deathCount=0;
	graveBound=false;
	nFeetUnder=0;
	rotCount=0;
	rotting=false;
	ashes=false;
	growth=0;
	isTree=false;
	eating=false;
	beingEaten=false;//--------
	isBeingEatenBy=-1;
	
	leftCount=0;
	rightCount=0;
	
}

void Bots::setParent(testApp & _parent){
	parent = &_parent;
}

void Bots::update(float slota, float slotb, float slotc)
{
	if (y>=py)
	{
		g*=1.04;
		downward=true;//**********
	}
	
	if (y<py) 
	{
		g=1.0;
		downward=false;//**********
	}
	
	//animated png run left or right
	if(vx>0){
		rightCount++;
		leftCount=0;
	}
	else{
		leftCount++;
		rightCount=0;
	}
	if(rightCount>framesPerStep)
	{
		rightCount=1;
		//curImage++;
	}
	if(leftCount>framesPerStep)
	{
		leftCount=1;
		//curImage++;
	}
	
	if(aliveCount%2==0) {
		curImage++;
	}
	
	
	//normal running around
	if(alive && eating==false)
	{
		x+=vx;
		y+=g;	
		
		//min max velocity
		if(fabs(velocity)<vmin) velocity=vmin*dir; 
		if(fabs(velocity)>vmax) velocity=vmax*dir;
		
		if(velocity>0)	{ normalAngle = slotc + PI / 2.0;}
		else {normalAngle = slotc - PI / 2.0;}
        //vx=velocity*fabs(cos(slotc));
		//vx=velocity;
		
		//*************************judge uphill or downhill******************
		if ((float)fabs(cos(slotc)) == 1.0) //normal walking
		{
			vx=velocity*fabs(cos(slotc));
			uphill = false;
			downhill = false;
        }
		else if ((velocity > 0 && fabs(normalAngle - PI) < PI / 2.0) || (velocity < 0 && fabs(normalAngle + PI) < PI / 2.0)) // uphill
		{
			vx = velocity * fabs(cos(slotc)) * fabs(cos(slotc));
			uphill = true;
			downhill = false;
		}
		
		else if ((velocity > 0 && fabs(normalAngle) < PI / 2.0) || (velocity < 0 && normalAngle < PI / 2.0)) // downhill
		{
			vx = velocity * fabs(cos(slotc)) * (2 - fabs(cos(slotc)));
			uphill = false;
			downhill = true;
		}
		//*******************************************************
		//speeds
		if(fabs(velocity)<=3)state="walk";
		if(fabs(velocity)>3 && fabs(velocity)<5 )state="jog";
		if(fabs(velocity)>=5)state="run";

		degrees=normalAngle/PI*180.0;
		
		aliveCount++;
		//------------if(aliveCount % 300 == 0)size+=.3;
		//------------if(aliveCount>=lifeLength) die();
		
	}
	
	//fell to death
	else if (alive==false && deathCount<50)
	{
		velocity=0;
		y+=g;	
		deathCount++;
	}
	//rotting----------alive && falling or eating fit into this, problem?
	else if(ashes==false)
	{
		maxDepth=size*2.0;
		
		velocity=0;
		
		if(!alive) 
		{
			nFeetUnder+=.03;
			if (nFeetUnder>=maxDepth)
			{
				nFeetUnder=maxDepth;
				rotCount++;
				rotting=true;
			}
			graveBound=true;
		}
	}
	//grow food
	else if (ashes && beingEaten==false && isTree==false)
	{
		
		growth+=.1;
		size-=.05;
		nFeetUnder-=.03;
		
		if(growth>maxDepth*2.0 || size<0)//----some tree grows to huge
		{
			growth=maxDepth*2.0;
			isTree=true;
		}
		
	}
	//eating
	if(eating)
	{
		velocity=0;
		size+=.005;
		nFeetUnder=0;
	}
	if(isBeingEatenBy!=-1)
	{
		growth-=.1;
		//nFeetUnder-=.03;
		
	}
	
	

	if (size>maxSize) size=maxSize;
	else if (size<.1) size=0.1;
	
	if(x>parent->mpeclient.getMWidth()) {
		//dir=-1.0;
		velocity=velocity*-5;
		px=x=parent->mpeclient.getMWidth()-1;
	}
	
	if(x<0){
		dir=1.0;
		velocity=velocity*-1;
		px=x=5;
	}
	
	
	if (y >= slotb - 5 + nFeetUnder)y=slotb;
	//-----------check y position with contour
	/*
	 if (y >= slotb - 5 + nFeetUnder || graveBound)
	{
		float dx = 0;
		float dy = y - slotb - nFeetUnder;
		shiftPos(dx, dy);
		fallingSetFalse();
	}
	
	*/
	else if (downward == true) fallingSetTrue(); //************** change downhill to into downward
	px=x;
	py=y;
	
}

void Bots::fallingToDeath()
{
	
}

void Bots::die()
{
	alive=false;
}

void Bots::fallingSetTrue()
{
	falling=true;	
	eating=false;//------avoid giant tree, I don't know why
	ofFill();
	//ofSetColor(210,210,210);
	//pSetHSV(180,.5,.85);
	fallCount++;
	//printf("%d",fallCount);
}

void Bots::fallingSetFalse()
{	
	
	falling=false;	
	ofFill();
	//pSetHSV(80,.5,.7);
	
	if(fallCount>size*9)//300)
	{
		die();
	}
	else //--------if (alive)
	{
		fallCount=0;
	}
	
}

void Bots::shiftPos(float X, float Y)
{
	x+=X;
	y-=Y;
	
	//	px = x;
	//	py = y;
	//printf("%f,%f\n",x,y);
}

void Bots::draw()
{
	if(alive)
	{
		
		//ofEllipse(x+cos(normalAngle)*size,y+sin(normalAngle)*size, size,size);
		float headX=x+cos(normalAngle)*size/5.0;
		float headY=y+sin(normalAngle)*size/5.0;
		
		//----------in case upside down
		if (headY > y) 
		{
			headY = y-(headY-y);
			if (headX >= x)
			{
				headX = x-(headX-x);
			}
			else headX = x+(x-headX);
		}
		
		//pSetHSV(80,.5,.7);
		//ofEllipse(headX,headY, size/5,size/5);
		ofLine(x, y, headX, headY);
	}
	else if (alive==false && ashes==false)
	{
		float value=.3+(float)5.0/(int)rotCount;
		if(value>.6)value=.6;
		if(value<.33) ashes=true;
		pSetHSV(30,.9,value);//light brown
		ofEllipse(x,y+size, size,size);
	}
	else if (ashes)
	{
		drawTree();		
		pSetHSV(30,.9,.33); //dirt brown
		ofEllipse(x,y+size, size,size);
		
	}
	
	//printf("id=%i\talive=%i\tfalling=%i\tashes=%i\trotting=%i\tisTree=%i\n", alive, falling, ashes, rotting, isTree);
}

void Bots::drawTree()
{
	//pSetHSV(30,.9,.25); //dirt brown
	//ofLine(x,y,x,y-growth);
	
	ofFill();
	//ofNoFill();
	pSetHSV(120,.9,.6); //green
	
	
	float w=.5;
	int d=-1;
	
	for ( int i=0; i<2; i++)
	{
		if(i==0)
		{
			d=1;
			w=.3;
		}
		if(i==1)
		{
			w=.5;
			d=-1;
		}
		float x1= x;
		float y1= y-fabs(growth)*.33;      //------------change growth into fabs(growth) to turn all trees upwards
		float x2= x-fabs(growth)*w*.33*d;
		float y2= y-fabs(growth)*.66;
		float x3= x+fabs(growth)*w*d;
		float y3= y-fabs(growth);
		
		ofBezier(x,y,x1,y1,x2,y2,x3,y3);	
	}
	
}

