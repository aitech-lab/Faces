#include "FaceCom.h"
#include "api-keys.h"


FaceCom::FaceCom(void) {

}


FaceCom::~FaceCom(void)
{
}


void FaceCom::threadedFunction() {

	while (isThreadRunning()) {
		if(!facesQueue.empty()) {
			callFaceCom();
		} else {
			sleep(100);
		}	
	}

}

void FaceCom::callFaceCom() {
	Face f = facesQueue.front();
	facesQueue.pop();

	string fname = ofGetTimestampString();
	string iname = string("photos\\")+fname+string(".jpg");
	string xname = string("photos\\")+fname+string(".xml");

	f.img.saveImage(iname);

	// FACECOM
	string path = "curl.exe -F media=@data\\"+iname+" \"http://api.face.com/faces/detect.xml?api_key="+string(API_KEY)+"&api_secret="+string(SEC_KEY)+"\" -o data\\"+xname;
	system(path.c_str());
	ofxXmlSettings xml(xname);
	f.parseXML(xml);
	processedFaces.push_back(f);

}

void FaceCom::addFace(Face& f) {
	facesQueue.push(f);
}