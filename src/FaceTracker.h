#pragma once

#include "Face.h"
#include "ofxCvHaarFinder.h"

class FaceTracker
{
public:
	FaceTracker(void);
	~FaceTracker(void);
	
	vector<Face> trackedFaces;

	void trackFaces(ofxCvHaarFinder& finder, ofImage& img, float S);
	
};

