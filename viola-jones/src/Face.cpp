#include "Face.h"

Face::Face() {

	velocity          = ofPoint(0, 0);
	lostTrackingTimer = LOST_COUNTER;
	trackingTimer     = 0;
	linkEstablished   = false;

	recognitionInProcess = false;
}


Face::~Face() {

}

void Face::setCenter(const ofPoint& c) {
	ofPoint co = center;
	center = c;
	velocity = c - co;
	rect.setFromCenter(center, rect.width, rect.height);
	lostTrackingTimer = LOST_COUNTER;
}


