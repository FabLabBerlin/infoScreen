#include "ofMain.h"
#include "ofApp.h"
#include "Settings.h"

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
	
	ofSetupOpenGL(1024,768, OF_WINDOW);
	ofRunApp( new ofApp());
	
}
