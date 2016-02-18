#pragma once

#include "ofMain.h"
#include "Settings.h"
#include "InstagramDataProvider.h"
#include "InstagramView.h"

class ofApp : public ofBaseApp{

	public:
		ofApp();
	
		void setup();
		void update();
		void draw();
	
		void onMediaLoaded(MediaLoadedEventArgs & args);
	
		InstagramDataProvider _instagramDataProvider;
		InstagramView * _instagramView;
	
};

