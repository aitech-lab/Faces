#pragma once

// algorithm informations
#define N_POINTS				15
#define N_FACIAL_FEATURES		4

// face detection defines
#define COLOR_THRESHOLD			5
#define INVALID_COLOR			-999
#define REJECTED_FACE			-1000

// face normalization constans
#define L_EYE_CENTER_X			15
#define L_EYE_CENTER_X_SQR		225
#define R_EYE_CENTER_X			30
#define EYES_ROW				23
#define BETWEEN_EYES_DISTANCE	15
#define BETWEEN_EYES_DISTANCE3	45
#define SIZE_X					46
#define SIZE_Y					56

#define COLOR_HISTOGRAM_SIZE	16

#define NORM_IMAGE_W			46
#define NORM_IMAGE_H			56

#define NORM_LE_X				15				
#define NORM_LE_Y				23
#define NORM_RE_X				30



/* detection buffer size needed in point detector methods.
If your graphic memory doesnt have enough memory, lower the below value */
//#define DETECTION_BUFFER_SIZE	4194304
//#define DETECTION_BUFFER_SIZE 1048576
//#define DETECTION_BUFFER_SIZE 1048576
#define DETECTION_BUFFER_SIZE 524288
// graph matching constants
#define MAX_GRAPH_SCALE_DIFFERENCE		0.6f
#define MAX_FACE_GRAPH_SCALE_DIFFERENCE 2.0f
#define WILDCARD_COST					1
#define ANGLE_WILDCARD_COST				1
// math defines
#define M_PI				3.14159265
#define M_PI_FLOAT			3.14159265f
#define M_PI2				1.57079632
#define M_PI2_FLOAT			1.57079632f
#define M_PI32_FLOAT		4.71238897f
#define M_2PI_FLOAT			6.2831853f


// point detection defines
#define MAX_MERGE_DISTANCE  10
#define MIN_RELATIVE_WEIGHT 0.1
#define MAX_POINTS 100000

#define DETECTION_MASK_SIZE	4
#define DETECTION_MASK_SIZE_INV 0.25f
#define DETECTION_MASK_SHIFT 2

// facial features detection methods
#define GENERAL_METHOD		100		// method same as the face detection from facial features
#define PARTICULAR_METHOD	200		// method particular for the facial features detection

#define MAX_FF_SCALE_DISTANCE		2
#define MAX_FF_COORD_DISTANCE		15


// size of the ring, useful for DGJ
#define FULL				0
#define LEFT_HALF			1
#define RIGHT_HALF			2

//-------
#define NO					0
#define YES					1
#define CONTINUE			2
//-------

// errors and exceptions
#define NEGATIVES_PATH_ERROR 10

#define NO_FILE_EXCEPTION	200
#define CREATE_THREAD_EXCEPTION	100

// facial features detector defines
#define MAX_FACIAL_FEATURES 10000

#define ERROR_EXCEPTION 300

#define LEFT_EYE	0
#define RIGHT_EYE	1
#define NOSE		2
#define MOUTH		3

#define NONE		-1


// debug console function
#ifndef NDEBUG
  #define DPRINT(text)  OutputDebugStringA(text "\n")
#else // #ifdef NDEBUG
  #define DPRINT(text)  ((void)0)
#endif

