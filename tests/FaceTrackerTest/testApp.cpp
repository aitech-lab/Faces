#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0);
	ofEnableAlphaBlending();
	ofSetCircleResolution(4);

	bg.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
	unsigned char* pixels = bg.getPixels();
	memset(pixels, 0, bg.width*bg.height*3);
}

//--------------------------------------------------------------
void testApp::update(){
	unsigned char* pixels = bg.getPixels();

	if(!B.size() || (B.size() < 9 && ofRandom(0.0, 100.0) > 99.0)) {
		
		B.push_back(ofRectangle(
			ofRandom(ofGetWidth()),
			ofRandom(ofGetHeight()),
			ofRandom(40.0, 80.0),
			ofRandom(40.0, 80.0)));

		T.push_back(ofPoint(
			ofRandom(ofGetWidth()),
			ofRandom(ofGetHeight())));
		
		V.push_back(0);

		C.push_back(ofColor(
			ofRandom(128.0, 255.0), 
			ofRandom(128.0, 255.0),
			ofRandom(128.0, 255.0)));
	} 

	for (int i=0; i<B.size(); i++) {
		float dx = B[i].x + B[i].width /2 - T[i].x;
		float dy = B[i].y + B[i].height/2 - T[i].y;
		float ln = sqrt(dx*dx + dy*dy);
		
		V[i].x += (-dx/ln*5 - V[i].x)/40;
		V[i].y += (-dy/ln*5 - V[i].y)/40;
		
		B[i] = B[i]+V[i];

		T[i].x +=dy/ln*5;
		T[i].y -=dx/ln*5;

		ofPoint c = B[i].getCenter();
		int pa = ((int)c.x*3 + (int)c.y*bg.width*3);
		if(c.x>=0 && c.x<bg.width && c.y>=0 && c.y<bg.height) {
			pixels[pa+0] += (int)C[i].r/2;
			pixels[pa+1] += (int)C[i].g/2;
			pixels[pa+2] += (int)C[i].b/2;
		}
		
		if(ofRandom(0.0, 100.0) > 99.5) 
			T[i] = ofPoint( ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
	}
	bg.update();
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
	ofSetColor(255);
	bg.draw(0,0);


	ofNoFill();
	
	for (int i=0; i<B.size(); i++) {
		ofSetColor(C[i]);
		ofRect(B[i]);
		ofCircle(T[i],5);
		ofDrawBitmapString(ofToString(i), B[i].x    , B[i].y-2);
		ofDrawBitmapString(ofToString(i), T[i].x - 3, T[i].y-6);
		
		ofSetColor(C[i], 40);
		ofLine(B[i].getCenter(), T[i]);
	}

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