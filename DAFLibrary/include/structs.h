#pragma once

#ifndef STRUCTS
#define STRUCTS

#include "consts.h"

#include <math.h>
#include <stdio.h>



struct simpleRECT
{
	int left;
	int right;
	int top;
	int bottom;
};

struct simplePOINT
{
	int x, y;
};

struct RECT2
{
	int left_top;
	int right_top;
	int left_bottom;
	int right_bottom;
};

class Point
{
public:
	int x;
	int y;
	bool set;
	int index;
	float s;

	Point();
};

class ReferenceDistances
{
public:
	int ref_point1;
	int ref_point2;

	int n_distances;
	float *distances;

	int *points1;
	int *points2;
	float *max_differences;
	float *min_dist, *max_dist;

	float max_threshold;

	ReferenceDistances();
	void CreateTables();
	void ClearTables();
	~ReferenceDistances();
};

class face
{
public:
	simplePOINT face_points[N_POINTS];		// if point wasn't found, (x, y) = (0, 0)
	simplePOINT facial_features[N_FACIAL_FEATURES];

	void clear();
};

class feature
{
public:
	int X, Y;	// anchoring point
	float S;	// scale
	int Sn;		// scale index
	bool F;		// flag (no specified usage)
	int weight; // weight of the ff truncated to int
	int type;   // type of the point

	void operator+=(feature &f);
	void Set(int _x, int _y, float _S, int _Sn=-1, bool _F=true, int _weight=1);
	feature& NormalizeWeight();
	feature();

};

class face_part
{
public:
	feature *features;
	int n_points;

	void Clear();
	face_part();
	simpleRECT getBounds();

	feature CalculateCenter();

	feature CalculateCenter(float scale_factor);
	void CreateTables(int _n_points);
	void ReadFromFile(FILE *f);
	void WriteToFile(FILE *f);
	face_part& operator=(face_part &fp);
	~face_part();
};

class Extractor
{
public:
	int type;
	int n;
	int R;
	int orientation;
	bool mirrored;

	float fScale;
	int nScale;

	simpleRECT *rects;

	void Copy(Extractor &ex);

	Extractor();

	void DestroyRects();
	~Extractor();
	
	void Set(int _type, int _n, int _R, int _orientation);
	void Write(FILE *f);
	void Load(FILE *f);
};

class Mirrors
{
public:
	int mirrors[N_POINTS];

	Mirrors();

	void Set();
};

struct ClassifierWindowBounds
{
	int minx;
	int miny;
	int maxx;
	int maxy;
};

// bounds from one point (p1) to another (p2)
struct Bound
{
	simpleRECT bound_rect;
	int p1;
	int p2;
};

#endif