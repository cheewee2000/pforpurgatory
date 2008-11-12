#include "ofMain.h"
#include "testApp.h"

//========================================================================
int main( ){
	//ofSetupOpenGL(1024,768, OF_FULLSCREEN);			// <-------- setup the GL context
	//ofSetupOpenGL(1440,136, OF_WINDOW);			// <-------- setup the GL context
	ofSetupOpenGL(2720,768, OF_FULLSCREEN);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	
	//no mouse cursor
	glutSetCursor(GLUT_CURSOR_NONE);	
	ofRunApp(new testApp());
	
}
