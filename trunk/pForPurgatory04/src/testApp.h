#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"

#define OF_ADDON_USING_OFXOPENCV

#include "ofAddons.h"

#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
								// otherwise, we'll use a movie file
#include "bots.h"

class testApp : public ofSimpleApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();

        #ifdef _USE_LIVE_VIDEO
		  ofVideoGrabber 		vidGrabber;
		#else
		  ofVideoPlayer 		vidPlayer;
		#endif
        
        ofxCvColorImage		colorImg;
        
        ofxCvGrayscaleImage 	grayImage;
		ofxCvGrayscaleImage 	grayBg;
		ofxCvGrayscaleImage 	grayDiff;
		
        ofxCvContourFinder 	contourFinder;

		int 				threshold;
		bool				bLearnBakground;
		
		
		//p vars
		#define nAnchors 20

		float curveAnchorX[nAnchors];
		float curveAnchorY[nAnchors];
		ofTrueTypeFont helveticaSM;

		
	//p functions
		float smooth(float raw, float smoothness, float smoothedVal);
		void pBackground();
	Bots  pContourCheck(float x, float y, Bots b);

	
	//bots
	#define nBots 100
	Bots bots[nBots];
	
};

#endif
