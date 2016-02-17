#pragma once

#include "ofMain.h"

class Settings {
	public:
		static Settings * instance();
	
		void setInstagramToken(string t);
		string getInstagramToken();
	
	private:
		static Settings * _instance;
	
		Settings();

		string _instagramToken;
};
