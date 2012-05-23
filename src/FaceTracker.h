#pragma once

#include "ofMain.h"
#include "Face.h"

class FaceTracker
{
public:
	FaceTracker(void);
	~FaceTracker(void);
	
	ofImage* source;
	vector<Face> faces;
	
	void trackFaces(vector<Face>& blobs);
	void addFaces(vector<Face>& blobs);
	void addFace(Face& blob);
	
	string debug;
	
};

