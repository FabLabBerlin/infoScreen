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
		void onInstagramDataLoaded(InstagramDataLoadedEventArgs & args);
	
	private:
	
		InstagramDataProvider _instagramDataProvider;
		InstagramView * _instagramView;
		InstagramView * _nextInstagramView;
	
		int _instagramMaxItems;
		int _instagramCurrentItem;
	
		float _changeIntervalSeconds;
		float _lastChangeTime;
	
		vector <InstagramPostData> _instagramPosts;
};

