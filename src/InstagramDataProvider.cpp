#include "InstagramDataProvider.h"

InstagramDataProvider::InstagramDataProvider(){
	_lastUpdateTime = -1.0f;
	_updateIntervalSeconds = 30.0f;
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
		
		if(now >= updateTime || _lastUpdateTime < 0){
			_instagram.getUserRecentMedia("self", 10);
			_lastUpdateTime = now;
			
			InstagramDataLoadedEventArgs args;
			
			for(int i = 0; i < _instagram.getVideoURL().size(); ++i){
				InstagramPostData postData;
				basicData data;
				data = _instagram.getBasicData()[i];
				
				postData.id = data.imageID;
				postData.username = data.user;
				postData.caption = data.caption;
				postData.videoUrl = _instagram.getVideoURL()[i];
				postData.imageUrl = _instagram.getImageURL()[i];
				postData.profilePictureUrl = _instagram.getProfilePicture()[i];
				
				if(postData.videoUrl == ""){
					postData.type = "image";
				}else{
					postData.type = "video";
				}
				
				args.posts.push_back(postData);
			} // for
			
			// Compare
			bool isSameOld = false;
			for(int i = 0; i < _args.posts.size(); ++i){
				if(_args.posts[i].id != args.posts[i].id){
					isSameOld = false;
				}
			}
			
			if(!isSameOld){
				ofNotifyEvent(dataLoadedEvent, args, this);
			}
			
		} // if
		
		ofSleepMillis(50);
	}
	
}