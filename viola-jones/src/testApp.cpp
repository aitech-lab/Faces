#include "testApp.h"

#define W 800
#define H 600
#define S   2

//--------------------------------------------------------------
void testApp::setup(){

	grabber.setVerbose(true);
	grabber.initGrabber(W, H);

	faceFinder.setup("haarcascade_frontalface_alt_tree.xml");

	ofEnableAlphaBlending();
	ofBackground(0);

	labLogo.loadImage("Ailove.Lab.png");

}

void testApp::exit(){
}

//--------------------------------------------------------------
void testApp::update(){
	
	grabber.grabFrame();
	
	blobs.clear();
	
	if(grabber.isFrameNew()) {
		ofImage img(grabber.getPixelsRef());
		faceFinder.findHaarObjects(img, 128, 128);
		int bs = faceFinder.blobs.size();
		for(int i=0; i<bs; i++) {
			blobs.push_back(faceFinder.blobs[i].boundingRect);
		}
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){
	static float bgAlpha = 255;

	float sx = (float) grabber.width  / ofGetWidth ();
	float sy = (float) grabber.height / ofGetHeight();
	
	grabber.draw(0,0); //, grabber.width/sx, grabber.height/sy);
	ofNoFill();
	ofSetColor(255);
	for(int i = 0; i < blobs.size(); i++) {
		ofRect(blobs[i]);
	}

	ofSetColor(255);
	labLogo.draw(ofGetWidth() - labLogo.width, ofGetHeight() - labLogo.height); 
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	if (key=='s') {

	}

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