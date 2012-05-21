#include "testApp.h"

#define W 640
#define H 480
#define S   4

//--------------------------------------------------------------
void testApp::setup(){

	grabber.setVerbose(true);
	grabber.initGrabber(W, H);

	faceFinder.setup("haarcascade_frontalface_alt_tree.xml");
	
	//faceCom.startThread();

	ofEnableAlphaBlending();
	ofBackground(0);

	labLogo.loadImage("Ailove.Lab.png");

}

void testApp::exit(){
	//faceCom.stopThread();
}

//--------------------------------------------------------------
void testApp::update(){
	
	grabber.grabFrame();
	
	faces.clear();
	
	if(grabber.isFrameNew()) {
		ofImage img(grabber.getPixelsRef());
		ofImage sml(img);
		sml.resize(W/S, H/S);
		faceFinder.findHaarObjects(sml, 16, 16);
		//tracker.trackFaces(faceFinder, img, S);
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	static float bgAlpha = 255;

	float sx = (float) grabber.width  / ofGetWidth ();
	float sy = (float) grabber.height / ofGetHeight();

	bgAlpha += faceFinder.blobs.size() ? (40.0-bgAlpha)/10.0 : (255.0-bgAlpha)/10.0;
	ofSetColor(255,255,255, bgAlpha); 
	
	grabber.draw(0,0, grabber.width/sx, grabber.height/sy);

	ofSetColor(255);
	for(int i = 0; i < faces.size(); i++) {
		ofRectangle r = faceFinder.blobs[i].boundingRect;
		faces[i].draw(r.x*S/sx, r.y*S/sy, r.width*S/sx, r.height*S/sy);
	}

	//if(detectEyes) {
	//	x=0;
	//	for(int i = 0; i < eyes.size(); i++) {
	//		eyes[i].draw(x, grabber.height+128);
	//		x +=eyes[i].width;
	//	}
	//}	
	
	ofSetColor(255);
	labLogo.draw(ofGetWidth() - labLogo.width, ofGetHeight() - labLogo.height); 
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	if (key=='s') {
		if(!faces.empty()) {
			Face f;
			f.img = faces[0];
			faceCom.addFace(f);
		}
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