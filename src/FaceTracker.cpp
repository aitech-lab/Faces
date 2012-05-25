#include "FaceTracker.h"

#include <armadillo>

using namespace std;
using namespace arma;

FaceTracker::FaceTracker(void) {
	source = NULL;
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
	
	int bs = blobs.size();
	int fs = faces.size();
	int linked = 0;

	if (!fs && !bs) return;
	
	if (!fs && bs)	return addFaces(blobs);

	// Create 2d array of pointers to D structs
	mat D(fs, bs);
	vec fl(fs); vec bl(bs); // link establish
	fl.zeros(); bl.zeros();

	vec fmv(fs); vec bmv(bs);	// min value in row & col
	fmv.fill(1e8); bmv.fill(1e8);
	
	uvec fmi(fs); uvec bmi(bs); // min index in row & col
	fmi.fill(0); bmi.fill(0);
	
	if(bs) {
		// calc distnaces
		for(int j=0; j<fs; j++) { 
			for (int i=0; i<bs; i++) {
				// predict new position
				double l = (faces[j].center+faces[j].velocity-blobs[i].center).length();
				D(j,i) = l;
				if(l<fmv(j)) { fmv(j) = l; fmi(j) = i; }
				if(l<bmv(i)) { bmv(i) = l; bmi(i) = j; }
			}
		}
		// D.print("D");
	
		for(int j=0; j<fs; j++) {
			if(fl(j)) continue; // got alreday linked col
			int i = fmi(j);
			if(bl(i)) continue; // got already linked row
			if(bmi(i) == j) {
				// we got winer
				bool rt = faces[j].lostTrackingTimer < LOST_COUNTER; // recover track
				fl(j) = bl(i) = 1;
				faces[j].setCenter(blobs[i].center);
				faces[j].rect.width  = blobs[i].rect.width ;
				faces[j].rect.height = blobs[i].rect.height;
				faces[j].trackingTimer++;
			
				if(rt) faces[j].velocity = ofPoint(0,0); // if tracking recovered - reset speed
				
				if (source) {
					ofRectangle& r = faces[j].rect;
					faces[j].img.cropFrom(*source, r.x, r.y, r.width, r.height);
					faces[j].img.resize(128,128);
				}

				linked++;
			}
		}
	}

	// Next Situations
	// a) We have mismatched faces but still have free blobs
	//    then we need to find new matched blobs for such faces
	// b) We have mismatched faces and have no free blobs
	//    then we need count down face and predict feature pos
	// c) We have no mismatched faces but have free blobs
	//    then we ned to create new tracked faces matched to this blobs
	// d) We have no faces and blobs
	//    yahoo, we did it
	
	// a)
	if(fs-linked>0 && bs-linked>0) {
		// It's a bad idea, but we just get an closest blob there
		for(int j=0; j<fs; j++) {
			if(fl(j)) continue;
			double mv = 1e8;
			uword  mi = 0; 
			for(int i=0; i<bs; i++) {
				if(bl(i)) continue;
				if(D(i,j)<mv) {
					mi = i;
					mv = D(i,j);
				} 
			}
			
			faces[j].setCenter(blobs[mi].center);

			fl(j) = bl (mi) = 1;
			linked++;
		}
	}
	
	// b)
	if (fs-linked>0 && bs-linked==0) { // we have facesn with lost track
		for (int j=0; j<fs; j++) {
			int dec = 0;
			if(fl(j)) continue;
			int t = faces[j].lostTrackingTimer--;
			if(t<=0) {
				// length of faces dectreases by one each time so index must be shifted
				faces.erase(faces.begin()+j-(dec--)); 
			}
		}
	}

	// c)
	if(fs-linked==0 && bs-linked>0) {
		for (int i=0; i<bs; i++) {
			if(bl(i)) continue;
			addFace(blobs[i]);
		}
	}
	

};