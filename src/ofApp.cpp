#include "ofApp.h"

ofApp::ofApp(){
	_instagramView = 0;
	_instagramMaxItems = 5;
	_instagramCurrentItem = 0;
	_changeIntervalSeconds = 15.0f;
	_lastChangeTime = -1.0f;
}

void ofApp::setup(){
	ofBackground(255,255,255);
	ofSetVerticalSync(true);
	ofAddListener(_instagramDataProvider.dataLoadedEvent, this, &ofApp::onInstagramDataLoaded);
	_instagramDataProvider.setup();
}

void ofApp::update(){
	if(_instagramPosts.size() <= 0){
		return;
	}
	
	float now = ofGetElapsedTimef();
	float nextChangeTime = _lastChangeTime + _changeIntervalSeconds;
	
	if(now >= nextChangeTime || _lastChangeTime < 0){
		cout << "change" << endl;
		cout << " numItems: " << _instagramPosts.size() << endl;
		
		if(_instagramView != 0){
			delete _instagramView;
		}
		
		_instagramView = new InstagramView(_instagramPosts[_instagramCurrentItem]);
		_instagramView->setup();
		_lastChangeTime = now;
		_instagramCurrentItem++;
		
		if(_instagramCurrentItem >= _instagramPosts.size()){
			_instagramCurrentItem = 0;
		}
	}
	
	if(_instagramView != 0){
		_instagramView->update();
	}
}

void ofApp::draw(){
	if(_instagramView != 0){
		_instagramView->draw();
	}
}

void ofApp::onInstagramDataLoaded(InstagramDataLoadedEventArgs & args){
	cout << "ofApp::onInstagramDataLoaded()" << endl;
	cout << " args.posts.size(): " << args.posts.size() << endl;
	
	_instagramPosts = args.posts;
	/*
	bool isNew = true;
	for(int i = 0; i < _instagramData.size(); ++i){
		if(args.videoUrl == _instagramData[i].videoUrl){
			isNew = false;
			break;
		}
		
		if(args.imageUrl == _instagramData[i].imageUrl){
			isNew = false;
			break;
		}
	}
	
	if(isNew){
		_instagramData.push_back(args);
	}
	*/
}
