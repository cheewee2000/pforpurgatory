#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup(){
	ofSetWindowTitle("pLife");	
	
	startup=true;
	
	for ( int h=0; h<nAnchors; h++) 
	{	
		curveAnchorY[h]=950;	
	}
	
	helveticaSM.loadFont("Helvetica Neue.ttf", 7);
	timer=-15000; //initial get http request
	maxTime=30*60*3;//frames per seconds per minutes
	
	verdana.loadFont("verdana.ttf",10, true, true);
	verdana.setLineHeight(20.0f);
	
	ofEnableAlphaBlending();
	
	//setup mysql tables , delete and make 10 new dummies
	connection.getWebPageAsString("http://cwwang.com/bigscreens/setup.php?n=50");

	pollMysql();
	
	//load png
	for (int i = 0; i <= NUMFRAMES; i++){
		//string myImageName = "anim/left/runLeft" + ofToString(i) + ".png";
		//animImages[i].loadImage(myImageName);
		runRight[i].loadImage("anim/right/runRight" + ofToString(i) + ".png");
		runLeft[i].loadImage("anim/left/runLeft" + ofToString(i) + ".png");
		
	}
	
	
}

//--------------------------------------------------------------
void testApp::pollMysql(){
	//get bots data from mysql database
	connection.getWebPageAsString("http://cwwang.com/bigscreens/getmysql.php");
	
 	myNode = parser.parseHtml(connection.getString()); 	
    number = parser.getContentOfXpathExpression(myNode,"//number");
    name = parser.getContentOfXpathExpression(myNode,"//name");
    prefs = parser.getContentOfXpathExpression(myNode,"//prefs");
	sizes = parser.getContentOfXpathExpression(myNode,"//size");

}

//--------------------------------------------------------------
void testApp::update(){
	//ofBackground(100,100,100);
    bool bNewFrame = false;
	//printf("%f \n", ofGetFrameRate());
	
	//check for new data ever 30 seconds
	if (ofGetElapsedTimeMillis()-timer>=15000)
	{
		pollMysql();
		setupNewBot();
		timer=ofGetElapsedTimeMillis();	
		
	}
	
	timer++;
}


void testApp::setupNewBot(){
	for (int i = 0; i < number.size(); i++){
		if( bots[i].number=="")
		{
			string botNum = number[i].getContent();
			string botPrefs = prefs[i].getContent();
			string botSize = sizes[i].getContent();

			bots[i].setup(botNum.c_str(),botPrefs.c_str(),botSize.c_str()  );
			printf("bot %d setup\n", number.size());
		}
	}
}


//--------------------------------------------------------------
void testApp::draw(){
	
	pBackground();
	drawSection();
	
	//update bot positions
	for ( int i=0; i<number.size(); i++) //for each bot point
	{
		bots[i].update();
		
		// the actual part calculating the normalAngle by the nAnchors next to it
		if (bots[i].falling == false) 
		{
			for (int m = 0; m < nAnchors; m++) 
			{
				if (curveAnchorX[m] < bots[i].x && curveAnchorX[m + 1] > bots[i].x) 
				{
					bots[i].normalAngle = atan2((curveAnchorY[m+1]-curveAnchorY[m]),(curveAnchorX[m+1]-curveAnchorX[m])) + PI/2.0;
				}
			}
		}
		
		//check bots y position to contour
		bots[i]=pContourCheck(0,ofGetHeight(), bots[i]);
		for ( int j=0; j<nAnchors; j++){
			bots[i]=pContourCheck(curveAnchorX[j],curveAnchorY[j], bots[i]);
		}
		
		bots[i]=pContourCheck(ofGetWidth(),ofGetHeight(), bots[i]);
		
		//alive bots eat food
		if(bots[i].alive && bots[i].falling==false)
		{
			for (int j=0; j<nBots; j++)
			{
				if(bots[i].x<bots[j].x+3 && bots[i].x>bots[j].x-3)//Chech bot position agains dead bot position
				{
					if(bots[j].isTree) 
					{
						if (bots[j].isBeingEatenBy==i || bots[j].isBeingEatenBy==-1)
						{
							bots[i].eating=true;
							
							bots[i].x=bots[j].x;
							bots[j].isBeingEatenBy=i;
							bots[j].beingEaten=true;//------
							
							if(bots[j].growth<0)
							{
								bots[i].eating=false;	 
								bots[i].velocity=bots[i].maxSize/bots[i].size*bots[i].dir;
								//----------------bots[j].growth=0;
							}
							
						}
					}
					else
					{
						bots[i].velocity=bots[i].maxSize/bots[i].size*bots[i].dir;						
					}
				}	
			}
		}
		
		if(bots[i].rightCount>0){
			runRight[bots[i].curImage].draw( bots[i].x-bots[i].size/2.0, bots[i].y-bots[i].size,bots[i].size,bots[i].size, bots[i].degrees+90) ;
			drawInfo(bots[i].x-bots[i].size, bots[i].y-bots[i].size*1.5, i);
		}
		else{
			
			runLeft[bots[i].curImage].draw( bots[i].x-bots[i].size/2.0 , bots[i].y-bots[i].size,bots[i].size,bots[i].size,bots[i].degrees+90);
			drawInfo(bots[i].x+bots[i].size, bots[i].y-bots[i].size*1.5, i);
		}
		if (bots[i].curImage >= NUMFRAMES ){
			bots[i].curImage = 0;
		}
		
		ofSetColor(255,255,255);
		bots[i].draw();
	}
}


void testApp::drawInfo(int xpos,int ypos, int i){
	ofSetColor(255,255,255);

	//above bot
		string content = number[i].getContent();
		verdana.drawString(content.c_str(), xpos, ypos +20);
		
		content = name[i].getContent();
		verdana.drawString(content.c_str(),  xpos, ypos);
		
		content = prefs[i].getContent();
		verdana.drawString(content.c_str(),  xpos, ypos+10);

	
	/*	
	 // onscreen text
	 ofSetColor(150,150,150);
	 char reportStr[1023];
	 sprintf(reportStr, "press ' ' to capture bg\nthreshold %i (press: +/-)\nnum blobs found %i", threshold, contourFinder.nBlobs);
	 ofDrawBitmapString(reportStr, ofGetWidth()-300, ofGetHeight()-100);
	 */
	
	/*
	 if(bots[i].alive)//==false)
	 {
	 ofSetColor(150,150,150);
	 char reportStr[1023];
	 //sprintf(reportStr, "fallCount: %i \n", bots[i].fallCount);
	 //sprintf(reportStr, "nFeetUnder: %f \ngrowth: %f \nisBeingEatenBy: %d \n", bots[i].nFeetUnder, bots[i].growth, bots[i].isBeingEatenBy);
	 sprintf(reportStr, "aliveCount: %d \nsize: %f", bots[i].aliveCount, bots[i].size);
	 helveticaSM.drawString(reportStr, bots[i].x , bots[i].y);
	 }
	 */
	
}


void testApp::drawSection(){
	horizon=ofGetHeight()-50;
	//set curve anchor Y positions
	for ( int h=0; h<nAnchors; h++)
	{
		//ofSetColor(0,0,0);
		//ofEllipse(curveAnchorX[h], curveAnchorY[h], 4,4);
		curveAnchorX[h]=ofGetWidth()/(float)(nAnchors-1)*h;
		curveAnchorY[h]=smooth(ofGetHeight(),.999, curveAnchorY[h]);
		if(curveAnchorY[h]>horizon) curveAnchorY[h]=horizon;
	}
	
	//draw hills and valleys
	ofFill();
	pSetHSV(30,.9,.3);
	ofBeginShape();
	//ofEnableSmoothing();//-----
	ofCurveVertex(0,horizon);
	ofCurveVertex(0,ofGetHeight());
	for ( int i=0; i<nAnchors; i++)
	{
		//draw lines through points
		ofCurveVertex(curveAnchorX[i],curveAnchorY[i]);
	}
	ofCurveVertex(ofGetWidth(),ofGetHeight());
	ofCurveVertex(ofGetWidth(),horizon);
	//ofDisableSmoothing(); //-----
	ofEndShape();
}





//---------------------------- and for curve vertexes, since we need 4 to make a curve
std::vector <double*> pCurveVertices;

Bots  testApp::pContourCheck(float x, float y, Bots b){
	double* point = new double[3];
 	point[0] = x;
	point[1] = y;
	point[2] = 0;
	
 	pCurveVertices.push_back(point);	
	
 	if (pCurveVertices.size() >= 4){
		
 		int startPos = (int)pCurveVertices.size() - 4;
		
 		float x0 = pCurveVertices[startPos + 0][0];
	   	float y0 = pCurveVertices[startPos + 0][1];
 		float x1 = pCurveVertices[startPos + 1][0];
	   	float y1 = pCurveVertices[startPos + 1][1];
 		float x2 = pCurveVertices[startPos + 2][0];
	   	float y2 = pCurveVertices[startPos + 2][1];
 		float x3 = pCurveVertices[startPos + 3][0];
	   	float y3 = pCurveVertices[startPos + 3][1];
		
		//int resolution = 100; //100 at home//-------this number if gets bigger makes everybody move right wards		
 		int resolution =220; //-------this number if gets bigger makes everybody move right wards
		//int resolution = ofGetWidth() / (nAnchors - 1) / 2;
		
		float t,t2,t3;
		float x,y;
		
		for (int i = 0; i < resolution; i++){
			
			t 	=  (float)i / (float)(resolution-1);
			t2 	= t * t;
			t3 	= t2 * t;
			
			x = 0.5f * ( ( 2.0f * x1 ) +
						( -x0 + x2 ) * t +
						( 2.0f * x0 - 5.0f * x1 + 4 * x2 - x3 ) * t2 +
						( -x0 + 3.0f * x1 - 3.0f * x2 + x3 ) * t3 );
			
			if (b.x<=x+1 && b.x>=x-1)//----------the reason when resolution gets bigger, everything move right is because they fit in slot and be moved twice
				//-----------the reason some bots drop to bottom is because they didn't fit into any slot
			{
			    y = 0.5f * ( ( 2.0f * y1 ) +
							( -y0 + y2 ) * t +
							( 2.0f * y0 - 5.0f * y1 + 4 * y2 - y3 ) * t2 +
							( -y0 + 3.0f * y1 - 3.0f * y2 + y3 ) * t3 );
				
				//float bottomX=b.x+cos(b.normalAngle+PI)*b.size;
				//float bottomY=b.y+sin(b.normalAngle+PI)*b.size;
				if (b.y>=y-5+b.nFeetUnder || b.graveBound)
				{
					//-----rots should not move
					//float dx=b.x-x;
					float dx=0;
					if (b.alive) dx=b.x-x;
					
					float dy=b.y-y-b.nFeetUnder;
					
					b.shiftPos(dx,dy);
					b.fallingSetFalse();
				}
				else if (b.downhill == true) //------------only downwards can falling //if(b.y<y-5)
				{
					b.fallingSetTrue();
				}
			}
		}
 	}
	//-----------------------clean the cache 
	if (pCurveVertices.size() >= 11) 
	{
		pCurveVertices.clear();
	}
	
	return  b;
}


void testApp::pBackground()
{
	for (int j=0; j<ofGetHeight(); j++)
	{	
		float linePos=(float)(j)/(float)ofGetHeight();
		//dawn to noon
		pSetHSV(16+linePos*100,1,.5);
		
		//noon to dusk
		//pSetHSV(200,1,(float)(j)/( (float)ofGetHeight()-timer) );
		//pSetHSV(360.0*(float)(j)/(float)ofGetHeight(),1,1);
		ofLine(0,j,ofGetWidth(),j);
	}		
}

float testApp::smooth(float raw, float smoothness, float smoothedVal){
	if (smoothness >= 1){      // check to make sure param's are within range
		smoothness = 1;
	}
	else if (smoothness <= 0){
		smoothness = 0;
	}
	smoothedVal = (raw * (1 - smoothness)) + (smoothedVal  *  smoothness);
	return smoothedVal;
}



//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	int rate=ofRandom(130,600);
	switch (key){
			
			
		case 'q':
			curveAnchorY[0] -=rate;
			break;	
		case 'a':
			curveAnchorY[0] +=rate;
			break;	
		case 'w':
			curveAnchorY[1] -=rate;
			break;	
		case 's':
			curveAnchorY[1] +=rate;
			break;	
		case 'e':
			curveAnchorY[2] -=rate;
			break;	
		case 'd':
			curveAnchorY[2] +=rate;
			break;
		case 'r':
			curveAnchorY[3] -=rate;
			break;	
		case 'f':
			curveAnchorY[3] +=rate;
			break;		
		case 't':
			curveAnchorY[4] -=rate;
			break;	
		case 'g':
			curveAnchorY[4] +=rate;
			break;		
		case 'y':
			curveAnchorY[5] -=rate;
			break;	
		case 'h':
			curveAnchorY[5] +=rate;
			break;	
		case 'u':
			curveAnchorY[6] -=rate;
			break;	
		case 'j':
			curveAnchorY[6] +=rate;
			break;	
		case 'i':
			curveAnchorY[7] -=rate;
			break;	
		case 'k':
			curveAnchorY[7] +=rate;
			break;	
		case 'o':
			curveAnchorY[8] -=rate;
			break;	
		case 'l':
			curveAnchorY[8] +=rate;
			break;		
	}
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}	

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
	
}
