#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	grabber.setVerbose(true);
	grabber.initGrabber(320, 240);

	faceFinder.setup("haarcascade_frontalface_alt_tree.xml");
	eyesFinder.setup("haarcascade_eye.xml");
}

//--------------------------------------------------------------
void testApp::update(){
	
	grabber.grabFrame();
	ofImage img(grabber.getPixelsRef());
	
	faces.clear();
	eyes.clear();

	faceFinder.findHaarObjects(img, 32, 32);
	
	for(int i = 0; i < faceFinder.blobs.size(); i++) {
		ofRectangle r = faceFinder.blobs[i].boundingRect;
		ofImage face;
		face.cropFrom(img, r.x, r.y, r.width, r.height);
		face.resize(128,128);
		faces.push_back(face);

		eyesFinder.findHaarObjects(face, 16, 8);
		for(int j = 0; j < eyesFinder.blobs.size(); j++) {
			ofRectangle r = eyesFinder.blobs[j].boundingRect;
			ofImage eye;
			eye.cropFrom(face, r.x, r.y, r.width, r.height);
			eye.resize(32,32);
			eyes.push_back(eye);
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	
	grabber.draw(0,0);
	ofNoFill();
	for(int i = 0; i < faceFinder.blobs.size(); i++) {
		ofRectangle cur = faceFinder.blobs[i].boundingRect;
		ofRect(cur.x, cur.y, cur.width, cur.height);
	}

	int x=0;
	for(int i = 0; i < faces.size(); i++) {
		faces[i].draw(x, grabber.height);
		x +=faces[i].width;
	}
	
	x=0;
	for(int i = 0; i < eyes.size(); i++) {
		eyes[i].draw(x, grabber.height+128);
		x +=eyes[i].width;
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