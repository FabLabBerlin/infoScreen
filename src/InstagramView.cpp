#include "InstagramView.h"

InstagramView::InstagramView(){
	_margin = 0.0f;
	_avatarWidth = 0.0f;
	_avatarHeight = 0.0f;
	
	_isLoaded = false;
	_isLoading = false;
}

InstagramView::~InstagramView(){
	ofUnregisterURLNotification(this);
}

void InstagramView::setup(){
	_margin = (float)ofGetWidth() / 22.0f;
	_avatarWidth = (float)ofGetWidth() / 12.0f;
	_avatarHeight = (float)ofGetWidth() / 12.0f;
	
	ofTrueTypeFont::setGlobalDpi(72);

	int fontMdSize = (int)(36.0f / 1920.0f * (float)ofGetWindowWidth());
	_fontMdRegular.load("OpenSans-Regular.ttf", fontMdSize, true, true);
	_fontMdRegular.setLineHeight(fontMdSize + 5);
	_fontMdRegular.setLetterSpacing(1.037);

	_fontMdBold.load("OpenSans-Bold.ttf", fontMdSize, true, true);
	_fontMdBold.setLineHeight(fontMdSize + 5);
	_fontMdBold.setLetterSpacing(1.037);
	
	int fontLgSize = (int)(42.0f / 1920.0f * (float)ofGetWindowWidth());
	_fontLgRegular.load("OpenSans-Regular.ttf", fontLgSize, true, true);
	_fontLgRegular.setLineHeight(fontLgSize + 5);
	_fontLgRegular.setLetterSpacing(1.037);
}

void InstagramView::load(InstagramPostData args){
	_args = args;
	
	// Format caption
	string tail;
	
	if(_args.caption.size() > 200){
		_args.caption = _args.caption.substr(0, 200);
		tail = "...";
	}else{
		tail = "";
	}
	
	_args.caption = getWordWrapString(_args.caption, 30) + tail;
	
	loadProfileImage();
	_isLoading = true;
}

void InstagramView::unload(){
	ofUnregisterURLNotification(this);
	
	#ifdef TARGET_RASPBERRY_PI
		_video.close();
	#else
		if(_video.isLoaded() && _video.isInitialized()){
			_video.stop();
			_video.close();
		}
	#endif
	
	if(_image.isAllocated()){
		_image.clear();
	}
	
	if(_profileImage.isAllocated()){
		_profileImage.clear();
	}
	
	_isLoaded = false;
}

void InstagramView::update(){
	#ifndef TARGET_RASPBERRY_PI
		if(_video.isLoaded()){
			_video.update();
		}
	#endif
}

void InstagramView::draw(){

	ofSetHexColor(0xFFFFFF);
	
	// Draw media
	#ifdef TARGET_RASPBERRY_PI
		if(_video.isPlaying()){
			_video.draw(0, 0, ofGetHeight(), ofGetHeight());
	#else
		if(_video.isLoaded() && _video.isInitialized()){
			_video.draw(0, 0, ofGetHeight(), ofGetHeight());
	#endif
	}else if(_image.isAllocated()){
		_image.draw(0, 0, ofGetHeight(), ofGetHeight());
	}
	
	// Draw avatar
	ofPushStyle();
	float avatarX = ofGetHeight() + _margin;
	float avatarY = _margin;
	ofSetHexColor(0xEB545A);
	ofDrawRectangle(avatarX, avatarY, _avatarWidth, _avatarHeight);
	if(_profileImage.isAllocated()){
		ofSetHexColor(0xFFFFFF);
		_profileImage.draw(avatarX + 5, avatarY + 5, _avatarWidth - 10, _avatarHeight - 10);
	}else{
		ofSetHexColor(0x333333);
		ofDrawRectangle(avatarX + 5, avatarY + 5, _avatarWidth - 10, _avatarHeight - 10);
	}
	ofPopStyle();
	
	// Draw username
	ofPushStyle();
	float usernameX = avatarX + _avatarWidth + (_margin / 2.0f);
	float usernameY = avatarY + (_avatarHeight / 2.0f) + 5.0f;
	ofSetHexColor(0xEB545A);
	if(_fontMdBold.isLoaded()){
		string username = "@" + _args.username;
		_fontMdBold.drawString(username, usernameX, usernameY);
	}
	ofPopStyle();
	
	// Draw comment
	ofPushStyle();
	float commentX = avatarX;
	float commentY = avatarY + _avatarHeight + _margin + _fontLgRegular.getSize();
	ofSetHexColor(0x000000);

	if(_fontLgRegular.isLoaded()){
		_fontLgRegular.drawString(_args.caption, commentX, commentY);
	}
	ofPopStyle();
	
	// Draw hashtag
	ofPushStyle();
	string hashtag = "@fablabberlin";
	float hashtagX = commentX;
	float hashtagY = ofGetHeight() - _margin - (_fontMdRegular.getLineHeight() * 2.5f);
	ofSetHexColor(0x61C5EA);
	if(_fontMdBold.isLoaded()){
		_fontMdBold.drawString(hashtag, hashtagX, hashtagY);
	}
	ofPopStyle();
	
	// Draw info
	ofPushStyle();
	string info = "Fab Lab Berlin on Instagram.\nContent? Talk to the lab manager!";
	float infoX = hashtagX;
	float infoY = ofGetHeight() - _margin - _fontMdRegular.getLineHeight();
	ofSetHexColor(0x61C5EA);
	if(_fontMdRegular.isLoaded()){
		_fontMdRegular.drawString(info, infoX, infoY);
	}
	ofPopStyle();
}

void InstagramView::loadImage(){
	ofRegisterURLNotification(this);
	size_t found = _args.imageUrl.find_last_of("/\\");
	string imageFileName = _args.imageUrl.substr(found + 1);
	
	// Uncomment this if caching is not important or filesystem does not support long filenames
	//found = imageFileName.find_first_of("?\\");
	//string fileName = imageFileName.substr(0, found);
	
	// Before loading check if we already have the file
	ofFile file = ofFile(imageFileName);
	if(file.exists() && Settings::instance()->getCache()){
		initImage(imageFileName);
	}else{
		ofSaveURLAsync(_args.imageUrl, imageFileName);
	}
}

void InstagramView::loadVideo(){
	ofRegisterURLNotification(this);
	size_t found = _args.videoUrl.find_last_of("/\\");
	string videoFileName = _args.videoUrl.substr(found + 1);
	
	// Before loading check if we already have the file
	ofFile file = ofFile(videoFileName);
	if(file.exists() && Settings::instance()->getCache()){
		initVideo(videoFileName);
	}else{
		ofSaveURLAsync(_args.videoUrl, videoFileName);
	}
}

void InstagramView::loadProfileImage(){
	ofRegisterURLNotification(this);
	size_t found = _args.profilePictureUrl.find_last_of("/\\");
	string profilePictureFileName = _args.profilePictureUrl.substr(found + 1);
	
	// Before loading check if we already have the file
	ofFile file = ofFile(profilePictureFileName);
	if(file.exists() && Settings::instance()->getCache()){
		initProfileImage(profilePictureFileName);
	}else{
		ofSaveURLAsync(_args.profilePictureUrl, profilePictureFileName);
	}
}

void InstagramView::initImage(string fileName){
	_image.load(fileName);
	_isLoaded = true;
	_isLoading = false;
}

void InstagramView::initVideo(string fileName){
	
	#ifdef TARGET_RASPBERRY_PI
		ofxOMXPlayerSettings settings;
		settings.videoPath = ofToDataPath(fileName, true);
		settings.useHDMIForAudio = true;	//default true
		settings.enableTexture = false;		//default true
		settings.enableLooping = true;		//default true
		settings.enableAudio = false;		//default true, save resources by disabling
		_video.setup(settings);
	#else
		_video.load(fileName);
		_video.setLoopState(OF_LOOP_NORMAL);
		_video.play();
	#endif

	_isLoaded = true;
	_isLoading = false;
}

void InstagramView::initProfileImage(string fileName){
	_profileImage.load(fileName);
	
	if(_args.type == "image"){
		loadImage();
	}

	if(_args.type == "video"){
		loadVideo();
	}
}

void InstagramView::urlResponse(ofHttpResponse & response){
	ofUnregisterURLNotification(this);

	if(response.status != 200){
		return;
	}
	
	if(response.request.url == _args.imageUrl){
		initImage(response.request.name);
	}
	
	if(response.request.url == _args.videoUrl){
		initVideo(response.request.name);
	}
	
	if(response.request.url == _args.profilePictureUrl){
		initProfileImage(response.request.name);
	}
}

string InstagramView::getWordWrapString(string inputString, int charsPerLine){
	int i = 0;
	int charInLine = 0;
	
	string outputLine;
	string outputString;
	
	while (i <= inputString.size()) {
		
		if( i > inputString.size() - 1){
			break;
		}
		
		outputLine += inputString[i];
		bool lineDone = false;
		
		if(outputLine.size() >= charsPerLine){
			
			// At this point current line is full with characters
			lineDone = true;
			
			// Check if the next character is whitespace
			// If it is not, we have to find last space and continue from there
			if((i + 1) < inputString.size() && inputString[i + 1] != ' '){
				while(outputLine[outputLine.size() - 1] != ' '){
					
					// Remove last char of the partial last word from the line
					outputLine.pop_back();
						
					// And move back our input string cursor by one step
					--i;
				}
			}
		}else{
			++charInLine;
		}
		
		if(lineDone || (i == inputString.size() - 1)){
			
			// Remove whitespace from the beginning of the line
			while(outputLine[0] == ' '){
				outputLine.erase(0, 1);
			}
			
			// Remove whitespace from the end of the line
			while(outputLine[outputLine.size() - 1] == ' '){
				outputLine.pop_back();
			}
		
			// Finalize line by adding a linebreak
			outputLine += "\n";
			
			// Add the line to final output string
			outputString += outputLine;
			
			// Reset line
			outputLine = "";
			charInLine = 0;
		}
		
		++i;
		
	}
	
	// Remove endlines from the end
	while(outputString[outputString.size() - 1] == '\n'){
		outputString.pop_back();
	}
	
    return outputString;
}
