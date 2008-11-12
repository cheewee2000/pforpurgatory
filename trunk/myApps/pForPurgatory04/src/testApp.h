#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
//#include "Box2D.h"
#define OF_ADDON_USING_OFXOPENCV

#include "ofAddons.h"

#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
								// otherwise, we'll use a movie file
#include "bots.h"
#include <fstream> 

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

		
		//p vars
		#define nAnchors 9

		float curveAnchorX[nAnchors];
		float curveAnchorY[nAnchors];
		ofTrueTypeFont helveticaSM;

		
	//p functions
		float smooth(float raw, float smoothness, float smoothedVal);
		void pBackground();
	Bots  pContourCheck(float x, float y, Bots b);
	void saveSettings();
	void loadSettings();
	
	//bots
	#define nBots 100
	Bots bots[nBots];
	
	int timer;
	int maxTime;
	
};

#endif
