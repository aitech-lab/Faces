#include "FaceTracker.h"

#define LOST_TICKS 30

FaceTracker::FaceTracker(void) {

}


FaceTracker::~FaceTracker(void) {

}

// TRACK METHOD
//
//          New face appears      One face disappear
// 
// finder j - [1] [2] [3]   :       [1] [2]      - ah height of matrix
//             | X | /	    :        | X | \		  
// faces  i - (1) (2)       :       (1) (2) (3)  - aw width of matrix
//							  
// Building of distance (dst) matrix, # - shortest
//        dst (*)>[*]           dst [*]>(*)
//
//            (0) (1)  i    :       (0) (1) (2)  i	  
//        [0]| # |   |      :   [0]| # |   |   |		  
//        [1]|   | # |      :   [1]|   | # |   |		  
//        [2]|   |   |      :	 j  			  
//         j
//        nw = true             nw = false
//       sid = [0, 1]          sid = [0, 1]
//       lid = [0, 1,-1]       lid = [0, 1,-1]  
//       lost face or blob = -1

void FaceTracker::trackFaces(ofxCvHaarFinder& finder, ofImage& img, float S) {
	
	int aw = finder.blobs.size();
	int ah = trackedFaces.size();
	
	// if aw > ah
	int  sc = min(aw, ah); // short side counter
	int  lc = max(aw, ah); // long side counter
	bool nw = aw < ah;     // true - number of detected faces greater than tracked faces  

	// Allocate memory
	float** dst; dst = new float* [ah]; for (int i = 0; i < ah; ++i) dst[i] = new float[aw];
	float*  min = new float[ah]; for (int i = 0; i < ah; ++i) min[i] = 1e8;
	// if nw lid - mean blob to face link else face to blob
	int*    sid = new int  [sc]; for (int i = 0; i < sc; ++i) sid[i] = -1; // link id
	int*    lid = new int  [lc]; for (int i = 0; i < lc; ++i) lid[i] = -1; // back reference id, has holes

	for(int j = 0; j < ah; j++) {
		for(int i = 0; i < aw; i++) {
			ofRectangle& r1 = trackedFaces[j].bounds;
			ofRectangle& r2 = finder.blobs[i].boundingRect;
			float dcx = r2.x+r2.width /2.0 - r1.x-r1.width /2.0;
			float dcy = r2.y+r2.height/2.0 - r1.y-r1.height/2.0;
			dst[j][i] = sqrt(dcx*dcx + dcy*dcy);
			int c = nw ? i : j; // shortest side counter
			int r = nw ? j : i; // reference to longer side counter
			if(dst[j][i] < min[c]) {
				min[c] = dst[j][i];
				sid[c] = r;
			}
		}
	}
	
	for (int i=0; i<sc; i++) {
		// if nw - lid have references to finder blobs
		// else  - lid have references to already tracked faces
		lid[sid[i]] = i; 

		// set new rects for tracked faces
		if(nw) {
			trackedFaces[i].lostCounter = LOST_TICKS;
			trackedFaces[i].setNewRect(finder.blobs[sid[i]].boundingRect);
		} else {
			trackedFaces[sid[i]].lostCounter = LOST_TICKS;
			trackedFaces[sid[i]].setNewRect(finder.blobs[i].boundingRect);
		}
	}

	for (int i=0; i<lc; i++) {
		if(lid[i]==-1) { // no link to face or blob
			if (nw) { 
				// we got an new untracked blob, creating new face for tracking
				ofRectangle& r = finder.blobs[i].boundingRect;
				r.x -= r.width*0.1;
				r.y -= r.width*0.2;
				r.width  *=1.2;
				r.height *=1.4;
				Face face;
				face.img.cropFrom(img, r.x*S, r.y*S, r.width*S, r.height*S);
				face.img.resize(120, 140);
				trackedFaces.push_back(face);				
			} else {  
				// we got lost face, and we do not have new blob for it
				trackedFaces[i].lostCounter--;
			}
		}
	}

	// De-Allocate memory to prevent memory leak
	delete[] lid;
	delete[] sid;
	delete[] min;
	for (int i = 0; i < ah; ++i) delete [] dst[i]; delete[] dst;
};