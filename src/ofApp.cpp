#include "ofApp.h"

void ofApp::setup(){
	ofBackground(255,255,255);
	ofSetVerticalSync(true);
	ofRegisterURLNotification(this);
	
	cout << "Using instagram token " << Settings::instance()->getInstagramToken() << endl;
	instagram.setup(Settings::instance()->getInstagramToken(), "self");
    instagram.setCertFileLocation(ofToDataPath("ca-bundle.crt", false));
	instagram.getUserRecentMedia("self");
	//instagram.getUserLikedMedia();
	
	lastInstagramUpdate = 0.0f;
	instagramUpdateIntervalSeconds = 5.0f;
}

void ofApp::update(){

	float now = ofGetElapsedTimef();
	float updateTime = lastInstagramUpdate + instagramUpdateIntervalSeconds;
	if(now >= updateTime){
		instagram.getUserRecentMedia("self");
		lastInstagramUpdate = now;
		cout << "Updating Instagram feed on: " << ofToString(now) << endl;
	}

	if(instagram.getVideoURL().size()){
		if(currentVideoUrl != instagram.getVideoURL()[0]){
			currentVideoUrl = instagram.getVideoURL()[0];
			size_t found = currentVideoUrl.find_last_of("/\\");
			currentVideoFileName = currentVideoUrl.substr(found + 1);
			
			//currentVideoUid = ofToString(ofGetSystemTime()) + ".mp4";
			//currentVideo.load(currentVideoUrl);
			cout << "numImages: " << instagram.getImageURL().size() << endl;
			cout << "numVideos: " << instagram.getVideoURL().size() << endl;
			cout << currentVideoUrl << endl;
			
			ofSaveURLAsync(currentVideoUrl, currentVideoFileName);
		}
	}

    currentVideo.update();
}

void ofApp::draw(){
	ofSetHexColor(0xFFFFFF);
    currentVideo.draw(20,20);
	instagram.drawJSON(10);
}

void ofApp::urlResponse(ofHttpResponse & response){
	cout << "response.status: " << response.status << endl;
	cout << "response.request.name: " << response.request.name << endl;
	cout << "response.data: " << response.data << endl;
	currentVideo.close();
	currentVideo.load(response.request.name);
	currentVideo.setLoopState(OF_LOOP_NORMAL);
	currentVideo.play();
}
