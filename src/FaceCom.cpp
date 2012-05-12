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
	
	f.img.saveImage("processed.jpg");

	// FACECOM
	string path = "curl.exe -F media=@data\\processed.jpg \"http://api.face.com/faces/detect.xml?api_key="+string(API_KEY)+"&api_secret="+string(SEC_KEY)+"\" -o data\\processed.xml";
	system(path.c_str());
	f.xml.loadFile("processed.xml");
	processedFaces.push_back(f);

}

void FaceCom::addFace(Face& f) {
	facesQueue.push(f);
}