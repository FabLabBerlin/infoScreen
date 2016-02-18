#pragma once

#include "ofMain.h"
#include "ofxInstagram.h"
#include "Settings.h"

struct MediaLoadedEventArgs{
	string type;
	string name;
	ofBuffer data;
	string username;
	string caption;
	string profilePicture;
};

class InstagramDataProvider : public ofThread{

	public:
		InstagramDataProvider();
	
		void setup();
		void threadedFunction();
		void urlResponse(ofHttpResponse & response);
	
		ofEvent <MediaLoadedEventArgs> mediaLoadedEvent;

	private:
		ofxInstagram _instagram;
		ofURLFileLoader _urlLoader;
	
		float _lastUpdateTime;
		float _updateIntervalSeconds;
		bool _isMediaLoading;
	
		string _currentMediaType;
		string _currentVideoUrl;
		string _currentVideoFileName;
		string _currentImageUrl;
		string _currentLoadingMediaType;

};