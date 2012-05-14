#pragma once
#include "ofMain.h"
#include "ofxXmlSettings.h"

class Face {
public:
	Face();
	~Face();

	ofImage img;
	void parseXML(ofxXmlSettings xml);

	// face.com info
	string url            ;

	string tid            ;
	string recognizable   ;
	string threshold      ;
	string uids			  ;
	string gid            ;
	string label          ;
	string confirmed      ;
	string manual         ;
	string tagger_id      ;
	
	double width          ;
	double height         ;
	double center_x       ;
	double center_y       ;
	double eye_left_x     ;
	double eye_left_y     ;
	double eye_right_x    ;
	double eye_right_y    ;
	double mouth_left_x   ;
	double mouth_left_y   ;
	double mouth_center_x ;
	double mouth_center_y ;
	double mouth_right_x  ;
	double mouth_right_y  ;
	double nose_x         ;
	double nose_y         ;
	double ear_left_x     ;
	double ear_left_y     ;
	double ear_right_x    ;
	double ear_right_y    ;
	double chin_x         ;
	double chin_y         ;
	double yaw            ;
	double roll           ;
	double pitch          ;
	
	string face_value     ;
	double face_conf      ;
	string gender_value   ;
	double gender_conf    ;
	string glasses_value  ;
	double glasses_conf   ;
	string smilling_value ;
	double smilling_conf  ;

};

