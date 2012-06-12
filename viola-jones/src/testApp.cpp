#include "testApp.h"

#define W 640
#define H 480
#define S   2

//--------------------------------------------------------------
void testApp::setup(){

	ofSetWindowTitle("Ailove-ViolaJones");
	
	grabber.setVerbose(true);
	grabber.initGrabber(W, H);

	faceFinder    .setup("haar-cascades/eugeny/haarcascade_frontalface_default.xml");
	eyeFinder     .setup("haar-cascades/eugeny/haarcascade_eye.xml");
	leftEyeFinder .setup("haar-cascades/eugeny/haarcascade_mcs_lefteye.xml");
	rightEyeFinder.setup("haar-cascades/eugeny/haarcascade_mcs_righteye.xml");
	mouthFinder   .setup("haar-cascades/eugeny/haarcascade_mcs_mouth.xml");

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
		faceFinder.findHaarObjects(img, 100, 100);
		int fc = faceFinder.blobs.size();

		for(int f=0; f<fc; f++) {
			ofRectangle& fr = faceFinder.blobs[f].boundingRect;
			blobs.push_back(fr);

			ofImage face;
			face.cropFrom(img, fr.x, fr.y, fr.width, fr.height);
			
			int ec;
			eyeFinder.findHaarObjects(face, 40, 20);
			ec = eyeFinder.blobs.size();
			for(int e=0; e<ec; e++) {
				ofRectangle& er = eyeFinder.blobs[e].boundingRect;
				er.x += fr.x;
				er.y += fr.y;
				blobs.push_back(er);
			}

			// leftEyeFinder.findHaarObjects(face, 20, 10);
			// ec = leftEyeFinder.blobs.size();
			// for(int e=0; e<ec; e++) {
			// 	ofRectangle& er = leftEyeFinder.blobs[e].boundingRect;
			// 	er.x += fr.x;
			// 	er.y += fr.y;
			// 	blobs.push_back(er);
			// }
			// 
			// rightEyeFinder.findHaarObjects(face, 20, 10);
			// ec = rightEyeFinder.blobs.size();
			// for(int e=0; e<ec; e++) {
			// 	ofRectangle& er = rightEyeFinder.blobs[e].boundingRect;
			// 	er.x += fr.x;
			// 	er.y += fr.y;
			// 	blobs.push_back(er);
			// }

			mouthFinder.findHaarObjects(face, 40, 20);
			int mc = mouthFinder.blobs.size();
			for(int m=0; m<mc; m++) {
				ofRectangle& mr = mouthFinder.blobs[m].boundingRect;
				mr.x += fr.x;
				mr.y += fr.y;
				blobs.push_back(mr);
			}
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