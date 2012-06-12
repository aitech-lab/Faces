#pragma once

#include <windows.h>

class FaceDetector;
class FacialFeatureDetector;

struct FDThreadParameters
{
	FaceDetector *fd;
	int parameter;
	HANDLE threadReadyEvent, requestDetectionEvent;
	HANDLE terminateAllEvent;

	FacialFeatureDetector **features_detector;

	int *integral_image;
	unsigned char *edge_image;
	unsigned char* grayscale_image;

	int minx, miny, maxx, maxy, minscale, maxscale;

	FDThreadParameters() { fd = NULL; parameter = -1; }
	FDThreadParameters(FaceDetector *_fd, int _parameter, FacialFeatureDetector **ff)
	{  fd = _fd;  parameter = _parameter; features_detector = ff; }

	void set(FaceDetector *_fd, int _parameter, FacialFeatureDetector **ff)
	{  fd = _fd;  parameter = _parameter; features_detector = ff; }

};

DWORD WINAPI DetectFacialFeature(void* data);

