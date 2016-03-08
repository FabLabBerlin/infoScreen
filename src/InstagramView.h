#pragma once

#include "ofMain.h"
#include "InstagramDataProvider.h"
#include "Settings.h"

#ifdef TARGET_RASPBERRY_PI
	#include "ofxOMXPlayer.h"
#endif

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
	
		#ifdef TARGET_RASPBERRY_PI
			ofxOMXPlayer _video;
		#else
			ofVideoPlayer _video;
		#endif
	
		float _margin;
		float _avatarWidth;
		float _avatarHeight;
	
		void loadImage();
		void loadVideo();
		void loadProfileImage();
	
		void initImage(string fileName);
		void initVideo(string fileName);
		void initProfileImage(string fileName);
	
		string splitInLines(string source, size_t width, string whitespace = " \t\r\n");
	
		InstagramPostData _args;
	
		ofTrueTypeFont	_fontMdRegular;
		ofTrueTypeFont  _fontMdBold;
		ofTrueTypeFont	_fontLgRegular;
	
		bool _isLoaded;
		bool _isLoading;
	
};