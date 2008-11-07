#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup(){	
	// initialize framerate
	ofSetFrameRate(30);
	ofSetBackgroundAuto(false);
	// set mpeclient's parent
	mpeclient.setParent(*this);
	// setup upd mpeclient
	mpeclient.setup("networkSettings.xml");
	// start mpeclient
	mpeclient.start();
	
	screenWidth=mpeclient.mWidth;
	screenHeight=mpeclient.mHeight;
	
	//resolution=screenWidth/(nAnchors-1)/2;
	//slotAmount=screenWidth/2;
	
	

	startingup=true;
	polled=false;
	
	for ( int h=0; h<nAnchors; h++) 
	{	
		curveAnchorY[h]=950;	
	}
	
	timer=-1000; //initial get http request
	maxTime=30*60*3;//frames per seconds per minutes
	
	verdana.loadFont("verdana.ttf",10, true, true);
	verdana.setLineHeight(20.0f);
	
	ofEnableAlphaBlending();

	bots= new Bots[nBots];
	
	slota=new float[slotAmount];
	slotb=new float[slotAmount];
	slotc=new float[slotAmount];
	

/*
	walkRight=new ofImage[WALKFRAMES];
	walkLeft=new ofImage[WALKFRAMES];
	
	for (int i = 0; i <= WALKFRAMES; i++){
		walkRight[i].loadImage("anim/walk/right/" + ofToString(i) + ".png");
		walkLeft[i].loadImage("anim/walk/left/" + ofToString(i) + ".png");
	}
	*/
	

//	jogRight[0].loadImage("anim/jog/right/0.png");
//	jogRight[1].loadImage("anim/jog/right/1.png");

	jogRight=new ofImage[JOGFRAMES];
	jogLeft=new ofImage[JOGFRAMES];
	for (int i = 0; i < JOGFRAMES; i++){
		jogRight[i].loadImage("anim/jog/right/" + ofToString(i) + ".png");
		jogLeft[i].loadImage("anim/jog/left/" + ofToString(i) + ".png");
	}
	///*
	runRight=new ofImage[RUNFRAMES];
	runLeft=new ofImage[RUNFRAMES];
	for (int i = 0; i < RUNFRAMES; i++){
		runRight[i].loadImage("anim/run/right/" + ofToString(i) + ".png");
		runLeft[i].loadImage("anim/run/left/" + ofToString(i) + ".png");
	}
	walkRight=new ofImage[WALKFRAMES];
	walkLeft=new ofImage[WALKFRAMES];
	for (int i = 0; i < WALKFRAMES; i++){
		walkRight[i].loadImage("anim/walk/right/" + ofToString(i) + ".png");
		walkLeft[i].loadImage("anim/walk/left/" + ofToString(i) + ".png");
	}
	 //*/
	
	/*
	 carryboxjogRight=new ofImage[CBOXJOGFRAMES];
	 carryboxjogLeft=new ofImage[CBOXJOGFRAMES];
	 for (int i = 0; i <= CBOXWALKFRAMES; i++){
	 carryboxwalkRight[i].loadImage("anim/carryboxwalk/right/" + ofToString(i) + ".png");
	 carryboxwalkLeft[i].loadImage("anim/carryboxwalk/left/" + ofToString(i) + ".png");
	 }
	 carryboxwalkRight=new ofImage[CBOXWALKFRAMES];
	 carryboxwalkLeft=new ofImage[CBOXWALKFRAMES];
	 for (int i = 0; i <= CBOXJOGFRAMES; i++){
	 carryboxjogRight[i].loadImage("anim/carryboxjog/right/" + ofToString(i) + ".png");
	 carryboxjogLeft[i].loadImage("anim/carryboxjog/left/" + ofToString(i) + ".png");
	 }
	 crawlRight=new ofImage[CRAWLFRAMES];
	 crawlLeft=new ofImage[CRAWLFRAMES];
	 for (int i = 0; i <= CRAWLFRAMES; i++){
	 crawlRight[i].loadImage("anim/crawl/right/" + ofToString(i) + ".png");
	 crawlLeft[i].loadImage("anim/crawl/left/" + ofToString(i) + ".png");
	 }
	 dragboxRight=new ofImage[DRAGBOXFRAMES];
	 dragboxLeft=new ofImage[DRAGBOXFRAMES];
	 for (int i = 0; i <= DRAGBOXFRAMES; i++){
	 dragboxRight[i].loadImage("anim/dragbox/right/" + ofToString(i) + ".png");
	 dragboxLeft[i].loadImage("anim/dragbox/left/" + ofToString(i) + ".png");
	 }
	 fallRight=new ofImage[FALLFRAMES];
	 fallLeft=new ofImage[FALLFRAMES];
	 for (int i = 0; i <= FALLFRAMES; i++){
	 fallRight[i].loadImage("anim/fall/right/" + ofToString(i) + ".png");
	 fallLeft[i].loadImage("anim/fall/left/" + ofToString(i) + ".png");
	 }
	 marchRight=new ofImage[MARCHFRAMES];
	 marchLeft=new ofImage[MARCHFRAMES];
	 for (int i = 0; i <= MARCHFRAMES; i++){
	 marchRight[i].loadImage("anim/march/right/" + ofToString(i) + ".png");
	 marchLeft[i].loadImage("anim/march/left/" + ofToString(i) + ".png");
	 }
	 pullboxRight=new ofImage[PULLBOXFRAMES];
	 pullboxLeft=new ofImage[PULLBOXFRAMES];
	 for (int i = 0; i <= PULLBOXFRAMES; i++){
	 pullboxRight[i].loadImage("anim/pullbox/right/" + ofToString(i) + ".png");
	 pullboxLeft[i].loadImage("anim/pullbox/left/" + ofToString(i) + ".png");
	 }
	 
	 pushboxRight=new ofImage[PUSHBOXFRAMES];
	 pushboxLeft=new ofImage[PUSHBOXFRAMES];
	 for (int i = 0; i <= PUSHBOXFRAMES; i++){
	 pushboxRight[i].loadImage("anim/pushbox/right/" + ofToString(i) + ".png");
	 pushboxLeft[i].loadImage("anim/pushbox/left/" + ofToString(i) + ".png");
	 }
	 rollcylinderRight=new ofImage[ROLLCYLINDERFRAMES];
	 rollcylinderLeft=new ofImage[ROLLCYLINDERFRAMES];
	 for (int i = 0; i <= ROLLCYLINDERFRAMES; i++){
	 carryboxjogRight[i].loadImage("anim/rollcylinder/right/" + ofToString(i) + ".png");
	 carryboxjogLeft[i].loadImage("anim/rollcylinder/left/" + ofToString(i) + ".png");
	 }
	 runRight=new ofImage[RUNFRAMES];
	 runLeft=new ofImage[RUNFRAMES];
	 
	 for (int i = 0; i <= RUNFRAMES; i++){
	 runRight[i].loadImage("anim/run/right/" + ofToString(i) + ".png");
	 runLeft[i].loadImage("anim/run/left/" + ofToString(i) + ".png");
	 }
	 skipRight=new ofImage[SKIPFRAMES];
	 skipLeft=new ofImage[SKIPFRAMES];
	 for (int i = 0; i <= SKIPFRAMES; i++){
	 skipRight[i].loadImage("anim/skip/right/" + ofToString(i) + ".png");
	 skipLeft[i].loadImage("anim/skip/left/" + ofToString(i) + ".png");
	 }
	 
	 stoopwalkRight=new ofImage[STOOPWALKFRAMES];
	 stoopwalkLeft=new ofImage[STOOPWALKFRAMES];
	 
	 
	 for (int i = 0; i <= STOOPWALKFRAMES; i++){
	 stoopwalkRight[i].loadImage("anim/stoopwalk/right/" + ofToString(i) + ".png");
	 stoopwalkLeft[i].loadImage("anim/stoopwalk/left/" + ofToString(i) + ".png");
	 }
	 */
	
	/*
	 monsterRight=new ofImage[MONSTERFRAMES];
	 monsterLeft=new ofImage[MONSTERFRAMES];
	 for (int i = 0; i <= MONSTERFRAMES; i++){
	 monsterRight[i].loadImage("anim/monster/right/" + ofToString(i) + ".png");
	 monsterLeft[i].loadImage("anim/monster/left/" + ofToString(i) + ".png");
	 }
	 */

	
	
	//setup mysql tables , delete and make 10 new dummies
	//connection.getWebPageAsString("http://cwwang.com/bigscreens/setup.php?n=10");
	
	//pollMysql();
	horizon=screenHeight-50;

	
	for ( int h=0; h<nAnchors; h++)
	{
		curveAnchorX[h]=screenWidth/(float)(nAnchors-1)*h;
	}

	
	
	// set the random seed
	//ofSeedRandom(0);

	
	for(int i=0;i<20;i++){
		bots[i].setParent(*this);
		float d=ofRandom(0,1);
		if(d<.5)d=-1.0;
		else d=1.0;
		
		bots[i].setup("0","blue","tiny", "jog", 0, ofRandom(200,250) , d, ofRandom(20,50), ofRandom(1.0, 6.0) );
	}	
	
	
	//audio
	ofSoundStreamSetup(0,2,this, 44100, 256, 4);	
	left = new float[256];
	right = new float[256];
	
	
	bufferCounter = 0;
	drawCounter = 0;
	
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
	 polled=true;
}



void testApp::setupNewBot(){
	if(polled==true){
	for (int i = 0; i < number.size(); i++){
		if( bots[i].number=="")
		{
			string botNum = number[i].getContent();
			string botPrefs = prefs[i].getContent();
			string botSize = sizes[i].getContent();

			bots[i].setParent(*this);

			int st=ofRandom(0,12);
			string state;
			if(st==0) state="walk";
			else if(st==0) state="run";
			else if(st==1) state="carryboxjog";
			else if(st==2) state="carryboxwalk";
			else if(st==3) state="crawl";
			else if(st==4) state="dragbox";
			else if(st==5) state="walk";
			else if(st==6) state="jog";
			else if(st==7) state="march";
			else if(st==8) state="monster";
			else if(st==9) state="pullbox";
			else if(st==10) state="pushbox";
			else if(st==11) state="rollcylinder";
			else if(st==12) state="stoopwalk";
			
			float d=ofRandom(0,1);
			if(d<.5)d=-1.0;
			else d=1.0;
			
			int bs;
			if(botSize=="tiny")	bs=ofRandom(20, 40);
			else if(botSize=="medium")bs=ofRandom(40, 80);
			else if(botSize=="large")bs=ofRandom(80, 150);
			else if(botSize=="xlarge")bs=ofRandom(150, 200);
			else if(botSize=="xxlarge")	bs=ofRandom(200, 250);
			//else bs=ofRandom(50, 80);
			else bs=ofRandom(20, 150);//sizes test at iac
	
			
			
			bots[i].setup(botNum.c_str(),botPrefs.c_str(),botSize.c_str(), state ,ofRandom(0,screenWidth), ofRandom(300,500),d, bs, ofRandom(.1,6.0)  );
			printf("bot %d setup\n", number.size());
		}
	}
	}
}

//--------------------------------------------------------------
void testApp::update(){
	mpeclient.update();
	//if(mpeclient.bDrawNewFrame) {
	if(mpeclient.bDrawNewFrame||mpeclient.bDrawNewFrame==false) {

		if(mpeclient.bMessageAvailable){
			//clients 1 and 2 recieve anchor positions from client 0
			if(mpeclient.clientID==1 || mpeclient.clientID==2){
				string * messages = mpeclient.getDataMessage();
				for ( int h=0; h<nAnchors; h++) 
				{	
					curveAnchorY[h]=atoi(messages[h].c_str());	
				}
			}
		}
			
		
		//if(mpeclient.clientID==0)
		//{
			for ( int h=0; h<nAnchors; h++)
			{
				//ofSetColor(0,0,0);
				//ofEllipse(curveAnchorX[h], curveAnchorY[h], 4,4);
				curveAnchorY[h]=smooth(screenHeight,.99, curveAnchorY[h]);
				if(curveAnchorY[h]>horizon) curveAnchorY[h]=horizon;
			}
			char newString[40];
			sprintf(newString, "%i,%i,%i,%i,%i,%i,%i,%i,%i",curveAnchorY[0],curveAnchorY[1],curveAnchorY[2],curveAnchorY[3],curveAnchorY[4],curveAnchorY[5],curveAnchorY[6],curveAnchorY[7],curveAnchorY[8]);
			mpeclient.broadcast(newString);	
		//}
		
		
		
		//client 3 does the database stuff
		if(mpeclient.clientID==3){
			if(startingup)	connection.getWebPageAsString("http://cwwang.com/bigscreens/setup.php?n=10");

			if (timer%1000==0)
			{
				
				pollMysql();
				//char newString[40];
				//sprintf(newString, "%i,%i", mpeclient.xOffset, mpeclient.yOffset);
				//mpeclient.broadcast(newString);

				setupNewBot();
				timer++;				
			}
		}
		
		

	}
}

//--------------------------------------------------------------
void testApp::draw(){
	//if(mpeclient.bDrawNewFrame) {
		if(mpeclient.bDrawNewFrame||mpeclient.bDrawNewFrame==false) {
	
		// do all of your drawing here 
		
		mpeclient.placeScreen();
		
		
		pBackground();
		drawSection();
		
		
		//--------------calculate the normal and x,y for every slot
			//if(mpeclient.clientID==0){
				pContourCheck1(0,screenHeight);
				for ( int j=0; j<nAnchors; j++){
					pContourCheck1(curveAnchorX[j],curveAnchorY[j]);
				}
				pContourCheck1(screenWidth,screenHeight);
				
			//}
		
		//update bot positions
		//for ( int i=0; i<number.size(); i++) //for each bot point
		for ( int i=0; i<20; i++) //for each bot point
			{
			
			//---------find which slot position for this bot
			int slotPosition = floor(bots[i].x / slotWidth);
			if (slotPosition >= 640) slotPosition = 640;
			if (slotPosition <= 0) slotPosition = 0;
			
			bots[i].update(slota[slotPosition],slotb[slotPosition],slotc[slotPosition]);
				
				//if(bots[i].y>slotb[slotPosition])bots[i].y=slotb[slotPosition];
				//bots[i].y=screenHeight;
				
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
			if(bots[i].state=="jog") drawAnim(i, JOGFRAMES, jogRight, ang);
			else if(bots[i].state=="run") drawAnim(i, RUNFRAMES, runRight, ang);
			 else if(bots[i].state=="walk") drawAnim(i, WALKFRAMES, walkRight, ang);
//			 else if(bots[i].state=="jog") drawAnim(i, JOGFRAMES, jogRight, ang);
//			 else if(bots[i].state=="carryboxjog") drawAnim(i, CBOXJOGFRAMES, carryboxjogRight, ang);
//			 else if(bots[i].state=="carryboxwalk") drawAnim(i, CBOXWALKFRAMES, carryboxwalkRight, ang);
			 }
			 else if(bots[i].leftCount>0){
			 ang=-90;
			if(bots[i].state=="jog") drawAnim(i, JOGFRAMES, jogLeft, ang);
			 else if(bots[i].state=="run") drawAnim(i, RUNFRAMES, runLeft, ang);
			 else if(bots[i].state=="walk") drawAnim(i, WALKFRAMES, walkLeft, ang);
//			 else if(bots[i].state=="jog") drawAnim(i, JOGFRAMES, jogLeft, ang);
//			 else if(bots[i].state=="carryboxjog") drawAnim(i, CBOXJOGFRAMES, carryboxjogLeft, ang);
//			 else if(bots[i].state=="carryboxwalk") drawAnim(i, CBOXWALKFRAMES, carryboxwalkLeft, ang);
			 }
			 
			
			ofSetColor(255,255,255);
			bots[i].draw();
		}
		
		mpeclient.done();
		mpeclient.bDrawNewFrame = false;

	}
}



void testApp::drawAnim(int i, int frames, ofImage imageArray[], int ang){
	if (bots[i].curImage >= frames){
		bots[i].curImage = 0;
	}
	imageArray[bots[i].curImage].draw( bots[i].x-bots[i].size*3.0/5.0, bots[i].y-bots[i].size,bots[i].size,bots[i].size, bots[i].degrees+ang) ;
	//drawInfo(bots[i].x+bots[i].size, bots[i].y-bots[i].size*1.5, i);
		

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
	
}

void testApp::drawSection(){
	//set curve anchor Y positions

	//draw hills and valleys
	ofFill();
	pSetHSV(30,.9,.3);
	ofBeginShape();
	//ofEnableSmoothing();//-----
	ofCurveVertex(-100,screenHeight);
	ofCurveVertex(-100,horizon);
	//ofCurveVertex(0,screenHeight);
	for ( int i=0; i<nAnchors; i++)
	{
		//draw lines through points
		ofCurveVertex(curveAnchorX[i],curveAnchorY[i]);
	}
	//ofCurveVertex(screenWidth,screenHeight);
	ofCurveVertex(screenWidth+100,horizon);
	ofCurveVertex(screenWidth+100,screenHeight);
	ofCurveVertex(0,screenHeight);
	ofCurveVertex(0,horizon);

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
			slota[slotNumber] = x;
			slotb[slotNumber] = y;
			if ( slotNumber == 0) 
			{
				slotc[slotNumber] = PI;
		    }   
			else  {slotc[slotNumber] = atan2((slotb[slotNumber - 1] - slotb[slotNumber]), (slota[slotNumber - 1] - slota[slotNumber]));}
			
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
	for (int j=0; j<screenHeight; j++)
	{	
		float linePos=(float)(j)/(float)screenHeight;
		//dawn to noon
		pSetHSV(16+linePos*100,1,.5);
		
		//noon to dusk
		//pSetHSV(200,1,(float)(j)/( (float)screenHeight-timer) );
		//pSetHSV(360.0*(float)(j)/(float)screenHeight,1,1);
		ofLine(0,j,screenWidth,j);
	}		
}



void testApp::audioReceived 	(float * input, int bufferSize, int nChannels){	
	// samples are "interleaved"
	for (int i = 0; i < bufferSize; i++){
		left[i] = input[i*2];
		right[i] = input[i*2+1];
	}
	bufferCounter++;
	
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
void testApp::keyReleased  (int key){ 
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
//	char newString[40];
//	
//	sprintf(newString, "%i,%i", x+mpeclient.xOffset, y+mpeclient.yOffset);
//	
//	mpeclient.broadcast(newString);
//	
	
}
//--------------------------------------------------------------
void testApp::mouseReleased(){

}
