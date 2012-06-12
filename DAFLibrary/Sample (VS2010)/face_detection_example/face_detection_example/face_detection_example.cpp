/*

	********************************************************************************
	Discrete Area Filters Face Detection library, copyright to Jacek Naruniec, 2012.
	********************************************************************************
	
	You can use this library for non-commercial use. If you are interested in commercial use, please contact the author of the library (Jacek Naruniec, email: jacek.naruniec@gmail.com")
	
	When publishing results obtained using this library or any of it's parts, user is obligated to cite the following paper:
	
	J. Naruniec, W. Skarbek:  "Face Detection by Discrete Gabor Jets and Reference Graph of Fiducial Points" in Lecture Notes in Computer Science, 4481 LNAI, pp. 187-194, 2007

	Above article presents some basics of the algorithm (features obtained using area filters, modified Linear Discriminant Analysis), although full description of the algorithm used here will be published soon. Then the given citation will change. 

	Authors contact information:
	Jacek Naruniec
	jacek.naruniec@gmail.com

**************************************************************************
*/


#include "stdafx.h"
#include "facedetector.h"
#include "PGM.h"
//#include "getopt.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Properties prop;
	int w, h;
	unsigned char *grayscale_image;
	const char out_name[] = "out.pgm";

	FaceDetector *fd;
	
	const char *face_features[4] = {"left eye", "right eye", "nose", "mouth"};


	if (argc<4)
	{
		printf("Syntax:\nface_detector_example [data_path] [PGM filename] [PGM outfilename]\n");
		printf("PGM outfilename is optional, out.pgm default");
		system("pause");
		exit(1);
	}

	// Image must be in a PGM format, created for example in IrfanView - no compression, binary encoding
	// grayscale_image is a pointer to the memory of size w*h - each byte correspond to one pixel grayscale value
	grayscale_image = ReadPGM(argv[2], w, h, false);

	if (grayscale_image==NULL)
	{
		printf("\nCouldn't load specified file... \n");
		exit(1);
	}

	try{
		// load the face detector, argv[1] containes path to the classifiers data (data\)
		fd = new FaceDetector(argv[1],  &prop, VERSION_1, false);
	}
	catch(...)
	{
		printf("\nException on loading detector! Is the data path correct?\n");
		delete []grayscale_image;
		exit(0);
	}

	// detect the faces
	fd->DetectFaces(grayscale_image, w, h);
	
	printf("\nDetected %d faces: ", fd->detected_faces.size());

	// print results of the detection
	for (size_t faces=0; faces<fd->detected_faces.size(); faces++)
	{
		printf("\nFace %d:\nFace parts - ", faces+1);
		for (int ff=0; ff<N_FACIAL_FEATURES; ff++)
		{
			printf("(%s): (%d, %d); ", face_features[ff], fd->detected_faces[faces].facial_features[ff].x,
				fd->detected_faces[faces].facial_features[ff].y);
		}
		printf("\nFiducial points: \n");
		for (int fp=0; fp<N_POINTS; fp++)
		{
			printf("(%d): (%d %d); ", fp, fd->detected_faces[faces].face_points[fp].x,
				fd->detected_faces[faces].face_points[fp].y);
		}
	}
	fd->DrawDetectionResultsOnImage(grayscale_image);

	printf("\n\nWriting results to ");
	if (argc==4)
	{
		WritePGM(argv[3], w, h, grayscale_image);
	} else
		WritePGM(out_name, w, h, grayscale_image);

	delete fd;
	delete []grayscale_image;
	return 0;
}

