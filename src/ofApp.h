#pragma once

#include "ofMain.h"
#include "ofxInstagram.h"
#include "Settings.h"

class ofApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();
		
		void urlResponse(ofHttpResponse & response);

		ofxInstagram instagram;
		ofVideoPlayer currentVideo;
		ofURLFileLoader urlLoader;
	
		string currentVideoUrl;
		string currentVideoFileName;
	
		float lastInstagramUpdate;
		float instagramUpdateIntervalSeconds;
};

