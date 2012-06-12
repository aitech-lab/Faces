#pragma once

#include "ofMain.h"
#include "ofxCvHaarFinder.h"
#include "ofxXmlSettings.h"

class testApp : public ofBaseApp{
	public:
		void setup ();
		void update();
		void draw  ();
		void exit  ();
		
		void keyPressed   (int key);
		void keyReleased  (int key);
		void mouseMoved   (int x, int y );
		void mouseDragged (int x, int y, int button);
		void mousePressed (int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent    (ofDragInfo dragInfo);
		void gotMessage   (ofMessage msg);		

		ofxCvHaarFinder faceFinder;
		ofxCvHaarFinder eyeFinder;
		ofxCvHaarFinder leftEyeFinder;
		ofxCvHaarFinder rightEyeFinder;
		ofxCvHaarFinder mouthFinder;

		
		ofVideoGrabber grabber;
		vector<ofRectangle> blobs;
		
		ofImage labLogo;


};
