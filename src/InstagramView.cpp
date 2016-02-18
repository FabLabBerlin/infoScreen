#include "InstagramView.h"

InstagramView::InstagramView(string type, string name, ofBuffer * data,
	string username, string caption, string profilePicture){
	
	_image = 0;
	_video = 0;
	_profileImage = 0;
	_username = username;
	_caption = caption;
	_profilePicture = profilePicture;
	
	cout << "InstagramView init" << endl;
	cout << " type: " << type << endl;
	
	if(type == "image"){
		_image = new ofImage();
		_image->load(*data);
	}
	
	if(type == "video"){
		_video = new ofVideoPlayer();
		_video->load(name);
		_video->setLoopState(OF_LOOP_NORMAL);
		_video->play();
	}
}

InstagramView::~InstagramView(){
	if(_video != 0){
		_video->stop();
		_video->close();
		delete _video;
	}
	
	if(_image != 0){
		delete _image;
	}
	
	if(_profileImage != 0){
		delete _profileImage;
	}
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
	
	ofRegisterURLNotification(this);
	ofLoadURLAsync(_profilePicture);
}

void InstagramView::update(){
	if(_video != 0){
		_video->update();
	}
}

void InstagramView::draw(){
	ofSetHexColor(0xFFFFFF);
	
	// Draw media
	if(_video != 0 && _video->isLoaded()){
		_video->draw(0, 0, ofGetHeight(), ofGetHeight());
	}else if(_image != 0 && _image->isAllocated()){
		_image->draw(0, 0, ofGetHeight(), ofGetHeight());
	}else{
		ofPushStyle();
		ofSetHexColor(0x333333);
		ofDrawRectangle(0, 0, ofGetHeight(), ofGetHeight());
		ofPopStyle();
	}
	
	// Draw avatar
	ofPushStyle();
	float avatarX = ofGetHeight() + _margin;
	float avatarY = _margin;
	ofSetHexColor(0xEB545A);
	ofDrawRectangle(avatarX, avatarY, _avatarWidth, _avatarHeight);
	if(_profileImage != 0 && _profileImage->isAllocated()){
		ofSetHexColor(0xFFFFFF);
		_profileImage->draw(avatarX + 5, avatarY + 5, _avatarWidth - 10, _avatarHeight - 10);
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
		string username = "@" + _username;
		_fontMdBold.drawString(username, usernameX, usernameY);
	}
	ofPopStyle();
	
	// Draw comment
	ofPushStyle();
	float commentX = avatarX;
	float commentY = avatarY + _avatarHeight + _margin + _fontLgRegular.getSize();
	ofSetHexColor(0x000000);
	
	char * buff = new char[255];
	char * str = new char[_caption.size() + 1];
	copy(_caption.begin(), _caption.end(), str);
	word_wrap(buff, str, 30);
	string caption = string(buff);
	
	if(_fontLgRegular.isLoaded()){
		_fontLgRegular.drawString(caption, commentX, commentY);
	}
	ofPopStyle();
	
	// Draw hashtag
	ofPushStyle();
	string hashtag = "#fablabberlin";
	float hashtagX = commentX;
	float hashtagY = ofGetHeight() - _margin - (_fontMdRegular.getLineHeight() * 2.5f);
	ofSetHexColor(0x61C5EA);
	if(_fontMdBold.isLoaded()){
		_fontMdBold.drawString(hashtag, hashtagX, hashtagY);
	}
	ofPopStyle();
	
	// Draw info
	ofPushStyle();
	string info = "Please hashtag us to appear\non this screen!";
	float infoX = hashtagX;
	float infoY = ofGetHeight() - _margin - _fontMdRegular.getLineHeight();
	ofSetHexColor(0x61C5EA);
	if(_fontMdRegular.isLoaded()){
		_fontMdRegular.drawString(info, infoX, infoY);
	}
	ofPopStyle();
	
}

void InstagramView::urlResponse(ofHttpResponse & response){
	
	ofUnregisterURLNotification(this);

	if(response.status!=200){
		return;
	}
	
	_profileImage = new ofImage();
	_profileImage->load(response.data);
}

char * InstagramView::word_wrap(char * buffer, char * string, int line_width){
    int i = 0;
    int k, counter;
 
    while(i < strlen(string)){
	
        // copy string until the end of the line is reached
        for(counter = 1; counter <= line_width; counter++){
            // check if end of string reached
            if (i == strlen(string)){
                buffer[i] = 0;
                return buffer;
            }
            buffer[i] = string[i];
            // check for newlines embedded in the original input 
            // and reset the index
            if(buffer[i] == '\n'){
                counter = 1; 
            }
            i++;
        }
		
        // check for whitespace
        if(isspace(string[i])){
            buffer[i] = '\n';
            i++;
        }else{
            // check for nearest whitespace back in string
            for (k = i; k > 0; k--){
                if(isspace(string[k])){
                    buffer[k] = '\n';
                    // set string index back to character after this one
                    i = k + 1;
                    break;
                }
            }
        }
    }
	
	buffer[i] = 0;
 
    return buffer;
}
