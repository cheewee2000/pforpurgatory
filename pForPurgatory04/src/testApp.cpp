#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	
	
#ifdef _USE_LIVE_VIDEO
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(320,240);
#else
	vidPlayer.loadMovie("fingers.mov");
	vidPlayer.play();
#endif
	
    colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	grayBg.allocate(320,240);
	grayDiff.allocate(320,240);
	
	bLearnBakground = true;
	threshold = 80;
	
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
	
#ifdef _USE_LIVE_VIDEO
	vidGrabber.grabFrame();
	bNewFrame = vidGrabber.isFrameNew();
#else
	vidPlayer.idleMovie();
	bNewFrame = vidPlayer.isFrameNew();
#endif
	
	if (bNewFrame){
		
#ifdef _USE_LIVE_VIDEO
		colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
#else
		colorImg.setFromPixels(vidPlayer.getPixels(), 320,240);
#endif
		
        grayImage = colorImg;
		if (bLearnBakground == true){
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBakground = false;
		}
		
		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);
		
		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayDiff, 20, (340*240)/3, 10, true);	// find holes
	}
	
	//printf("%f \n", ofGetFrameRate());
	
	timer++;
}

//--------------------------------------------------------------
void testApp::draw(){
	
	pBackground();
	
	// draw the incoming, the grayscale, the bg and the thresholded difference
	//ofSetColor(255,255,255);
	//colorImg.draw(20,20);	
	//grayImage.draw(360,20);
	//grayBg.draw(20,280);
	
	//grayDiff.draw(0,ofGetHeight()-240);
	float contourScale = ofGetWidth()/320.0;	
	
	/*
	 
	 //contour finder
	 // ---------------------------- draw the bounding rectangle
	 ofSetColor(105,105,105);
	 glPushMatrix();
	 //glTranslatef( 0, 0, 0.0 );
	 
	 ofNoFill();
	 for( int i=0; i<contourFinder.blobs.size(); i++ ) {
	 ofRect( ofGetWidth() - contourFinder.blobs[i].boundingRect.x*contourScale, contourFinder.blobs[i].boundingRect.y*contourScale,
	 - contourFinder.blobs[i].boundingRect.width*contourScale, contourFinder.blobs[i].boundingRect.height*contourScale );
	 }
	 */
	
	/*
	 // ---------------------------- draw the blobs
	 //ofSetColor(255,20,0);
	 ofSetColor(98,98,98);
	 ofFill();
	 for( int i=0; i<contourFinder.blobs.size(); i++ ) {
	 ofBeginShape();
	 for( int j=0; j<contourFinder.blobs[i].nPts; j++ ) {
	 ofVertex(ofGetWidth() - contourFinder.blobs[i].pts[j].x*contourScale, contourFinder.blobs[i].pts[j].y*contourScale );
	 }
	 ofEndShape();
	 }
	 glPopMatrix();
	 */
	
	//find peaks and valleys
	
	for ( int h=0; h<nAnchors; h++) //for each anchor point
	{
		curveAnchorX[h]=ofGetWidth()/(float)(nAnchors-1)*h;
		
		for( int i=0; i<contourFinder.blobs.size(); i++ ) //check each blob 
		{
			for( int j=0; j<contourFinder.blobs[i].nPts; j++ ) //check all points in blob
			{
				float contX=ofGetWidth() - contourFinder.blobs[i].pts[j].x*contourScale; 
				if (h>=0)
				{
					if (contX>=curveAnchorX[h]-ofGetWidth()/nAnchors/2.0 && contX<=curveAnchorX[h]+ofGetWidth()/nAnchors/2.0) //if blob x position is within anchor point
					{
						float contY=contourFinder.blobs[i].pts[j].y*contourScale;
						if(contY < curveAnchorY[h]) //find the highest point
						{
							curveAnchorY[h]=smooth(contY,.99, curveAnchorY[h]);  //smooth changes from previous reading
						}
						
					}
				}
			}
		}
	}
	
	//draw anchors
	float horizon=ofGetHeight()-50;
	
	//ofSetColor(0,0,0);
	for ( int h=0; h<nAnchors; h++)
	{
		//ofEllipse(curveAnchorX[h], curveAnchorY[h], 4,4);
		curveAnchorY[h]=smooth(ofGetHeight(),.95, curveAnchorY[h]);
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
		for ( int j=0; j<nAnchors; j++) bots[i]=pContourCheck(curveAnchorX[j],curveAnchorY[j], bots[i]);
		bots[i]=pContourCheck(ofGetWidth(),ofGetHeight(), bots[i]);
		
		
		//alive bots eat food
		if(bots[i].alive && bots[i].falling==false)
		{
			for (int j=0; j<nBots; j++)
			{
				
				if(bots[i].x<bots[j].x+3 && bots[i].x>bots[j].x-3)
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
		
 		int resolution = 50;
		
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
		pSetHSV(200,1,(float)(j)/( (float)ofGetHeight()-timer) );
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
	
	switch (key){
		case ' ':
			bLearnBakground = true;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
			case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
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
