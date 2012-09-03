#pragma once
#include "ofMain.h"
#include "ofxXmlSettings.h"
#include <queue>

#define LOST_COUNTER 10

class Face {
public:
	Face();
	~Face();

	int id;
	int lostTrackingTimer;
	int trackingTimer;

	bool linkEstablished;
	bool recognitionInProcess;

	ofRectangle rect;
	ofPoint     center;
	ofPoint     velocity;
	ofColor     color;

	ofImage		img;
	string      uid;

	void setCenter(const ofPoint& c); 
	

	// ofImage        img;
	// ofRectangle    bounds;
	// queue<ofPoint> track;
	// int            lostCounter;


};

