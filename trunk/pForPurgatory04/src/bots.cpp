/*
 *  bots.cpp
 *  openFrameworks
 *
 *  Created by cw wang on 6/4/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "bots.h"

void Bots::setup()
{
	
	x=ofRandom(0,ofGetWidth());
	y=ofRandom(0,ofGetHeight());
	px=x;
	py=y;
	vx=0;
	vy=0;
	//size=3;
	maxSize=18.0;
	size=ofRandom(4, 13);
	maxDepth=size*2.0;
	g=1;
	//gmin=1;
	//gmax=11;
	
	float d=ofRandom(0,1);
	if(d<.5)dir=-1;
	else dir=1;
	
	//velocity=4;
	velocity=5.0/size*dir;
	//velocity=0;
	
	vmin=0;
	vmax=6;
	falling=true;
	downhill=false;
	normalAngle=PI;
	fallCount=0;
	alive=true;
	aliveCount=0;
	lifeLength=ofRandom(500,3000);
	
	deathCount=0;
	graveBound=false;
	nFeetUnder=0;
	rotCount=0;
	rotting=false;
	ashes=false;
	growth=0;
	isTree=false;
	eating=false;
	isBeingEatenBy=-1;
}

void Bots::update()
{
	
	if (y>=py)
	{
		g*=1.04;
		downhill=true;
	}
	
	if (y<py) 
	{
		g=1.0;
		downhill=false;
	}
	
	//normal running around
	if(alive && eating==false)
	{
		x+=vx;
		y+=g;	
		
		//min max velocity
		if(fabs(velocity)<vmin) velocity=vmin*dir; 
		if(fabs(velocity)>vmax) velocity=vmax*dir;
	
		//find normal 
		float angle=atan2( (py-y),(px-x));
		if(velocity>0)	normalAngle=angle+PI/2.0;
		else normalAngle=angle-PI/2.0;
		
		vx=velocity*fabs(cos(angle));
		
		aliveCount++;
		if(aliveCount % 300 == 0)size+=.3;
		if(aliveCount>=lifeLength) die();
	}
	
	//fell to death
	else if (alive==false && deathCount<50)
	{
		velocity=0;
		y+=g;	
		deathCount++;
	}
	//rotting
	else if( ashes==false)
	{
		maxDepth=size*2.0;
		
		velocity=0;
		nFeetUnder+=.03;
		if (nFeetUnder>=maxDepth)
		{
			nFeetUnder=maxDepth;
			rotCount++;
			rotting=true;
		}
		graveBound=true;
	}
	//grow food
	else if (ashes && beingEaten==false && isTree==false)
	{
		
		growth+=.1;
		size-=.05;
		nFeetUnder-=.03;
		
		if(growth>maxDepth*2.0)
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

	//alive bots find partners
	//bots give birth
	//bots build stuff
	
	px=x;
	py=y;
	
	if (size>maxSize) size=maxSize;
	else 	if (size<.1) size=0.1;
	
	if(x>ofGetWidth()+5) x=0;
	if(x<-5) x=ofGetWidth();
	
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
	ofFill();
	//ofSetColor(210,210,210);
	pSetHSV(80,.5,.85);
	
	fallCount++;
	
	//printf("%d",fallCount);
}

void Bots::fallingSetFalse()
{	
	
	falling=false;	
	ofFill();
	pSetHSV(80,.5,.7);
	
	if(fallCount>100)
	{
		die();
	}
	else if (alive)
	{
		fallCount=0;
	}
	
}

void Bots::shiftPos(float X, float Y)
{
	x+=X;
	y-=Y;
	//printf("%f,%f\n",x,y);
}

void Bots::draw()
{
	if(alive)
	{
		//ofEllipse(x+cos(normalAngle)*size,y+sin(normalAngle)*size, size,size);
		float headX=x+cos(normalAngle)*size*4.0;
		float headY=y+sin(normalAngle)*size*4.0;
		ofEllipse(headX,headY, size,size);
		//normal line
		ofLine(x, y, headX, headY);
	}
	else if (alive==false && ashes==false)
	{
		float value=.3+(float)5.0/(int)rotCount;
		if(value>.6)value=.6;
		if(value<.33) ashes=true;
		pSetHSV(30,.9,value);
		ofEllipse(x,y+size, size,size);
	}
	else if (ashes)
	{
		drawTree();		
		pSetHSV(30,.9,.33); //dirt brown
		ofEllipse(x,y+size, size,size);
		
	}
}

void Bots::drawTree()
{
	
	//pSetHSV(30,.9,.25); //dirt brown
	//ofLine(x,y,x,y-growth);
	
	ofFill();
	//ofNoFill();
	pSetHSV(120,.9,.6); //green
	
	//for (float i=0; i<growth; i=i+growth/10)
	//	{
	/*
	 float x1= x+cos(normalAngle)*maxDepth*2.0;
	 float y1= y+sin(normalAngle)*maxDepth*2.0;
	 float x2= x+cos(normalAngle)*maxDepth*2.0;
	 float y2= y-growth*9.0;
	 float x3= x;
	 float y3= y-growth*10.0;
	 */
	
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
		float y1= y-growth*.33;
		float x2= x-growth*w*.33*d;
		float y2= y-growth*.66;
		float x3= x+growth*w*d;
		float y3= y-growth;
		
		ofBezier(x,y,x1,y1,x2,y2,x3,y3);	
	}
	
	//	}
	
	/*
	 //if(isTree)
	 //{
	 //ofEllipse(x,y-growth,size,size);
	 float scale=3;
	 float maxScale=scale;
	 for( int i=1;i<6; i++)
	 {
	 scale-=.7;
	 float ypos=y+scale/maxScale;
	 
	 float x1= x-growth/maxScale*scale;
	 float x2= x;
	 float x3= x+growth/maxScale*scale;
	 float y1=ypos-growth/2.0*i;
	 float y2=ypos-growth/2.0*i-(growth/maxScale/2.0)*scale;
	 float y3=ypos-growth/2.0*i;
	 
	 ofTriangle(x1,y1,x2,y2,x3,y3);
	 }
	 //}
	 */	
}

