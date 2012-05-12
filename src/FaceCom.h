#pragma once
#include "ofThread.h"
#include "Face.h"
#include <queue>

class FaceCom : public ofThread {
public:
	FaceCom(void);
	~FaceCom(void);

	queue<Face>  facesQueue;
	vector<Face> processedFaces;

	void addFace(Face& f);
	void threadedFunction();

private:	
	void callFaceCom();


};

