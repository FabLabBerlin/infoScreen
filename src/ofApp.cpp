#include "ofApp.h"

ofApp::ofApp(){
	_instagramView = 0;
}

void ofApp::setup(){
	ofBackground(255,255,255);
	ofSetVerticalSync(true);
	
	ofAddListener(_instagramDataProvider.mediaLoadedEvent, this, &ofApp::onMediaLoaded);
	_instagramDataProvider.setup();
}

void ofApp::update(){
	if(_instagramView != 0){
		_instagramView->update();
	}
}

void ofApp::draw(){
	if(_instagramView != 0){
		_instagramView->draw();
	}
}

void ofApp::onMediaLoaded(MediaLoadedEventArgs & args){
	if(_instagramView != 0){
		delete _instagramView;
		_instagramView = 0;
	}

	if(args.type == "image"){
		_instagramView = new InstagramView("image", "", &args.data,
			args.username, args.caption, args.profilePicture);
		_instagramView->setup();
	}
	
	if(args.type == "video"){
		_instagramView = new InstagramView("video", args.name, 0,
			args.username, args.caption, args.profilePicture);
		_instagramView->setup();
	}
}
