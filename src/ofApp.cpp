#include "ofApp.h"

ofApp::ofApp(){
	_currentInstagramView = &_instagramViewA;
	_instagramCurrentItem = 0;
	_changeIntervalSeconds = Settings::instance()->getChangeIntervalSeconds();
	_lastChangeTime = -1.0f;
}

void ofApp::setup(){
	_instagramViewA.setup();
	_instagramViewB.setup();
	
	ofBackground(255,255,255);
	ofSetVerticalSync(true);
	
	ofAddListener(_instagramDataProvider.dataLoadedEvent, this, &ofApp::onInstagramDataLoaded);
	_instagramDataProvider.setup();
}

void ofApp::update(){
	ofHideCursor();

	if(_instagramPosts.size() <= 0){
		return;
	}
	
	float now = ofGetElapsedTimef();
	float nextChangeTime = _lastChangeTime + _changeIntervalSeconds;
	
	if(now >= nextChangeTime || _lastChangeTime < 0){
	
		InstagramView * next;
		if(_currentInstagramView == &_instagramViewA){
			next = &_instagramViewB;
		}else{
			next = &_instagramViewA;
		}
	
		if(next->getIsLoaded()){
			_currentInstagramView->unload();
			_currentInstagramView = next;
			_lastChangeTime = now;
		}else if(!next->getIsLoading()){
			_instagramCurrentItem++;
			
			if(_instagramCurrentItem >= _instagramPosts.size()){
				_instagramCurrentItem = 0;
			}
			
			next->load(_instagramPosts[_instagramCurrentItem]);
		}
	}
	
	if(_currentInstagramView->getIsLoaded()){
		_currentInstagramView->update();
	}
}

void ofApp::draw(){
	if(_currentInstagramView->getIsLoaded()){
		_currentInstagramView->draw();
	}
	
	InstagramView * next;
	if(_currentInstagramView == &_instagramViewA){
		next = &_instagramViewB;
	}else{
		next = &_instagramViewA;
	}
	
	if(next->getIsLoading()){
		ofPushStyle();
		ofSetHexColor(0xff0000);
		ofDrawRectangle(ofRectangle(ofGetWidth()-20, 10, 10, 10));
		ofPopStyle();
	}
}

void ofApp::onInstagramDataLoaded(InstagramDataLoadedEventArgs & args){
	cout << "ofApp::onInstagramDataLoaded()" << endl;
	cout << " args.posts.size(): " << args.posts.size() << endl;
	
	_instagramPosts = args.posts;
}
