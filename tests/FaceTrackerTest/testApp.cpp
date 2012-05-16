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

	ofBackground(0);
	ofEnableAlphaBlending();
	ofSetCircleResolution(4);

	bg.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
	unsigned char* pixels = bg.getPixels();
	memset(pixels, 0x0, bg.width*bg.height*3);
	//ofSetFrameRate(300);
}

//--------------------------------------------------------------
void testApp::update(){

	unsigned char* pixels = bg.getPixels();

	if(!B.size() || (B.size() < 10 && ofRandom(0.0, 100.0) > 99.0)) {
		
		B.push_back(ofRectangle(
			ofRandom(ofGetWidth()),
			ofRandom(ofGetHeight()),
			ofRandom(40.0, 80.0),
			ofRandom(40.0, 80.0)));

		T.push_back(ofPoint(
			ofRandom(ofGetWidth()),
			ofRandom(ofGetHeight())));
		
		V.push_back(0);
		int c = ofRandom(18);
		C.push_back(ofColor(colors[c*3], colors[c*3+1], colors[c*3+2]));
	} 
	
	if(B.size() >= 5 && ofRandom(0.0, 100.0) > 99.0) {
		B.erase(B.begin());
		T.erase(T.begin());
		V.erase(V.begin());
		C.erase(C.begin());
	}

	for (int i=0; i<B.size(); i++) {
		float dx = B[i].x + B[i].width /2 - T[i].x;
		float dy = B[i].y + B[i].height/2 - T[i].y;
		float ln = sqrt(dx*dx + dy*dy);

		float v = 1.0;
		
		V[i].x += (-dx/ln*v- V[i].x)/25;
		V[i].y += (-dy/ln*v- V[i].y)/25;
		
		B[i] = B[i]+V[i];

		// T[i].x +=dy/ln/ln*1e2;
		// T[i].y -=dx/ln/ln*1e2;
		T[i].x +=dy/ln*v/2.0;
		T[i].y -=dx/ln*v/2.0;
	
		// ofPoint c = B[i].getCenter();
		// for (int j=0; j<ln/2; j++) {
		// 	static float R =  25.0;
		// 	static float l =  30.0;
		// 	float x = c.x + ofRandom(-(ln-l)/R, (ln-l)/R)+ofRandom(-(ln-l)/R, (ln-l)/R);
		// 	float y = c.y + ofRandom(-(ln-l)/R, (ln-l)/R)+ofRandom(-(ln-l)/R, (ln-l)/R);	
		// 	if(x>0 && x<bg.width-1 && y>0 && y<bg.height-1) {
		// 		int pa = ((int)x + (int)y*bg.width)*3;
		// 		float r = ofRandom(0.8, 1.0);
		// 		pixels[pa+0] = r*pixels[pa+0] + (1.0-r)*colors[((int)ln/20) % NUM_COL*3+0];
		// 		pixels[pa+1] = r*pixels[pa+1] + (1.0-r)*colors[((int)ln/20) % NUM_COL*3+1];
		// 		pixels[pa+2] = r*pixels[pa+2] + (1.0-r)*colors[((int)ln/20) % NUM_COL*3+2];
		// 	}
		// }

		if(ofRandom(0.0, 100.0) > 99.5) 
			T[i] = ofPoint( ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
	}
	bg.update();

	vector<ofRectangle> b = B;
	random_shuffle(b.begin(), b.end());
	tracker.trackFaces(b);
	
}

//--------------------------------------------------------------
void testApp::draw() {
	
	ofSetColor(255);
	bg.draw(0,0);
	//fl.draw(0,0);

	ofNoFill();
	
	for (int i=0; i<B.size(); i++) {
		ofSetColor(C[i]);
		ofRect(B[i]);
		ofCircle(T[i],5);
		ofDrawBitmapString(ofToString(i), B[i].x    , B[i].y-2);
		ofDrawBitmapString(ofToString(i), T[i].x - 3, T[i].y-6);
		
		ofSetColor(C[i], 80);
		ofLine(B[i].getCenter(), T[i]);
	}

	ofFill();
	for (int i=0; i<tracker.trackedFaces.size(); i++) {
		ofRectangle& f = tracker.trackedFaces[i];
		ofPoint      c = f.getCenter();
		ofSetColor(colors[i%21*3], colors[i%21*3+1], colors[i%21*3+2], 80);
		//ofRect(f.x+2, f.y+2, f.width-4, f.height-4);	
		ofCircle(c, 20);
		ofSetColor(colors[i%21*3], colors[i%21*3+1], colors[i%21*3+2]);
		ofDrawBitmapString(ofToString(i)+"-"+ofToString(tracker.trackedFacesCounter[i]/10), f.x + 10 , f.y-2);
	}
	ofSetColor(255);
	ofDrawBitmapString(tracker.debug, 10 , 20);
		
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

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