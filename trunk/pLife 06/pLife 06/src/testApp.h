#ifndef _TEST_APP
#define _TEST_APP


//#define OF_ADDON_USING_OFXOPENCV
#define OF_ADDON_USING_OFXOBJLOADER
#define OF_ADDON_USING_OFXDIRLIST
//#define OF_ADDON_USING_OFXVECTORMATH
#define OF_ADDON_USING_OFXNETWORK
#define OF_ADDON_USING_OFXVECTORGRAPHICS
#define OF_ADDON_USING_OFXOSC
//#define OF_ADDON_USING_OFXTHREAD
#define OF_ADDON_USING_OFXXMLSETTINGS
#define OF_ADDON_USING_OFSCRAPER

#include "ofMain.h"
#include "ofAddons.h"
#include "udpClient.h"
//#include "ball.h"
#include "bots.h"

class testApp : public ofSimpleApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed  (int key);
		void keyReleased (int key);
		
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
		
		// we don't actually use these
		// just checking to see if they 
		// all work in the same place :)
		/*
		ofxCvGrayscaleImage cvGray;
		ofxObjLoader obj;
		ofxDirList dirList;
		ofxVec2f p;
		ofxTCPClient client;
		ofxTCPServer server;
		ofxOscSender osc_sender;
		ofxThread thread;
		ofxXmlSettings settings;
		 */
	
	
	//ofscraper
	ofScraperWebConnection 			connection;
	ofScraperParser					parser;
	ofScraperXmlNode 				myNode;
	vector<ofScraperXmlNode>     	nodes;
	vector<ofScraperXmlNode>     	number;
	vector<ofScraperXmlNode>     	name; 
	vector<ofScraperXmlNode>     	prefs;
	vector<ofScraperXmlNode>     	sizes;
	void pollMysql();
	bool polled;
	
	ofTrueTypeFont 					verdana;
	
	udpClient mpeclient;
	int screenWidth;
	int screenHeight;

	
	void addBall(int x, int y);
	//ball * bouncingBalls;
	int activeBallCount;
	int maxBalls;
	
	
	
	
	
	//p vars
	#define nAnchors 9
	int curveAnchorX[nAnchors];
	int curveAnchorY[nAnchors];

	//p functions
	float smooth(float raw, float smoothness, float smoothedVal);
	void pBackground();
	void  pContourCheck1(float x, float y);
	
	
	//bots
	#define nBots 100
	Bots *bots;
	
	int timer;
	int maxTime;

	//width/8/2
	#define resolution 75
	//int resolution;
	
	//width/2
	#define slotAmount 600
	//int slotAmount;
	
	//slotAmount = (nAnchors - 1) * resolution;
	#define slotWidth 2
	//slotWidth = ofGetWidth() / slotAmount;
	
	
	float *slota;
	float *slotb;
	float *slotc;

	
	void setupNewBot();
	float horizon;
	bool startingup;
	void drawSection();
	void drawInfo(int xpos,int ypos, int i);

	void drawAnim(int i, int FRAMECOUNT, ofImage imageArray[],  int ang);


//# define JOGFRAMES 19
	//vector <ofImage> jogRight;
	//ofImage *jogRight;
	//ofImage *jogLeft;
	//ofImage jogRight;
	
	/*
	ofImage jogRight[19];
	ofImage jogLeft[19];
	ofImage runRight[14];
	ofImage runLeft[14];
	ofImage walkRight[18];
	ofImage walkLeft[18];
	*/
	
		
	
	 # define JOGFRAMES 19
	 ofImage *jogRight;
	 ofImage *jogLeft;
	# define RUNFRAMES 14	
	ofImage *runRight;
	ofImage *runLeft;
	 # define WALKFRAMES 18
	 ofImage *walkRight;
	 ofImage *walkLeft;
	/*
	 # define CBOXJOGFRAMES 17
	 ofImage *carryboxjogRight;
	 ofImage *carryboxjogLeft;
	 # define CBOXWALKFRAMES 19
	 ofImage *carryboxwalkRight;
	 ofImage *carryboxwalkLeft;
	 # define CRAWLFRAMES 29
	 ofImage *crawlRight;
	 ofImage *crawlLeft;
	 # define DRAGBOXFRAMES 20
	 ofImage *dragboxRight;
	 ofImage *dragboxLeft;
	 # define FALLFRAMES 11
	 ofImage *fallRight;
	 ofImage *fallLeft;
	 # define MARCHFRAMES 20
	 ofImage *marchRight;
	 ofImage *marchLeft;
	 # define MONSTERFRAMES 31
	 ofImage *monsterRight;
	 ofImage *monsterLeft;
	 # define PULLBOXFRAMES 19
	 ofImage *pullboxRight;
	 ofImage *pullboxLeft;
	 # define PUSHBOXFRAMES 24
	 ofImage *pushboxRight;
	 ofImage *pushboxLeft;
	 # define ROLLCYLINDERFRAMES 23
	 ofImage *rollcylinderRight;
	 ofImage *rollcylinderLeft;
	 # define SKIPFRAMES 21
	ofImage *skipRight;
	 ofImage *skipLeft;
	 # define STOOPWALKFRAMES 24
	 ofImage  *stoopwalkRight;
	 ofImage  *stoopwalkLeft;

	*/

	
	
	
	
	//audio
	void audioReceived 	(float * input, int bufferSize, int nChannels); 
	
	float * left;
	float * right;
	int 	bufferCounter;
	int 	drawCounter;
};


#endif
	
