#include "testApp.h"

#define NUM_COL 21
unsigned char testApp::colors[] = { 
	0x7c, 0x9f, 0xb0,   0x56, 0x98, 0xc4,   0x9a, 0xbf, 0x88,  
	0x91, 0x63, 0xb6,   0xe2, 0x79, 0xa3,   0xe0, 0x59, 0x8b,    
	0x99, 0x37, 0x67,   0x65, 0x38, 0x7d,   0x4e, 0x24, 0x72,    
	0xc9, 0x4a, 0x53,   0xbe, 0x51, 0x68,   0xa3, 0x49, 0x74,    
	0xe2, 0x97, 0x5d,   0xf1, 0x96, 0x70,   0xe1, 0x65, 0x52,    
	0x8e, 0x8c, 0x6d,   0xe4, 0xbf, 0x80,   0xe9, 0xd7, 0x8e,    
	0x51, 0x57, 0x4a,   0x44, 0x7c, 0x69,   0x74, 0xc4, 0x93,    
};

//--------------------------------------------------------------
void testApp::setup(){
	
	oclx1 = ofGetWidth()* 4/16;
	oclx2 = ofGetWidth()*11/16;
	oclw  = ofGetWidth()   /16;

	ofBackground(0);
	ofEnableAlphaBlending();
	ofSetCircleResolution(36);

	ofSetFrameRate(5);

	nextStep = false;
	stepByStep = false;

	for(int i=0; i<5; i++) addNewBlob();
}

void testApp::addNewBlob() {
	static unsigned int id = 0;
	Face f;
	f.id = ++id;
	f.center = ofPoint(
		ofRandom(ofGetWidth ()),
		ofRandom(ofGetHeight()));
	f.rect.setFromCenter(
		f.center,
		ofRandom(40.0, 80.0),
		ofRandom(40.0, 80.0));
		
	int c = (int) ofRandom(21);
	f.color = ofColor(colors[c*3], colors[c*3+1], colors[c*3+2]);

	B.push_back(f);

	T.push_back(ofPoint(
		ofRandom(ofGetWidth ()),
		ofRandom(ofGetHeight())
	));
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	if(stepByStep && !nextStep) return;

	if(!B.size() || (B.size() < 10 && ofRandom(0.0, 100.0) > 99.5)) 
		addNewBlob();

	// random kill first 
	if(B.size() >= 5 && ofRandom(0.0, 100.0) > 99.5) {
		B.erase(B.begin());
		T.erase(T.begin());
	}

	for (int i=0; i<B.size(); i++) {
		ofPoint& bc = B[i].center;
		ofPoint  D  = T[i]-bc;
		D.normalize();
		float    v  = 50.0;
		
		B[i].velocity += (D*v-B[i].velocity)/100.0;
		
		B[i].center += B[i].velocity;
		B[i].rect.setFromCenter(B[i].center, B[i].rect.width, B[i].rect.height);

		T[i].x +=B[i].velocity.y*v/200.0;
		T[i].y -=B[i].velocity.x*v/200.0;
	
		if(ofRandom(0.0, 100.0) > 99.85) 
			T[i] = ofPoint( ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
	}

	vector<Face> b;
	// occlude  blobs
	for (int i=0; i< B.size(); i++) {
		float x = B[i].center.x;
		if((x<oclx1 || x>oclx1+oclw) && (x<oclx2 || x>oclx2+oclw)) {
			b.push_back(B[i]);
		}
	}
	
	random_shuffle(b.begin(), b.end());
	tracker.trackFaces(b);
	
	nextStep = false;
}

//--------------------------------------------------------------
void testApp::draw() {
	
	
	ofNoFill();
	
	for (int i=0; i<B.size(); i++) {
		float x = B[i].center.x;
		if((x<oclx1 || x>oclx1+oclw) && (x<oclx2 || x>oclx2+oclw)) {
			ofSetColor(B[i].color);
		} else {
			ofSetColor(B[i].color, 40);
		}
		ofRect(B[i].rect);
		ofCircle(T[i],5);
		ofDrawBitmapString(ofToString(B[i].id), B[i].rect.x, B[i].rect.y-2);
		
		ofSetColor(B[i].color, 80);
		ofLine(B[i].center, T[i]);
	}
	
	ofFill();
	for (int i=0; i<tracker.faces.size(); i++) {
		Face&   f = tracker.faces[i];
		ofPoint c = f.center;
		ofSetColor(f.color, 80);
		//ofRect(f.x+2, f.y+2, f.width-4, f.height-4);
		ofCircle(c, 20);
		ofSetColor(f.color);
		ofLine(f.center, f.center+f.velocity);
		ofDrawBitmapString(ofToString(f.id)+"-"+ofToString(tracker.faces[i].lostTrackingTimer/10), f.rect.x , f.rect.y+f.rect.height+16);
	}

	// occlusions
	ofSetColor(40, 200);
	ofFill();
	ofRect(oclx1, 0, oclw, ofGetHeight());
	ofRect(oclx2, 0, oclw, ofGetHeight());

	ofSetColor(255);
	ofDrawBitmapString(tracker.debug, 10 , 20);
		
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	if(key == ' ') nextStep   = true;
	if(key == 's') stepByStep = !stepByStep;

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}