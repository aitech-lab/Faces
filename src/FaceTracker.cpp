#include "FaceTracker.h"

#include <armadillo>

#define LOST_TICKS 300

using namespace std;
using namespace arma;


FaceTracker::FaceTracker(void) {

}


FaceTracker::~FaceTracker(void) {

}

void FaceTracker::addFaces(vector<Face>& blobs) {
	for(int i=0; i<blobs.size(); i++) addFace(blobs[i]);
}

void FaceTracker::addFace(Face& blob) {
	faces.push_back(blob);
}

void FaceTracker::trackFaces(vector<Face>& blobs) {
	
	static struct Distance {
		unsigned int j, i;
		double dst;
	};

	int bs = blobs.size();
	int fs = faces.size();

	if (!fs && !bs) return;
	
	if (!fs && bs)	return addFaces(blobs);
	
	field<Distance> D(fs, bs); 
	uvec fmin(fs); fmin.zeros();
	uvec bmin(bs); bmin.zeros();

	for(int j = 0; j < fs; j++) {
		for(int i = 0; i < bs; i++) {
			Face& ff = faces[j];
			Face& fb = blobs[i];
			ofPoint& cf = ff.center;
			ofPoint& vf = ff.velocity;
			ofPoint& cb = fb.center;
			// cf+vf - old center + velocity = predicted position
			ofPoint pr = cb - (cf+vf);
			Distance d = {j, i, pr.length() };
			D(j,i) = d;
			// search mins
			if(D(j,fmin[j]).dst > d.dst) fmin[j] = i;
			if(D(bmin[i],i).dst > d.dst) bmin[i] = j;
		}
	}
	
	// Get pairs
	for(int j = 0; j < fs; j++) {
		for(int i = 0; i < bs; i++) {
			if(fmin[j] == i && bmin[i] == j) {
				// we got fb pair
			}
		}
	}


	// tracking
	//for (int i=0; i<sc; i++) {
	//	// if nw - lid have references to finder blobs
	//	// else  - lid have references to already tracked faces
	//	lid[sid[i]] = i; 
	//
	//	// set new rects for tracked faces
	//	if(nw) {
	//		trackedFacesCounter[i] = LOST_TICKS;
	//		//trackedFaces[i].lostCounter = LOST_TICKS;
	//		//trackedFaces[i].setNewRect(blobs[sid[i]]);
	//	} else {
	//		trackedFaces[sid[i]] = blobs[i]; 
	//		trackedFacesCounter[sid[i]] = LOST_TICKS;
	//		//trackedFaces[sid[i]].lostCounter = LOST_TICKS;
	//		//trackedFaces[sid[i]].setNewRect(blobs[i]);
	//	}
	//}

	// Process new blobs and lost tracks
	//for (int i=0; i<lc; i++) {
	//	if(lid[i]==-1) { // no link to face or blob
	//		if (nw) { 
	//			// we got an new untracked blob, creating new face for tracking
	//			// ofRectangle& r = blobs[i];
	//			// r.x -= r.width*0.1;
	//			// r.y -= r.width*0.2;
	//			// r.width  *=1.2;
	//			// r.height *=1.4;
	//			// Face face;
	//			// face.img.cropFrom(img, r.x*S, r.y*S, r.width*S, r.height*S);
	//			// face.img.resize(120, 140);
	//			// trackedFaces.push_back(face);
	//			trackedFaces.push_back(blobs[i]);
	//		} else {  
	//			// we got lost face, and we do not have new blob for it
	//			if(--trackedFacesCounter[i] <= 0) {
	//				trackedFaces.erase(trackedFaces.begin() + i);
	//			};
	//
	//		}
	//	}
	//}
};