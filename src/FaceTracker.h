#pragma once

#include "ofMain.h"
#include "Face.h"

class FaceTracker
{
public:
	FaceTracker(void);
	~FaceTracker(void);
	
	vector<Face> faces;
	
	void trackFaces(vector<Face>& blobs);
	
	string debug;
	
};

