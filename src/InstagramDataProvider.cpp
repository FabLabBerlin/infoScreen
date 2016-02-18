#include "InstagramDataProvider.h"

InstagramDataProvider::InstagramDataProvider(){
	_lastUpdateTime = -1.0f;
	_updateIntervalSeconds = 10.0f;
	_isMediaLoading = false;
}

void InstagramDataProvider::setup(){
	cout << "Using instagram token " << Settings::instance()->getInstagramToken() << endl;
	_instagram.setup(Settings::instance()->getInstagramToken(), "self");
    _instagram.setCertFileLocation(ofToDataPath("ca-bundle.crt", false));
	
	startThread();
}

void InstagramDataProvider::threadedFunction(){

	while(isThreadRunning()){
		
		float now = ofGetElapsedTimef();
		float updateTime = _lastUpdateTime + _updateIntervalSeconds;
		
		if((now >= updateTime || _lastUpdateTime < 0) && !_isMediaLoading){
			_instagram.getUserRecentMedia("self");
			_lastUpdateTime = now;

			if(_instagram.getVideoURL().size() && _instagram.getVideoURL()[0] != ""){
				if(_currentVideoUrl != _instagram.getVideoURL()[0]){
					_currentVideoUrl = _instagram.getVideoURL()[0];
					size_t found = _currentVideoUrl.find_last_of("/\\");
					_currentVideoFileName = _currentVideoUrl.substr(found + 1);
					ofRegisterURLNotification(this);
					ofSaveURLAsync(_currentVideoUrl, _currentVideoFileName);
					_currentMediaType = "video";
					_isMediaLoading = true;
				}
			}else if(_instagram.getImageURL().size()){
				if(_currentImageUrl != _instagram.getImageURL()[0]){
					_currentImageUrl = _instagram.getImageURL()[0];
					ofRegisterURLNotification(this);
					ofLoadURLAsync(_currentImageUrl);
					_currentMediaType = "image";
					_isMediaLoading = true;
				}
			}
		}
		
		ofSleepMillis(100);
	}
	
}

void InstagramDataProvider::urlResponse(ofHttpResponse & response){
	
	ofUnregisterURLNotification(this);
	
	if(response.status!=200){
		_isMediaLoading = false;
		return;
	}
	
	MediaLoadedEventArgs args;
	
	if(response.request.saveTo){
		args.type = "video";
		args.name = response.request.name;
	}else{
		args.type = "image";
		args.data = response.data;
	}
	
	basicData data;
	if(_instagram.getBasicData().size()){
		data = _instagram.getBasicData()[0];
	}
	
	string profilePicture;
	if(_instagram.getProfilePicture().size()){
		profilePicture = _instagram.getProfilePicture()[0];
	}
	
	args.profilePicture = profilePicture;
	args.username = data.user;
	args.caption = data.caption;
	
	ofNotifyEvent(mediaLoadedEvent, args, this);
	
	_isMediaLoading = false;
}

