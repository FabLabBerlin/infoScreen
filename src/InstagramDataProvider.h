#pragma once

#include "ofMain.h"
#include "ofxInstagram.h"
#include "Settings.h"

struct InstagramPostData{
	string id;
	string type;
	string videoUrl;
	string imageUrl;
	string username;
	string profilePictureUrl;
	string caption;
};

struct InstagramDataLoadedEventArgs{
	vector <InstagramPostData> posts;
};

class InstagramDataProvider : public ofThread{

	public:
		InstagramDataProvider();
	
		void setup();
		void threadedFunction();
	
		ofEvent <InstagramDataLoadedEventArgs> dataLoadedEvent;

	private:
		ofxInstagram _instagram;
	
		float _lastUpdateTime;
		float _updateIntervalSeconds;
	
		// A copy of args to compare with
		InstagramDataLoadedEventArgs _args;
};