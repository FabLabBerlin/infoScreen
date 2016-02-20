#include "Settings.h"

Settings * Settings::_instance = 0;

Settings * Settings::instance(){
	if(_instance == 0){
		_instance = new Settings();
	}
	return _instance;
}

Settings::Settings(){
	_instagramToken = "";
	_cache = true;
}

void Settings::setInstagramToken(string t){
	_instagramToken = t;
}

string Settings::getInstagramToken(){
	return _instagramToken;
}

void Settings::setCache(bool c){
	_cache = c;
}

bool Settings::getCache(){
	return _cache;
}

void Settings::setChangeIntervalSeconds(float s){
	_changeIntervalSeconds = s;
}

float Settings::getChangeIntervalSeconds(){
	return _changeIntervalSeconds;
}
