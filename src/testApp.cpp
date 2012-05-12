#include "testApp.h"

#define W 640
#define H 480
#define S   4

//--------------------------------------------------------------
void testApp::setup(){
	grabber.setVerbose(true);
	grabber.initGrabber(W, H);

	detectEyes = false;

	faceFinder.setup("haarcascade_frontalface_alt_tree.xml");
	eyesFinder.setup("haarcascade_eye.xml");

	faceCom.startThread();
}

void testApp::exit(){
	faceCom.stopThread();
}

//--------------------------------------------------------------
void testApp::update(){
	
	grabber.grabFrame();
	
	if(grabber.isFrameNew()) {
		ofImage img(grabber.getPixelsRef());
		ofImage sml(img);
		sml.resize(W/S, H/S);
		faceFinder.findHaarObjects(sml, 16, 16);
		if (faceFinder.blobs.size()) {
			faces.clear();
			eyes.clear();
			for(int i = 0; i < faceFinder.blobs.size(); i++) {
				ofRectangle r = faceFinder.blobs[i].boundingRect;
				ofImage face;
				face.cropFrom(img, r.x*S, r.y*S, r.width*S, r.height*S);
				face.resize(128, 128);
				faces.push_back(face);
				
				if (detectEyes) {
					eyesFinder.findHaarObjects(face, 16, 8);
					for(int j = 0; j < eyesFinder.blobs.size(); j++) {
						ofRectangle r = eyesFinder.blobs[j].boundingRect;
						ofImage eye;
						eye.cropFrom(face, r.x, r.y, r.width, r.height);
						eye.resize(64,64);
						eyes.push_back(eye);
					}
				}
			}
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	
	grabber.draw(0,0);
	ofNoFill();
	for(int i = 0; i < faceFinder.blobs.size(); i++) {
		ofRectangle cur = faceFinder.blobs[i].boundingRect;
		ofRect(cur.x*S, cur.y*S, cur.width*S, cur.height*S);
	}

	int x=0;
	for(int i = 0; i < faces.size(); i++) {
		faces[i].draw(x, grabber.height);
		x +=faces[i].width;
	}

	if(detectEyes) {
		x=0;
		for(int i = 0; i < eyes.size(); i++) {
			eyes[i].draw(x, grabber.height+128);
			x +=eyes[i].width;
		}
	}	

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