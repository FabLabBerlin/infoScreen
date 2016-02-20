#pragma once

#include "ofMain.h"
#include "InstagramDataProvider.h"
#include "Settings.h"

class InstagramView{

	public:
	
		InstagramView();
		~InstagramView();
	
		void setup();
		void load(InstagramPostData args);
		void unload();
		void update();
		void draw();
		void urlResponse(ofHttpResponse & response);
	
		bool getIsLoaded(){ return _isLoaded; }
		bool getIsLoading(){ return _isLoading; }
	
	private:
	
		ofImage _image;
		ofImage _profileImage;
		ofVideoPlayer _video;
	
		float _margin;
		float _avatarWidth;
		float _avatarHeight;
	
		void loadImage();
		void loadVideo();
		void loadProfileImage();
	
		void initImage(string fileName);
		void initVideo(string fileName);
		void initProfileImage(string fileName);
	
		string getWordWrapString(string inputString, int charsPerLine = 30);
	
		InstagramPostData _args;
	
		ofTrueTypeFont	_fontMdRegular;
		ofTrueTypeFont  _fontMdBold;
		ofTrueTypeFont	_fontLgRegular;
	
		bool _isLoaded;
		bool _isLoading;
	
};