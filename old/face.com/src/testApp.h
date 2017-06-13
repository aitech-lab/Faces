#pragma once

#include "ofMain.h"
#include "ofxCvHaarFinder.h"
#include "FaceCom.h"
#include "FaceTracker.h"
#include "ofxXmlSettings.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		void exit();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

		ofxCvHaarFinder faceFinder;
		
		ofVideoGrabber grabber;
		vector<ofImage> faces;
		
		FaceCom     faceCom;
		FaceTracker tracker;

		ofImage labLogo;


};
