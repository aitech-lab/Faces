#include "FaceTracker.h"


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
//
//            (1) (2)  i    :       (1) (2) (3)  i	  
//        [1]| 1 |   |      :   [1]| 1 |   |   |		  
//        [2]|   | 2 |      :   [2]|   | 2 |   |		  
//        [3]|   |   |      :	 j  			  
//         j
//        nw = true             nw = false

void FaceTracker::trackFaces(ofxCvHaarFinder& finder, ofImage& img, float S) {
	
	int aw = finder.blobs.size();
	int ah = trackedFaces.size();
	
	// if aw > ah
	int  lc = min(aw, ah); // link counter 
	bool nw = aw < ah;     // true - number of detected faces greater than tracked faces  

	// Allocate memory
	float** dst; dst = new float* [ah]; for (int i = 0; i < ah; ++i) dst[i] = new float[aw];
	float*  min = new float[ah]; for (int i = 0; i < ah; ++i) min[i] = 1e8;
	int*    lid = new int  [lc]; for (int i = 0; i < lc; ++i) lid[i] =  -1; // tracking rect id

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
				lid[c] = r;
			}
		}
	}
	
	for (int i=0; i<lc; i++) {
		// if nw - lid have references to finder blobs
		// else  - lid have references to already tracked faces
		if(nw) {
		
		} else {
		
		}
	}

	// Process blobs without tracked faces
	// Process tracked faces without blobs

	if (finder.blobs.size()) {
		for(int i = 0; i < finder.blobs.size(); i++) {
			ofRectangle& r = finder.blobs[i].boundingRect;
			r.x -= r.width*0.1;
			r.y -= r.width*0.2;
			r.width  *=1.2;
			r.height *=1.4;
			ofImage face;
			face.cropFrom(img, r.x*S, r.y*S, r.width*S, r.height*S);
			face.resize(120, 140);
			trackedFaces.push_back(face);
		}
	}

	// De-Allocate memory to prevent memory leak
	delete[] lid;
	delete[] min;
	for (int i = 0; i < ah; ++i) delete [] dst[i]; delete[] dst;
};