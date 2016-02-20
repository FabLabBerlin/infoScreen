#include "ofMain.h"
#include "ofApp.h"
#include "Settings.h"
#include "ofxXmlSettings.h"

int main(int argc, char * argv[]){
	
	vector <string> arguments = vector<string>(argv, argv + argc);
	
	for(int i = 0; i < arguments.size(); ++i){
		if(arguments.at(i) == "-it"){
			int numArgs = arguments.size();
			bool isLast = (i == arguments.size() - 1);
			if(isLast){
				cout << "Please provide an IP address after the -it flag";
				ofExit(EXIT_FAILURE);
			}else{
				string instagramToken = arguments.at(i+1);
				Settings::instance()->setInstagramToken(instagramToken);
				break; // For now, before we have extra cli arguments
			}
		}
	}
	
	if(Settings::instance()->getInstagramToken() == ""){
		ofxXmlSettings settings;
		if(!settings.load("config.xml")){
			cout << "Please copy config-example.xml to config.xml and set up your token" << endl;
			ofExit(EXIT_FAILURE);
		}
		if(settings.tagExists("config")){
			settings.pushTag("config");
			Settings::instance()->setInstagramToken(settings.getValue("access_token", ""));
			Settings::instance()->setCache(settings.getValue("cache", true));
			settings.popTag();
		}
	}
	
	#ifdef TARGET_RASPBERRY_PI
		ofSetupOpenGL(800, 450, OF_FULLSCREEN);
	#else
		ofSetupOpenGL(800, 450, OF_WINDOW);
	#endif
	
	ofRunApp( new ofApp());
	
}
