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
	connection.getWebPageAsString("http://cwwang.com/bigscreens/setup.php?n=10");

	pollMysql();
	
	//load pngs
	for (int i = 0; i <= WALKFRAMES; i++){
		walkRight[i].loadImage("anim/walk/right/" + ofToString(i) + ".png");
		walkLeft[i].loadImage("anim/walk/left/" + ofToString(i) + ".png");
	}
	for (int i = 0; i <= JOGFRAMES; i++){
		jogRight[i].loadImage("anim/jog/right/" + ofToString(i) + ".png");
		jogLeft[i].loadImage("anim/jog/left/" + ofToString(i) + ".png");
	}
	for (int i = 0; i <= CBOXWALKFRAMES; i++){
		carryboxwalkRight[i].loadImage("anim/carryboxwalk/right/" + ofToString(i) + ".png");
		carryboxwalkLeft[i].loadImage("anim/carryboxwalk/left/" + ofToString(i) + ".png");
	}
	for (int i = 0; i <= CBOXJOGFRAMES; i++){
		carryboxjogRight[i].loadImage("anim/carryboxjog/right/" + ofToString(i) + ".png");
		carryboxjogLeft[i].loadImage("anim/carryboxjog/left/" + ofToString(i) + ".png");
	}
	for (int i = 0; i <= CRAWLFRAMES; i++){
		crawlRight[i].loadImage("anim/crawl/right/" + ofToString(i) + ".png");
		crawlLeft[i].loadImage("anim/crawl/left/" + ofToString(i) + ".png");
	}
	for (int i = 0; i <= DRAGBOXFRAMES; i++){
		dragboxRight[i].loadImage("anim/dragbox/right/" + ofToString(i) + ".png");
		dragboxLeft[i].loadImage("anim/dragbox/left/" + ofToString(i) + ".png");
	}
	for (int i = 0; i <= FALLFRAMES; i++){
		fallRight[i].loadImage("anim/fall/right/" + ofToString(i) + ".png");
		fallLeft[i].loadImage("anim/fall/left/" + ofToString(i) + ".png");
	}
	
	for (int i = 0; i <= MARCHFRAMES; i++){
		marchRight[i].loadImage("anim/march/right/" + ofToString(i) + ".png");
		marchLeft[i].loadImage("anim/march/left/" + ofToString(i) + ".png");
	}
	/*
	 for (int i = 0; i <= MONSTERFRAMES; i++){
		monsterRight[i].loadImage("anim/monster/right/" + ofToString(i) + ".png");
		monsterLeft[i].loadImage("anim/monster/left/" + ofToString(i) + ".png");
	}
	 */
	for (int i = 0; i <= PULLBOXFRAMES; i++){
		pullboxRight[i].loadImage("anim/pullbox/right/" + ofToString(i) + ".png");
		pullboxLeft[i].loadImage("anim/pullbox/left/" + ofToString(i) + ".png");
	}
	for (int i = 0; i <= PUSHBOXFRAMES; i++){
		pushboxRight[i].loadImage("anim/pushbox/right/" + ofToString(i) + ".png");
		pushboxLeft[i].loadImage("anim/pushbox/left/" + ofToString(i) + ".png");
	}
	for (int i = 0; i <= ROLLCYLINDERFRAMES; i++){
		carryboxjogRight[i].loadImage("anim/rollcylinder/right/" + ofToString(i) + ".png");
		carryboxjogLeft[i].loadImage("anim/rollcylinder/left/" + ofToString(i) + ".png");
	}
	for (int i = 0; i <= RUNFRAMES; i++){
		runRight[i].loadImage("anim/run/right/" + ofToString(i) + ".png");
		runLeft[i].loadImage("anim/run/left/" + ofToString(i) + ".png");
	}
	for (int i = 0; i <= SKIPFRAMES; i++){
		skipRight[i].loadImage("anim/skip/right/" + ofToString(i) + ".png");
		skipLeft[i].loadImage("anim/skip/left/" + ofToString(i) + ".png");
	}
	for (int i = 0; i <= STOOPWALKFRAMES; i++){
		stoopwalkRight[i].loadImage("anim/stoopwalk/right/" + ofToString(i) + ".png");
		stoopwalkLeft[i].loadImage("anim/stoopwalk/left/" + ofToString(i) + ".png");
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
	
	//--------------calculate the normal and x,y for every slot
	pContourCheck1(0,ofGetHeight());
	for ( int j=0; j<nAnchors; j++){
		pContourCheck1(curveAnchorX[j],curveAnchorY[j]);
	}
	pContourCheck1(ofGetWidth(),ofGetHeight());

	
	
	//update bot positions
	for ( int i=0; i<number.size(); i++) //for each bot point
	{
			
		//---------find which slot position for this bot
		int slotPosition = floor(bots[i].x / slotWidth);
		if (slotPosition >= 640) slotPosition = 640;
		if (slotPosition <= 0) slotPosition = 0;
		
		bots[i].update(slot[slotPosition]);
		
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
		
		int ang=90;
		if(bots[i].rightCount>0){
			if(bots[i].state=="run") drawAnim(i, RUNFRAMES, runRight, ang);
			else if(bots[i].state=="walk") drawAnim(i, WALKFRAMES, walkRight, ang);
			else if(bots[i].state=="jog") drawAnim(i, JOGFRAMES, jogRight, ang);
			else if(bots[i].state=="carryboxjog") drawAnim(i, CBOXJOGFRAMES, carryboxjogRight, ang);
			else if(bots[i].state=="carryboxwalk") drawAnim(i, CBOXWALKFRAMES, carryboxwalkRight, ang);
			}
		else{
			ang=-90;
			if(bots[i].state=="run") drawAnim(i, RUNFRAMES, runLeft, ang);
			else if(bots[i].state=="walk") drawAnim(i, WALKFRAMES, walkLeft, ang);
			else if(bots[i].state=="jog") drawAnim(i, JOGFRAMES, jogLeft, ang);
			else if(bots[i].state=="carryboxjog") drawAnim(i, CBOXJOGFRAMES, carryboxjogLeft, ang);
			else if(bots[i].state=="carryboxwalk") drawAnim(i, CBOXWALKFRAMES, carryboxwalkLeft, ang);
		}
		
		ofSetColor(255,255,255);
		bots[i].draw();
	}
}

void testApp::drawAnim(int i, int FRAMECOUNT, ofImage imageArray[], int ang){
	imageArray[bots[i].curImage].draw( bots[i].x-bots[i].size*3.0/5.0, bots[i].y-bots[i].size,bots[i].size,bots[i].size, bots[i].degrees+ang) ;
	drawInfo(bots[i].x+bots[i].size, bots[i].y-bots[i].size*1.5, i);

	if (bots[i].curImage >= FRAMECOUNT ){
		bots[i].curImage = 0;
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

void  testApp::pContourCheck1(float x, float y){
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
		
 		//resolution = 70; //-------this number if gets bigger makes everybody move right wards
		
		float t,t2,t3;
		float x,y;
		
		for (int i = 0; i < resolution; i++){
			
			t 	=  (float)i / (float)(resolution-1.0);
			t2 	= t * t;
			t3 	= t2 * t;
			
			x = 0.5f * ( ( 2.0f * x1 ) +
						( -x0 + x2 ) * t +
						( 2.0f * x0 - 5.0f * x1 + 4 * x2 - x3 ) * t2 +
						( -x0 + 3.0f * x1 - 3.0f * x2 + x3 ) * t3 );
			
			y = 0.5f * ( ( 2.0f * y1 ) +
						( -y0 + y2 ) * t +
						( 2.0f * y0 - 5.0f * y1 + 4 * y2 - y3 ) * t2 +
						( -y0 + 3.0f * y1 - 3.0f * y2 + y3 ) * t3 );
			
			int slotNumber = startPos * resolution + i;
			slot[slotNumber][0] = x;
			slot[slotNumber][1] = y;
			if ( slotNumber == 0) 
			{
				slot[slotNumber][2] = PI;
		    }   else  {slot[slotNumber][2] = atan2((slot[slotNumber - 1][1] - slot[slotNumber][1]), (slot[slotNumber - 1][0] - slot[slotNumber][0]));}
			
		}
 	}
	//-----------------------clean the cache 
	if (pCurveVertices.size() >= 11) 
	{
		pCurveVertices.clear();
	}
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
