#pragma once

#include "ofMain.h"

class Settings {
	public:
		static Settings * instance();
	
		void setInstagramToken(string t);
		string getInstagramToken();
	
		void setCache(bool c);
		bool getCache();
	
		void setChangeIntervalSeconds(float s);
		float getChangeIntervalSeconds();
	
	private:
		static Settings * _instance;
	
		Settings();

		string _instagramToken;
		bool _cache;
		float _changeIntervalSeconds;
};
