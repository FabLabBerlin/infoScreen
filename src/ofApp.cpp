#include "ofApp.h"

ofApp::ofApp(){
	_instagramView = 0;
	_nextInstagramView = 0;
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
	ofHideCursor();

	if(_instagramPosts.size() <= 0){
		return;
	}
	
	float now = ofGetElapsedTimef();
	float nextChangeTime = _lastChangeTime + _changeIntervalSeconds;
	
	if(now >= nextChangeTime || _lastChangeTime < 0){
		if(_nextInstagramView == 0){
			_instagramCurrentItem++;
			
			if(_instagramCurrentItem >= _instagramPosts.size()){
				_instagramCurrentItem = 0;
			}
			
			_nextInstagramView = new InstagramView(_instagramPosts[_instagramCurrentItem]);
			_nextInstagramView->setup();
		}else{
			if(_nextInstagramView->getIsLoaded()){
				if(_instagramView != 0){
					delete _instagramView;
				}
				
				_instagramView = _nextInstagramView;
				_nextInstagramView = 0;
				_lastChangeTime = now;
			}
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
	
	if(_nextInstagramView != 0){
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
