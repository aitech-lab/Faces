/*
	FaceDetector declarations

	This is a part of the Discrete Area Filters Face Detection library, copyright to Jacek Naruniec, 2012.
	You can use this library for non-commercial use. If you are interested in commercial use, please contact
	the author of the library (Jacek Naruniec, email: jacek.naruniec@gmail.com")
	
	When publishing results obtained using this library or any of it's parts, user is obligated to cite the following paper:
	
	J. Naruniec, W. Skarbek:  "Face Detection by Discrete Gabor Jets and Reference Graph of Fiducial Points"
	in Lecture Notes in Computer Science, 4481 LNAI, pp. 187-194, 2007

	Above article presents some basics of the algorithm (features obtained using area filters, modified Linear 
	Discriminant Analysis), although full description of the algorithm used here will be published soon. 
	Then the given citation will change. 

	Authors contact information:
	Jacek Naruniec
	jacek.naruniec@gmail.com
*/

#pragma once

#include "FaceDetectorThreads.h"
#include "Properties.h"
#include "structs.h"
#include "FaceGraph.h"
#include <vector>

#define 	EVENT_CREATION_FAULT	-1
#define		EXC_NO_FACE_GRAPH		-2

#define		DETECTOR_NOT_INITIALIZED	-1000
#define		THREADS_CREATION_ERROR		-2000

#define		VERSION_1		1	/* faster, less falsely accepted faces, more falsely rejected faces */
#define		VERSION_2		2	/* slower, more falsely accepted faces, less falsely rejected faces */

using namespace std;

class FacialFeatureDetector;

class FaceDetector
{
public:
/* results of the detection */
	vector <face> detected_faces;

/* it is set to true when the detector has been succesfully initialized */
	bool detector_initialized;

/* total faces detected */
	int detectionCounter;

/* detector mode, can be modified anytime */
	int mode;

/* data path, don't change when the object is created */
	char workpath[1024];

/* Constructor. 
	workpath : is a directory, where the data files are placed. It have to end with '\\' sign
	prop : pointer to the Properties, where informations such as starting scale, number of scales and sale multiplayer is held
	leaveOneProcessorFree : applicable when working on a multi core system; setting this flag to true makes the algorithm to perform 
							processing on all of the cores, excluding the last one
*/
	FaceDetector(char *workpath, Properties *prop, int mode = VERSION_1, bool leaveOneProcessorFree = false);

/*
	Perform the face detection.
	image : pointer to the grayscale image. It has to point on continous w*h bytes of memory, where the image is placed in rows
	w, h : width and the height of the given image
*/
	int DetectFaces(unsigned char *image, int w, int h);

	int GetWidth() {return im_width; }
	int GetHeight() {return im_height; }

/* Returns pointer to the current properties of the detector. Properties shouldn't be changed, when the detector
	is constructed. Rather delete the detector and create a new one to set new properties set. */
	Properties* GetProp() { return prop; }

/* Draws the detection results (visualisation of the detected_faces vector) on the specified image. Image must be the same
size, that the image taken as an input for DetectFaces. One byte per pixel grayscale image representation. */
	void DrawDetectionResultsOnImage(unsigned char *image);


/* Destructor. */
	~FaceDetector();


private:

	/* Detector properties, can't be changed after the detector is created */
	Properties *prop;

	bool leaveOneProcessorFree;

    /* Internal detector functions. */
	void RemoveOverlappedFaces();
	void InitImageVariables(int _w, int _h);
	void ReduceEdgeImage(int factor);
	void FreeImageMemory();
	int CreateFFDetectionThreads();


	void TerminateFFDetectionThreads();
	bool cpuSetImageWithEdges(unsigned char *image);	// when the w and h is predefined

	void ResetAllEvents();
	void ZeroVariables();

	int im_width, im_height;
	int GetNumberOfCPUs();

	FDThreadParameters *params[N_FACIAL_FEATURES];  // used for ff detection threads

	HANDLE FFDetectionThreads[N_FACIAL_FEATURES];
	DWORD FFThreadsID[N_FACIAL_FEATURES];
	
	HANDLE requestDetectionEvent[N_FACIAL_FEATURES], threadReadyEvent[N_FACIAL_FEATURES];
	HANDLE terminateAllEvent;

	void RequestThreadsDetection();
	void WaitForThreadsToFinish();
	void FindBestFittingGraphs(int minNodesForGraph);

	bool detectionThreadsCreated;

	void FreeMemory();
	void PutResultsToContainer();

	Graph faceGraph;

	void fdError(int errn);

	/* Pointers to the images used by the detector. These pointers are set automatically during the detection. */
	int *integral_image;
	unsigned char *edge_image;
	unsigned char* grayscale_image;


	/* Face parts detectors. Each detector is handled in a separate CPU thread. */
	FacialFeatureDetector *features_detectors[N_FACIAL_FEATURES];
};