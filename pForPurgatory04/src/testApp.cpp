#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	
	//set intial anchor y positions
	for ( int h=0; h<nAnchors; h++) //for each anchor point
	{
		curveAnchorY[h]=ofGetHeight();		
	}
	
	//set initial bot positions
	for ( int i=0; i<nBots; i++) //for each anchor point
	{
		bots[i].setup();		
	}
	
	helveticaSM.loadFont("Helvetica Neue.ttf", 7);
	timer=0;
	maxTime=30*60*3;//frames per seconds per minutes
}

//--------------------------------------------------------------
void testApp::update(){
	//ofBackground(100,100,100);
    bool bNewFrame = false;
	//printf("%f \n", ofGetFrameRate());
	
	timer++;
}

//--------------------------------------------------------------
void testApp::draw(){
	
	pBackground();
	//saveSettings();
	//float contourScale = ofGetWidth()/320.0;	

	//place curve anchor X positions
	for ( int h=0; h<nAnchors; h++) //for each anchor point
	{
		curveAnchorX[h]=ofGetWidth()/(float)(nAnchors-1)*h;
	}
	
	
	//draw anchors
	float horizon=ofGetHeight()-50;
	
	//ofSetColor(0,0,0);
	
	//set curve anchor Y positions
	for ( int h=0; h<nAnchors; h++)
	{
		//ofSetColor(0,0,0);
		//ofEllipse(curveAnchorX[h], curveAnchorY[h], 4,4);
		curveAnchorY[h]=smooth(ofGetHeight(),.995, curveAnchorY[h]);
		if(curveAnchorY[h]>horizon) curveAnchorY[h]=horizon;
	}
	
	//draw hills and valleys
	ofFill();
	pSetHSV(30,.9,.3);
	
	ofBeginShape();
	
	ofCurveVertex(0,horizon);
	ofCurveVertex(0,ofGetHeight());
	for ( int i=0; i<nAnchors; i++)
	{
		//draw lines through points
		ofCurveVertex(curveAnchorX[i],curveAnchorY[i]);
		
	}
	ofCurveVertex(ofGetWidth(),ofGetHeight());
	ofCurveVertex(ofGetWidth(),horizon);
	ofEndShape();
	
	//update bot positions
	for ( int i=0; i<nBots; i++) //for each bot point
	{
		bots[i].update();
		
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
						
							if(bots[j].growth<0)
							{
								bots[i].eating=false;	 
								bots[i].velocity=bots[i].maxSize/bots[i].size*bots[i].dir;
								bots[j].growth=0;
								bots[j].setup();
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
		
		
		bots[i].draw();		
		
		//draw info here because you only want to load the font once
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
	
	/*	
	 // onscreen text
	 ofSetColor(150,150,150);
	 char reportStr[1023];
	 sprintf(reportStr, "press ' ' to capture bg\nthreshold %i (press: +/-)\nnum blobs found %i", threshold, contourFinder.nBlobs);
	 ofDrawBitmapString(reportStr, ofGetWidth()-300, ofGetHeight()-100);
	 */
}



void testApp::saveSettings() {
    ofstream fout;
    fout.open( ofToDataPath("text.txt").c_str() );
	
    fout << bots[0].x << " " << bots[0].y << endl;
	
    fout.close();
}



void testApp::loadSettings() {
    ifstream fin;
    fin.open( ofToDataPath("text.txt").c_str() );
	
    fin >> bots[0].x >> bots[0].y;
	
    fin.close();
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
		
 		int resolution = 20	0;
		
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
			
			y = 0.5f * ( ( 2.0f * y1 ) +
						( -y0 + y2 ) * t +
						( 2.0f * y0 - 5.0f * y1 + 4 * y2 - y3 ) * t2 +
						( -y0 + 3.0f * y1 - 3.0f * y2 + y3 ) * t3 );
			
			if (b.x<=x+1 && b.x>=x-1 )
			{
				//float bottomX=b.x+cos(b.normalAngle+PI)*b.size;
				//float bottomY=b.y+sin(b.normalAngle+PI)*b.size;
				if (b.y>=y-5+b.nFeetUnder || b.graveBound)
				{
					float dx=b.x-x;
					float dy=b.y-y-b.nFeetUnder;
					
					b.shiftPos(dx,dy);
					b.fallingSetFalse();
				}
				else //if(b.y<y-5)
				{
					b.fallingSetTrue();
				}
			}
		}
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
