<<<<<<< HEAD:face.com/src/Face.cpp
#include "Face.h"

Face::Face() {

	velocity = ofPoint(0, 0);
	lostTrackingTimer = LOST_COUNTER;
	linkEstablished = false;
	
	url =
	tid = label  = 
	recognizable =   
	threshold    =  
	uids = gid   =        
	confirmed    =  
	manual       = 
	tagger_id    = ""; 
	
	width          = height         =
	center_x       = center_y       =
	eye_left_x     = eye_left_y     =
	eye_right_x    = eye_right_y    =
	mouth_left_x   = mouth_left_y   =
	mouth_center_x = mouth_center_y =
	mouth_right_x  = mouth_right_y  =
	nose_x         = nose_y         =
	ear_left_x     = ear_left_y     =
	ear_right_x    = ear_right_y    =
	chin_x         = chin_y         =        
	
	yaw = roll = pitch              = -1.0;          
	
	glasses_value = smilling_value = gender_value = face_value = "";
	glasses_conf  = smilling_conf  = gender_conf  = face_conf  = -1.0;
	  
}


Face::~Face() {

}

void Face::setCenter(const ofPoint& c) {
	ofPoint co = center;
	center = c;
	velocity = c - co;
	rect.setFromCenter(center, rect.width, rect.height);
	lostTrackingTimer = LOST_COUNTER;
}


void Face::parseXML(ofxXmlSettings xml) {
	
	cout << xml.getValue("response:status","none") << "\n";
	if(xml.getValue("response:status","none") == "success") {
		
		url = xml.getValue("response:photos:photo:url",  url);
		
		if (xml.pushTag("response") && xml.pushTag("photos") && xml.pushTag("photo") && xml.pushTag("tags")) {
			tid            = xml.getValue("tag:tid"           , tid           );
			recognizable   = xml.getValue("tag:recognizable"  , recognizable  );
			threshold      = xml.getValue("tag:threshold"     , threshold     );
			uids		   = xml.getValue("tag:uids"          , uids		  );
			gid            = xml.getValue("tag:gid"           , gid           );
			label          = xml.getValue("tag:label"         , label         );
			confirmed      = xml.getValue("tag:confirmed"     , confirmed     );
			manual         = xml.getValue("tag:manual"        , manual        );
			tagger_id      = xml.getValue("tag:tagger_id"     , tagger_id     );
			width          = xml.getValue("tag:width"         , width         );
			height         = xml.getValue("tag:height"        , height        );
			center_x       = xml.getValue("tag:center:x"      , center_x      );
			center_y       = xml.getValue("tag:center:y"      , center_y      );
			eye_left_x     = xml.getValue("tag:eye_left:x"    , eye_left_x    );
			eye_left_y     = xml.getValue("tag:eye_left:y"    , eye_left_y    );
			eye_right_x    = xml.getValue("tag:eye_right:x"   , eye_right_x   );
			eye_right_y    = xml.getValue("tag:eye_right:y"   , eye_right_y   );
			mouth_left_x   = xml.getValue("tag:mouth_left:x"  , mouth_left_x  );
			mouth_left_y   = xml.getValue("tag:mouth_left:y"  , mouth_left_y  );
			mouth_center_x = xml.getValue("tag:mouth_center:x", mouth_center_x);
			mouth_center_y = xml.getValue("tag:mouth_center:y", mouth_center_y);
			mouth_right_x  = xml.getValue("tag:mouth_right:x" , mouth_right_x );
			mouth_right_y  = xml.getValue("tag:mouth_right:y" , mouth_right_y );
			nose_x         = xml.getValue("tag:nose:x"        , nose_x        );
			nose_y         = xml.getValue("tag:nose:y"        , nose_y        );
			ear_left_x     = xml.getValue("tag:ear_left:x"    , ear_left_x    );			
			ear_left_y     = xml.getValue("tag:ear_left:y"    , ear_left_y    );
			ear_right_x    = xml.getValue("tag:ear_right:x"   , ear_right_x   );			
			ear_right_y    = xml.getValue("tag:ear_right:y"   , ear_right_y   );
			chin_x         = xml.getValue("tag:chin:x"        , chin_x        );
			chin_y         = xml.getValue("tag:chin:y"        , chin_y        );
			yaw            = xml.getValue("tag:yaw"           , yaw           );
			roll           = xml.getValue("tag:roll"          , roll          );
			pitch          = xml.getValue("tag:pitch"         , pitch         );

			face_value     = xml.getValue("tag:attributes:face_value"    , face_value    ); 
			face_conf      = xml.getValue("tag:attributes:face_conf"     , face_conf     ); 
			gender_value   = xml.getValue("tag:attributes:gender_value"  , gender_value  ); 
			gender_conf    = xml.getValue("tag:attributes:gender_conf"   , gender_conf   ); 
			glasses_value  = xml.getValue("tag:attributes:glasses_value" , glasses_value ); 
			glasses_conf   = xml.getValue("tag:attributes:glasses_conf"  , glasses_conf  ); 
			smilling_value = xml.getValue("tag:attributes:smilling_value", smilling_value); 
			smilling_conf  = xml.getValue("tag:attributes:smilling_conf" , smilling_conf );
				
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

			xml.popTag(); xml.popTag(); xml.popTag(); xml.popTag();
		}
	}
}
=======
#include "Face.h"

Face::Face() {

	velocity          = ofPoint(0, 0);
	lostTrackingTimer = LOST_COUNTER;
	trackingTimer     = 0;
	linkEstablished   = false;
	  
}


Face::~Face() {

}

void Face::setCenter(const ofPoint& c) {
	ofPoint co = center;
	center = c;
	velocity = c - co;
	rect.setFromCenter(center, rect.width, rect.height);
	lostTrackingTimer = LOST_COUNTER;
}


>>>>>>> deatached:src/Face.cpp
