#pragma once

#include "ofMain.h"
#include "InstagramDataProvider.h"
#include <regex>

class InstagramView{

	public:
	
		InstagramView(InstagramPostData args);
		~InstagramView();
	
		void setup();
		void update();
		void draw();
		void urlResponse(ofHttpResponse & response);
	
		char * word_wrap (char * buffer, char * string, int line_width);
	
	private:
	
		ofImage * _image;
		ofImage * _profileImage;
		ofVideoPlayer * _video;
	
		float _margin;
		float _avatarWidth;
		float _avatarHeight;
	
		void loadImage();
		void loadVideo();
		void loadProfileImage();
	
		InstagramPostData _args;
	
		ofTrueTypeFont	_fontMdRegular;
		ofTrueTypeFont  _fontMdBold;
		ofTrueTypeFont	_fontLgRegular;
	
};