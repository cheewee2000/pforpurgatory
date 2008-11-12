#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup(){	
	
	if(mpeclient.clientID!=3){
		//load walkcycles
		jogRight=new ofImage[JOGFRAMES];
		jogLeft=new ofImage[JOGFRAMES];
		for (int i = 0; i < JOGFRAMES; i++){
			jogRight[i].loadImage("../../anim/jog/right/" + ofToString(i) + ".png");
			jogLeft[i].loadImage("../../anim/jog/left/" + ofToString(i) + ".png");
		}
		runRight=new ofImage[RUNFRAMES];
		runLeft=new ofImage[RUNFRAMES];
		for (int i = 0; i < RUNFRAMES; i++){
			runRight[i].loadImage("../../anim/run/right/" + ofToString(i) + ".png");
			runLeft[i].loadImage("../../anim/run/left/" + ofToString(i) + ".png");
		}
		walkRight=new ofImage[WALKFRAMES];
		walkLeft=new ofImage[WALKFRAMES];
		for (int i = 0; i < WALKFRAMES; i++){
			walkRight[i].loadImage("../../anim/walk/right/" + ofToString(i) + ".png");
			walkLeft[i].loadImage("../../anim/walk/left/" + ofToString(i) + ".png");
		}
		carryboxwalkRight=new ofImage[CBOXWALKFRAMES];
		carryboxwalkLeft=new ofImage[CBOXWALKFRAMES];
		
		for (int i = 0; i < CBOXWALKFRAMES; i++){
			carryboxwalkRight[i].loadImage("../../anim/carryboxwalk/right/" + ofToString(i) + ".png");
			carryboxwalkLeft[i].loadImage("../../anim/carryboxwalk/left/" + ofToString(i) + ".png");
		}
		
		carryboxjogRight=new ofImage[CBOXJOGFRAMES];
		carryboxjogLeft=new ofImage[CBOXJOGFRAMES];
		
		for (int i = 0; i < CBOXJOGFRAMES; i++){
			carryboxjogRight[i].loadImage("../../anim/carryboxjog/right/" + ofToString(i) + ".png");
			carryboxjogLeft[i].loadImage("../../anim/carryboxjog/left/" + ofToString(i) + ".png");
		}
		
		fallRight=new ofImage[FALLFRAMES];
		fallLeft=new ofImage[FALLFRAMES];
		for (int i = 0; i < FALLFRAMES; i++){
			fallRight[i].loadImage("../../anim/fall/right/" + ofToString(i) + ".png");
			fallLeft[i].loadImage("../../anim/fall/left/" + ofToString(i) + ".png");
		}
		
		
		crawlRight=new ofImage[CRAWLFRAMES];
		crawlLeft=new ofImage[CRAWLFRAMES];
		for (int i = 0; i < CRAWLFRAMES; i++){
			crawlRight[i].loadImage("../../anim/crawl/right/" + ofToString(i) + ".png");
			crawlLeft[i].loadImage("../../anim/crawl/left/" + ofToString(i) + ".png");
		}
		dragboxRight=new ofImage[DRAGBOXFRAMES];
		dragboxLeft=new ofImage[DRAGBOXFRAMES];
		for (int i = 0; i < DRAGBOXFRAMES; i++){
			dragboxRight[i].loadImage("../../anim/dragbox/right/" + ofToString(i) + ".png");
			dragboxLeft[i].loadImage("../../anim/dragbox/left/" + ofToString(i) + ".png");
		}
		skipRight=new ofImage[SKIPFRAMES];
		skipLeft=new ofImage[SKIPFRAMES];
		for (int i = 0; i < SKIPFRAMES; i++){
			skipRight[i].loadImage("../../anim/skip/right/" + ofToString(i) + ".png");
			skipLeft[i].loadImage("../../anim/skip/left/" + ofToString(i) + ".png");
		}
		pullboxRight=new ofImage[PULLBOXFRAMES];
		pullboxLeft=new ofImage[PULLBOXFRAMES];
		for (int i = 0; i < PULLBOXFRAMES; i++){
			pullboxRight[i].loadImage("../../anim/pullbox/right/" + ofToString(i) + ".png");
			pullboxLeft[i].loadImage("../../anim/pullbox/left/" + ofToString(i) + ".png");
		}
		stoopwalkRight=new ofImage[STOOPWALKFRAMES];
		stoopwalkLeft=new ofImage[STOOPWALKFRAMES];
		for (int i = 0; i < STOOPWALKFRAMES; i++){
			stoopwalkRight[i].loadImage("../../anim/stoopwalk/right/" + ofToString(i) + ".png");
			stoopwalkLeft[i].loadImage("../../anim/stoopwalk/left/" + ofToString(i) + ".png");
		}
		
		marchRight=new ofImage[MARCHFRAMES];
		marchLeft=new ofImage[MARCHFRAMES];
		for (int i = 0; i < MARCHFRAMES; i++){
			marchRight[i].loadImage("../../anim/march/right/" + ofToString(i) + ".png");
			marchLeft[i].loadImage("../../anim/march/left/" + ofToString(i) + ".png");
		}
		
		/*	 
		 pushboxRight=new ofImage[PUSHBOXFRAMES];
		 pushboxLeft=new ofImage[PUSHBOXFRAMES];
		 for (int i = 0; i < PUSHBOXFRAMES; i++){
		 pushboxRight[i].loadImage("../../anim/pushbox/right/" + ofToString(i) + ".png");
		 pushboxLeft[i].loadImage("../../anim/pushbox/left/" + ofToString(i) + ".png");
		 }
		 rollcylinderRight=new ofImage[ROLLCYLINDERFRAMES];
		 rollcylinderLeft=new ofImage[ROLLCYLINDERFRAMES];
		 for (int i = 0; i < ROLLCYLINDERFRAMES; i++){
		 carryboxjogRight[i].loadImage("../../anim/rollcylinder/right/" + ofToString(i) + ".png");
		 carryboxjogLeft[i].loadImage("../../anim/rollcylinder/left/" + ofToString(i) + ".png");
		 }
		 
		 
		 
		 
		 monsterRight=new ofImage[MONSTERFRAMES];
		 monsterLeft=new ofImage[MONSTERFRAMES];
		 for (int i = 0; i < MONSTERFRAMES; i++){
		 monsterRight[i].loadImage("../../anim/monster/right/" + ofToString(i) + ".png");
		 monsterLeft[i].loadImage("../../anim/monster/left/" + ofToString(i) + ".png");
		 }
		 */
		
		
	}
	
	
	ofSoundStreamListDevices();
	// initialize framerate
	ofSetFrameRate(30);
	ofSetBackgroundAuto(false);
	// set mpeclient's parent
	mpeclient.setParent(*this);
	// setup upd mpeclient
	mpeclient.setup("networkSettings.xml");
	// start mpeclient
	
	if(mpeclient.clientID!=3)mpeclient.start();
	else mpeclient.silentStart();
	
	screenWidth=mpeclient.mWidth;
	screenHeight=mpeclient.mHeight;
	nSlots=screenWidth/2;
	slotRes=screenWidth/16;
	horizon=screenHeight-50;
	

	for ( int h=0; h<nAnchors; h++) 
	{	
		curveAnchorY[h]=horizon;	
		curveAnchorX[h]=screenWidth/(float)(nAnchors-1)*h;
	}
	
	timer=-100; //initial get http request
	maxTime=30*60*3;//frames per seconds per minutes
	
	verdana.loadFont("verdana.ttf",10, true, true);
	verdana.setLineHeight(14.0f);
	largeFont.loadFont("verdana.ttf",24, true, true);

	ofEnableAlphaBlending();

	bots= new Bots[nBots];
	
	slota=new float[nSlots];
	slotb=new float[nSlots];
	slotc=new float[nSlots];
	

	startingup=true;
	polled=false;
	
	waitForServer=true;
	

	
	// set the random seed
	//ofSeedRandom(0);

	//setupNewBot();
	/*
	for(int i=0;i<20;i++){
		bots[i].setParent(*this);
		float d=ofRandom(0,1);
		if(d<.5)d=-1.0;
		else d=1.0;
		
		bots[i].setup("0","blue","tiny", "jog", 0, horizon , d, ofRandom(20,50), ofRandom(1.0, 6.0) );
	}	
	*/
	
	//audio
	//left computer ITP
	//snoball setup
	ofSoundStreamSetup(0,1,this, 44100, 256, 4, 6);	
	//ofSoundStreamSetup(0,1,this, 44100, 256, 4, 7);	

	//2 laptop
	//ofSoundStreamSetup(0,1,this, 44100, 256, 4, 4);	
	//snowball
	//ofSoundStreamSetup(0,1,this, 44100, 256, 4, 4);	
	//ofSoundStreamSetup(0,1,this, 44100, 256, 4, 5);	

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
	 setupNewBot();

}



void testApp::setupNewBot(){
	if(polled==true){
	for (int i = 0; i < number.size(); i++){
	//	if( bots[i].number=="")
//		{
			//bots[i].setParent(*this);

			string botNum = number[i].getContent();
			string botPrefs = prefs[i].getContent();
			string botSize = sizes[i].getContent();

			/*
			int st=ofRandom(0,3);
			string botState;
			if(st==0) botState="walk";
			else if(st==1) botState="run";
			else if(st==2) botState="jog";

			else if(st==3) botState="carryboxjog";
			else if(st==4) botState="carryboxwalk";
			else if(st==5) botState="crawl";
			else if(st==6) botState="dragbox";
			else if(st==7) botState="walk";
			else if(st==8) botState="march";
			else if(st==9) botState="monster";
			else if(st==10) botState="pullbox";
			else if(st==11) botState="pushbox";
			else if(st==12) botState="rollcylinder";
			else if(st==13) botState="stoopwalk";
			*/
			
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
			
		if(waitForServer==false){
			if( bots[i].number=="")
			{
			bots[i].setParent(*this);
			bots[i].setup(botNum.c_str(),botPrefs.c_str(),botSize.c_str() ,int(ofRandom(0,screenWidth)), int(ofRandom(300,500)),int(d), int(bs), ofRandom(.3,4) );
		
			}
			
		}
			char  botString[400];
			sprintf(botString, "B,%s,%s,%s,%i,%i,%i,%i,%f,%i",botNum.c_str(),botPrefs.c_str(),botSize.c_str() ,int(ofRandom(0,screenWidth)), int(ofRandom(300,500)),int(d), int(bs), ofRandom(.3,4), i);
			mpeclient.broadcast(botString);	
			//void setup(string botNum, string botPrefs, string botSize, int xp, int yp, int d, int bs, float v);

			printf("bot %d setup\n", number.size());
		//}
	}
	}
}




//--------------------------------------------------------------
void testApp::update(){
	if(mpeclient.clientID!=3){
		
		mpeclient.update();
		if(mpeclient.bDrawNewFrame || waitForServer==false) {
			//if(mpeclient.bDrawNewFrame||mpeclient.bDrawNewFrame==false) {
			
			if(mpeclient.bMessageAvailable){
				//clients 1 and 2 recieve anchor positions from client 0
				if(mpeclient.clientID==1 || mpeclient.clientID==2){					
					
					string fullMessage = mpeclient.getDataMessage();
					
					char messages[1024];
					strcpy(messages, fullMessage.c_str());
					char * temp;
					char * messageA;
					char * messageB;
					
					
					//split messages into A and B
					temp = strtok(messages,":");
					if (temp != NULL && temp[0] == 'A') {
						messageA = temp;
						messageB = strtok (NULL, ":");
					} else if (temp != NULL && temp[0] == 'B') {
						messageB = temp;
						messageA = strtok(NULL, ":");
					}
					
					//parse messageA
					int vals[9];
					if (messageA != NULL) {
						messageA = messageA + 1;
						printf ("A: %s\n",messageA);
						char * A;
						A = strtok(messageA,",");
						for ( int h=0; h < nAnchors; h++) {
							vals[h] = atoi(A);
							curveAnchorY[h]=vals[h];	
							A = strtok (NULL, ",");
						}
					}
					
					//parse messageB
					if (messageB != NULL) {
						messageB = messageB + 1;
						printf ("B: %s\n",messageB);
						char * B;
						char * items[9];
						B = strtok(messageB,",");
						for (int h = 0; h < 9; h++) {
							items[h] = B;
							B = strtok(NULL,",");
						}
						if( bots[atoi(items[8])].number=="")
						{
							bots[atoi(items[8])].setParent(*this);
							//printf("%i %s %s %s %i %i %i %i,%f",atoi(items[8]),items[0],items[1],items[2],atoi(items[3]),atoi(items[4]),atoi(items[5]),atoi(items[6]),atof(items[7]));
							bots[atoi(items[8])].setup(items[0],items[1],items[2] ,atoi(items[3]), atoi(items[4]),atoi(items[5]), atoi(items[6]), atof(items[7]) );
						}
					}
					
					
					
				}
				
			}
		}
		
		
		for ( int h=0; h<nAnchors; h++)
		{
			//ofSetColor(0,0,0);
			//ofEllipse(curveAnchorX[h], curveAnchorY[h], 4,4);
			
			curveAnchorY[h]=smooth(screenHeight,.985, curveAnchorY[h]);
			if(curveAnchorY[h]>horizon) curveAnchorY[h]=horizon;
		}	
		
		if(mpeclient.clientID==3)
		{
			char newString[40];
			sprintf(newString, "A,%i,%i,%i,%i,%i,%i,%i,%i,%i",curveAnchorY[0],curveAnchorY[1],curveAnchorY[2],curveAnchorY[3],curveAnchorY[4],curveAnchorY[5],curveAnchorY[6],curveAnchorY[7],curveAnchorY[8]);
			mpeclient.broadcast(newString);	
		}
		
		
		if(mpeclient.clientID==3 || waitForServer==false)
		{
			if(startingup)
			{
				connection.getWebPageAsString("http://cwwang.com/bigscreens/setup.php?n=10");
				startingup=false;
			}
			
			if (timer%500==0)
			{
				pollMysql();
			}
			timer++;	
		}
		
		
		//ITP snowball Setup
		//	if(mpeclient.clientID==0)	if(left[100]>.1)	curveAnchorY[1]-=50;
		//	if(mpeclient.clientID==1)	if(left[100]>.1)	curveAnchorY[4]-=50;
		//	if(mpeclient.clientID==2)	if(left[100]>.1)	curveAnchorY[8]-=50;
		//	
		//	if(mpeclient.clientID==0)	if(left[200]>.1)	curveAnchorY[2]-=50;
		//	if(mpeclient.clientID==1)	if(left[200]>.1)	curveAnchorY[5]-=50;
		//	if(mpeclient.clientID==2)	if(left[200]>.1)	curveAnchorY[7]-=50;
		//	
		
		//if(right[100]>.2)	curveAnchorY[3]-=50;
		//if(left[200]>.2)	curveAnchorY[3]-=50;
		//if(right[200]>.2)	curveAnchorY[7]-=50;

		
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	if(mpeclient.clientID!=3){
		if(mpeclient.bDrawNewFrame || waitForServer==false) {
			//if(mpeclient.bDrawNewFrame||mpeclient.bDrawNewFrame==false) {
			
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
			for ( int i=0; i<number.size(); i++) //for each bot point
				//for ( int i=0; i<20; i++) //for each bot point
			{
				
				//---------find which slot position for this bot
				int slotPosition = floor(bots[i].x / slotWidth);
				if (slotPosition >= nSlots) slotPosition = nSlots;
				if (slotPosition <= 0) slotPosition = 0;
				
				bots[i].update(slota[slotPosition],slotb[slotPosition],slotc[slotPosition]);
				
				
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
										//bots[i].velocity=bots[i].maxSize/bots[i].size*bots[i].dir;
									}
								}
							}
						}	
					}
				}
				
				int ang=90;
				
				if(bots[i].vx>0){
					if(bots[i].fallCount>15) drawAnim(i, FALLFRAMES, fallRight, ang);
					else if(bots[i].state=="crawl") drawAnim(i, CRAWLFRAMES, crawlRight, ang);
					else if(bots[i].state=="stoop") drawAnim(i, STOOPWALKFRAMES, stoopwalkRight, ang);
					else if(bots[i].state=="march") drawAnim(i, MARCHFRAMES, marchRight, ang);
					else if(bots[i].state=="walk") drawAnim(i, WALKFRAMES, walkRight, ang);
					else if(bots[i].state=="skip") drawAnim(i, SKIPFRAMES, skipRight, ang);
					else if(bots[i].state=="jog") drawAnim(i, JOGFRAMES, jogRight, ang);
					else if(bots[i].state=="run") drawAnim(i, RUNFRAMES, runRight, ang);
					else if(bots[i].state=="carryboxjog") drawAnim(i, CBOXJOGFRAMES, carryboxjogRight, ang);
					else if(bots[i].state=="carryboxwalk") drawAnim(i, CBOXWALKFRAMES, carryboxwalkRight, ang);
					else if(bots[i].state=="dragbox") drawAnim(i, DRAGBOXFRAMES, dragboxRight, ang);
					else if(bots[i].state=="pullbox") drawAnim(i, PULLBOXFRAMES, pullboxRight, ang);
					
				}
				else if(bots[i].vx<0){
					ang=-90;
					if(bots[i].fallCount>15) drawAnim(i, FALLFRAMES, fallLeft, ang);
					
					else if(bots[i].state=="crawl") drawAnim(i, CRAWLFRAMES, crawlLeft, ang);
					else if(bots[i].state=="stoop") drawAnim(i, STOOPWALKFRAMES, stoopwalkLeft, ang);
					else if(bots[i].state=="march") drawAnim(i, MARCHFRAMES, marchLeft, ang);
					else if(bots[i].state=="walk") drawAnim(i, WALKFRAMES, walkLeft, ang);
					else if(bots[i].state=="skip") drawAnim(i, SKIPFRAMES, skipLeft, ang);
					else if(bots[i].state=="jog") drawAnim(i, JOGFRAMES, jogLeft, ang);
					else if(bots[i].state=="run") drawAnim(i, RUNFRAMES, runLeft, ang);
					else if(bots[i].state=="carryboxjog") drawAnim(i, CBOXJOGFRAMES, carryboxjogLeft, ang);
					else if(bots[i].state=="carryboxwalk") drawAnim(i, CBOXWALKFRAMES, carryboxwalkLeft, ang);
					else if(bots[i].state=="dragbox") drawAnim(i, DRAGBOXFRAMES, dragboxLeft, ang);
					else if(bots[i].state=="pullbox") drawAnim(i, PULLBOXFRAMES, pullboxLeft, ang);
				}
				
				
				ofSetColor(255,255,255);
				bots[i].draw();
			}
			
			mpeclient.done();
			mpeclient.bDrawNewFrame = false;
			
		}
	}
}



void testApp::drawAnim(int i, int frames, ofImage imageArray[], int ang){
	if (bots[i].curImage >= frames){
		bots[i].curImage = 0;
	}
	
	float angle=bots[i].degrees+ang;
	float imageWidth=bots[i].size;
	float imageHeight=bots[i].size*5/3;
	//ofPoint rPoint=ofPoint( bots[i].x, bots[i].y+imageHeight);
	//ofPoint nPoint=ofPoint(  imageHeight*cos(bots[i].angle) , imageHeight*sin(bots[i].angle) );
	
	//ofPoint nnPoint=rPoint-nPoint;
	
	//imageArray[bots[i].curImage].draw( bots[i].x-imageWidth/2.0, bots[i].y-imageHeight, imageWidth, imageHeight, angle) ;
	//imageArray[bots[i].curImage].draw( bots[i].x+cos(PI/2-bots[i].angle)*imageHeight, bots[i].y-sin(PI/2-bots[i].angle)*imageHeight, imageWidth, imageHeight, angle) ;
	//imageArray[bots[i].curImage].draw( bots[i].x+imageHeight*cos( (PI-bots[i].angle)/2.0 ), bots[i].y-sin((PI-bots[i].angle)/2.0)*imageHeight, imageWidth, imageHeight, angle) ;
	imageArray[bots[i].curImage].draw( bots[i].x-imageWidth/2-imageWidth*cos( (PI+bots[i].angle)/2.0 )/2 , bots[i].y-sin((PI-bots[i].angle)/2.0)*imageHeight, imageWidth, imageHeight, angle) ;

	//imageArray[bots[i].curImage].draw( bots[i].x-imageWidth/2.0+cos(bots[i].angle+PI)*imageWidth/2.0, bots[i].y - fabs( sin(bots[i].angle+PI) )*imageHeight , imageWidth, imageHeight, angle) ;

	drawInfo(bots[i].x+bots[i].size, bots[i].y-bots[i].size*1.5, i);
		

}

void testApp::drawInfo(int xpos,int ypos, int i){
	ofSetColor(255,255,255);
	
	//above bot
	string content = number[i].getContent();
	if(content!="0"){
	verdana.drawString(content.c_str(), xpos, ypos +20);
	
	content = name[i].getContent();
	verdana.drawString(content.c_str(),  xpos, ypos);
	
	content = prefs[i].getContent();
	verdana.drawString(content.c_str(),  xpos, ypos+10);
	}
	largeFont.drawString("Send a text message to 41411 with a size and your name",  screenWidth/2, 30);
	largeFont.drawString("e.g. tiny tim",  screenWidth/2, 60);
	largeFont.drawString("e.g. medium mary",  screenWidth/2, 90);
	largeFont.drawString("e.g. large marge",  screenWidth/2, 120);
	largeFont.drawString("e.g. xlarge andre",  screenWidth/2, 150);

}

void testApp::drawSection(){
	//set curve anchor Y positions

	//draw hills and valleys
	ofFill();
	pSetHSV(30,.9,.3);
	ofBeginShape();
	ofEnableSmoothing();//-----
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

	ofDisableSmoothing(); //-----
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
		
 		//slotRes = 70; //-------this number if gets bigger makes everybody move right wards
		
		float t,t2,t3;
		float x,y;
		
		for (int i = 0; i < slotRes; i++){
			
			t 	=  (float)i / (float)(slotRes-1.0);
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
			
			int slotNumber = startPos * slotRes + i;
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
