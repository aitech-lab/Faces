#include "testApp.h"

#define W 640
#define H 480
#define S   1

//--------------------------------------------------------------
void testApp::setup(){

	grabber.setVerbose(true);
	grabber.initGrabber(W, H);

	faceFinder.setup("haarcascade_frontalface_alt_tree.xml");
	
	faceCom.startThread();

	ofEnableAlphaBlending();
	ofBackground(0);

	labLogo.loadImage("Ailove.Lab.png");

}

void testApp::exit(){
	faceCom.stopThread();
	Sleep(1000);
}

//--------------------------------------------------------------
void testApp::update(){
	
	grabber.grabFrame();
	
	faces.clear();
	
	if(grabber.isFrameNew()) {
		ofImage img(grabber.getPixelsRef());
		ofImage sml(img);
		sml.resize(W/S, H/S);
		faceFinder.findHaarObjects(sml, 64, 64);
		
		tracker.source = &sml;

		int bs = faceFinder.blobs.size();
		vector<Face> blobs;
		for(int i=0; i<bs; i++) {
			Face        f;
			ofRectangle b = faceFinder.blobs[i].boundingRect;
			f.rect.width  = b.width;
			f.rect.height = b.width;
			f.setCenter(b.getCenter());
			blobs.push_back(f);
		}
		tracker.trackFaces(blobs);

		for(int i = 0; i < tracker.faces.size(); i++) {
			if((tracker.faces[i].trackingTimer+50) % 60 == 0) faceCom.addFace(&tracker.faces[i]);
		}

	}

	
}

//--------------------------------------------------------------
void testApp::draw(){
	static float bgAlpha = 255;

	float sx = (float) grabber.width  / ofGetWidth ();
	float sy = (float) grabber.height / ofGetHeight();

	bgAlpha += tracker.faces.size() ? (40.0-bgAlpha)/10.0 : (255.0-bgAlpha)/10.0;
	ofSetColor(255,255,255, bgAlpha); 
	
	grabber.draw(0,0, grabber.width/sx, grabber.height/sy);

	ofSetColor(255);
	for(int i = 0; i < tracker.faces.size(); i++) {
		
		ofRectangle r = tracker.faces[i].rect;

		if(tracker.faces[i].img.isAllocated()) 
			tracker.faces[i].img.draw(r.x*S/sx, r.y*S/sy, r.width*S/sx, r.height*S/sy); 
	
		ofNoFill();
		ofRect(r.x*S/sx, r.y*S/sy, r.width*S/sx, r.height*S/sy);

		ofDrawBitmapString(
			ofToString(tracker.faces[i].lostTrackingTimer)+
			string(" - ")+
			ofToString(tracker.faces[i].trackingTimer), 
			r.x*S/sx, r.y*S/sy-1);
		
		ofDrawBitmapString(
			tracker.faces[i].uid,
			r.x*S/sx, (r.y+r.height+10)*S/sy-1);

	}

	ofSetColor(255);
	labLogo.draw(ofGetWidth() - labLogo.width, ofGetHeight() - labLogo.height); 
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