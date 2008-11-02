#ifndef _TEST_APP
#define _TEST_APP




#define OF_ADDON_USING_OFXOPENCV
#define OF_ADDON_USING_OFXOBJLOADER
#define OF_ADDON_USING_OFXDIRLIST
#define OF_ADDON_USING_OFXVECTORMATH
#define OF_ADDON_USING_OFXNETWORK
#define OF_ADDON_USING_OFXVECTORGRAPHICS
#define OF_ADDON_USING_OFXOSC
#define OF_ADDON_USING_OFXTHREAD
#define OF_ADDON_USING_OFXXMLSETTINGS
#define OF_ADDON_USING_OFSCRAPER

#define OF_ADDON_USING_OFXVECTORMATH //ofxPhysics needs ofxVectorMath, you must include it in your project
#define OF_ADDON_USING_OFXPHYSICS            //the main physics include file, this fetches everything you need

#include "ofMain.h"
#include "ofAddons.h"

//#include "Box2D.h"


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
	
	
	//ofscraper
	ofScraperWebConnection 			connection;
	ofScraperParser					parser;
	ofScraperXmlNode 				myNode;
	vector<ofScraperXmlNode>     	nodes;
	vector<ofScraperXmlNode>     	number;
	vector<ofScraperXmlNode>     	name; 
	vector<ofScraperXmlNode>     	prefs;
	vector<ofScraperXmlNode>     	sizes;

	ofTrueTypeFont 					verdana;
	
	void pollMysql();
	
	//threadedObject	TO;	
	# define NUMFRAMES 19	
	ofImage runRight[NUMFRAMES];
	ofImage runLeft[NUMFRAMES];
	# define WALKFRAMES 20
	ofImage walkRight[WALKFRAMES];
	ofImage walkLeft[WALKFRAMES];
	# define JOGFRAMES 19
	ofImage jogRight[JOGFRAMES];
	ofImage jogLeft[JOGFRAMES];
	# define CBOXJOGFRAMES 17
	ofImage carryboxjogRight[CBOXJOGFRAMES];
	ofImage carryboxjogLeft[CBOXJOGFRAMES];
	# define CBOXWALKFRAMES 19
	ofImage carryboxwalkRight[CBOXWALKFRAMES];
	ofImage carryboxwalkLeft[CBOXWALKFRAMES];
	
	
	void setupNewBot();
	float horizon;
	bool startup;
	void drawSection();
	void drawInfo(int xpos,int ypos, int i);
};

#endif
