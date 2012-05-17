#include "FaceTracker.h"

#include <armadillo>

#define LOST_TICKS 300

using namespace std;
using namespace arma;


FaceTracker::FaceTracker(void) {

}


FaceTracker::~FaceTracker(void) {

}


void FaceTracker::trackFaces(vector<Face>& blobs) {
	
	int aw = blobs.size();
	int ah = trackedFaces.size();

	mat D(aw, ah);

	// if aw > ah
	int  sc = min(aw, ah); // short side counter
	int  lc = max(aw, ah); // long side counter
	bool nw = aw > ah;     // true - number of detected faces greater than tracked faces  

	// Allocate memory
	
	for(int j = 0; j < ah; j++) {
		for(int i = 0; i < aw; i++) {
			ofRectangle& r1 = trackedFaces[j];
			ofRectangle& r2 = blobs[i];
			//float dcx = r2.x+r2.width /2.0 - r1.x-r1.width /2.0;
			//float dcy = r2.y+r2.height/2.0 - r1.y-r1.height/2.0;
			//dst[j][i] = sqrt(dcx*dcx + dcy*dcy);
			//int c = nw ? j : i; // shortest side counter
			//int r = nw ? i : j; // reference to longer side counter
			//if(dst[j][i] < min[c]) {
			//	min[c] = dst[j][i];
			//	sid[c] = r;
			//}
		}
	}


	// tracking
	for (int i=0; i<sc; i++) {
		// if nw - lid have references to finder blobs
		// else  - lid have references to already tracked faces
		lid[sid[i]] = i; 

		// set new rects for tracked faces
		if(nw) {
			trackedFacesCounter[i] = LOST_TICKS;
			//trackedFaces[i].lostCounter = LOST_TICKS;
			//trackedFaces[i].setNewRect(blobs[sid[i]]);
		} else {
			trackedFaces[sid[i]] = blobs[i]; 
			trackedFacesCounter[sid[i]] = LOST_TICKS;
			//trackedFaces[sid[i]].lostCounter = LOST_TICKS;
			//trackedFaces[sid[i]].setNewRect(blobs[i]);
		}
	}

	// Process new blobs and lost tracks
	for (int i=0; i<lc; i++) {
		if(lid[i]==-1) { // no link to face or blob
			if (nw) { 
				// we got an new untracked blob, creating new face for tracking
				// ofRectangle& r = blobs[i];
				// r.x -= r.width*0.1;
				// r.y -= r.width*0.2;
				// r.width  *=1.2;
				// r.height *=1.4;
				// Face face;
				// face.img.cropFrom(img, r.x*S, r.y*S, r.width*S, r.height*S);
				// face.img.resize(120, 140);
				// trackedFaces.push_back(face);
				trackedFaces.push_back(blobs[i]);
			} else {  
				// we got lost face, and we do not have new blob for it
				if(--trackedFacesCounter[i] <= 0) {
					trackedFaces.erase(trackedFaces.begin() + i);
				};

			}
		}
	}

	// De-Allocate memory to prevent memory leak
	for (int i = 0; i < ah; ++i) delete [] dst[i]; delete[] dst;
};