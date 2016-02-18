#pragma once

#include "ofMain.h"

class InstagramView{

	public:
	
		InstagramView(string type, string name, ofBuffer * data,
			string username, string caption, string profilePicture);
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
	
		string _username;
		string _caption;
		string _profilePicture;
	
		ofTrueTypeFont	_fontMdRegular;
		ofTrueTypeFont  _fontMdBold;
		ofTrueTypeFont	_fontLgRegular;
	
};