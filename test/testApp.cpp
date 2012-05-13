#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	xml.loadFile("test.txt");
	img.loadImage("test.jpg");
	cout << xml.getValue("response:status","none") << "\n";
	if(xml.getValue("response:status","none") == "success") {
		if (xml.pushTag("response") && xml.pushTag("photos") && xml.pushTag("photo") && xml.pushTag("tags")) {
			int tags = xml.getNumTags("tag");
			for(int i=0; i<tags; i++) {
				tid            = xml.getValue("tag:tid"           , tid           , i);
				recognizable   = xml.getValue("tag:recognizable"  , recognizable  , i);
				threshold      = xml.getValue("tag:threshold"     , threshold     , i);
				uids		   = xml.getValue("tag:uids"          , uids		  , i);
				gid            = xml.getValue("tag:gid"           , gid           , i);
				label          = xml.getValue("tag:label"         , label         , i);
				confirmed      = xml.getValue("tag:confirmed"     , confirmed     , i);
				manual         = xml.getValue("tag:manual"        , manual        , i);
				tagger_id      = xml.getValue("tag:tagger_id"     , tagger_id     , i);
				width          = xml.getValue("tag:width"         , width         , i);
				height         = xml.getValue("tag:height"        , height        , i);
				center_x       = xml.getValue("tag:center:x"      , center_x      , i);
				center_y       = xml.getValue("tag:center:y"      , center_y      , i);
				eye_left_x     = xml.getValue("tag:eye_left:x"    , eye_left_x    , i);
				eye_left_y     = xml.getValue("tag:eye_left:y"    , eye_left_y    , i);
				eye_right_x    = xml.getValue("tag:eye_right:x"   , eye_right_x   , i);
				eye_right_y    = xml.getValue("tag:eye_right:y"   , eye_right_y   , i);
				mouth_left_x   = xml.getValue("tag:mouth_left:x"  , mouth_left_x  , i);
				mouth_left_y   = xml.getValue("tag:mouth_left:y"  , mouth_left_y  , i);
				mouth_center_x = xml.getValue("tag:mouth_center:x", mouth_center_x, i);
				mouth_center_y = xml.getValue("tag:mouth_center:y", mouth_center_y, i);
				mouth_right_x  = xml.getValue("tag:mouth_right:x" , mouth_right_x , i);
				mouth_right_y  = xml.getValue("tag:mouth_right:y" , mouth_right_y , i);
				nose_x         = xml.getValue("tag:nose:x"        , nose_x        , i);
				nose_y         = xml.getValue("tag:nose:y"        , nose_y        , i);
				ear_left_x     = xml.getValue("tag:ear_left:x"    , ear_left_x    , i);			
				ear_left_y     = xml.getValue("tag:ear_left:y"    , ear_left_y    , i);
				ear_right_x    = xml.getValue("tag:ear_right:x"   , ear_right_x   , i);			
				ear_right_y    = xml.getValue("tag:ear_right:y"   , ear_right_y   , i);
				chin_x         = xml.getValue("tag:chin:x"        , chin_x        , i);
				chin_y         = xml.getValue("tag:chin:y"        , chin_y        , i);
				yaw            = xml.getValue("tag:yaw"           , yaw           , i);
				roll           = xml.getValue("tag:roll"          , roll          , i);
				pitch          = xml.getValue("tag:pitch"         , pitch         , i);

				face_value     = xml.getValue("tag:attributes:face_value"    , face_value    , i); 
				face_conf      = xml.getValue("tag:attributes:face_conf"     , face_conf     , i); 
				gender_value   = xml.getValue("tag:attributes:gender_value"  , gender_value  , i); 
				gender_conf    = xml.getValue("tag:attributes:gender_conf"   , gender_conf   , i); 
				glasses_value  = xml.getValue("tag:attributes:glasses_value" , glasses_value , i); 
				glasses_conf   = xml.getValue("tag:attributes:glasses_conf"  , glasses_conf  , i); 
				smilling_value = xml.getValue("tag:attributes:smilling_value", smilling_value, i); 
				smilling_conf  = xml.getValue("tag:attributes:smilling_conf" , smilling_conf , i);
				
				cout << "tid           : " << tid            << "\n";
				cout << "recognizable  : " << recognizable   << "\n";
				cout << "threshold     : " << threshold      << "\n";
				cout << "uids		   : " << uids           << "\n";
				cout << "gid           : " << gid            << "\n";
				cout << "label         : " << label          << "\n";
				cout << "confirmed     : " << confirmed      << "\n";
				cout << "manual        : " << manual         << "\n";
				cout << "tagger_id     : " << tagger_id      << "\n";
				cout << "width         : " << width          << "\n";
				cout << "height        : " << height         << "\n";
				cout << "center_x      : " << center_x       << "\n";
				cout << "center_y      : " << center_y       << "\n";
				cout << "eye_left_x    : " << eye_left_x     << "\n";
				cout << "eye_left_y    : " << eye_left_y     << "\n";
				cout << "eye_right_x   : " << eye_right_x    << "\n";
				cout << "eye_right_y   : " << eye_right_y    << "\n";
				cout << "mouth_left_x  : " << mouth_left_x   << "\n";
				cout << "mouth_left_y  : " << mouth_left_y   << "\n";
				cout << "mouth_center_x: " << mouth_center_x << "\n";
				cout << "mouth_center_y: " << mouth_center_y << "\n";
				cout << "mouth_right_x : " << mouth_right_x  << "\n";
				cout << "mouth_right_y : " << mouth_right_y  << "\n";
				cout << "nose_x        : " << nose_x         << "\n";
				cout << "nose_y        : " << nose_y         << "\n";
				cout << "ear_left_x    : " << ear_left_x     << "\n";
				cout << "ear_left_y    : " << ear_left_y     << "\n";
				cout << "chin_x        : " << chin_x         << "\n";
				cout << "chin_y        : " << chin_y         << "\n";
				cout << "yaw           : " << yaw            << "\n";
				cout << "roll          : " << roll           << "\n";
				cout << "pitch         : " << pitch          << "\n";

				cout << "face_value    : " << face_value     << "\n";
				cout << "face_conf     : " << face_conf      << "\n";
				cout << "gender_value  : " << gender_value   << "\n";
				cout << "gender_conf   : " << gender_conf    << "\n";
				cout << "glasses_value : " << glasses_value  << "\n";
				cout << "glasses_conf  : " << glasses_conf   << "\n";
				cout << "smilling_value: " << smilling_value << "\n";
				cout << "smilling_conf : " << smilling_conf  << "\n";

			}
			xml.popTag();
		}
	}
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	img.draw(0,0);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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