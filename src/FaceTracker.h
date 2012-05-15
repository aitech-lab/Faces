#pragma once

#include "ofRectangle.h"

class FaceTracker
{
public:
	FaceTracker(void);
	~FaceTracker(void);
	
	vector<ofRectangle> trackedFaces;
	int                 trackedFacesCounter[100];
	void trackFaces(vector<ofRectangle>& blobs);
	
	
};

