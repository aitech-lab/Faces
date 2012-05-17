#pragma once
#include "ofMain.h"

class Face {
public:
	Face(void);
	~Face(void);
	
	unsigned int id;

	ofRectangle rectBefore;
	ofRectangle rect;
	ofPoint     velocity;

};

