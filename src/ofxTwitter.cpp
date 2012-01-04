#include "ofxTwitter.h"
ofxTwitter::ofxTwitter() {
}

ofxTwitter::~ofxTwitter() {
	connector.stop();
	thread.join();
}

void ofxTwitter::connect(
	string sUser
	,string sPass
	,string sServer
	,string sFilter
)
{
	connector.setup(sUser, sPass, sServer, sFilter);
	thread.start(connector);
}

bool ofxTwitter::hasNewTweets() {
	return connector.hasNewTweets();
}

ofxTweet ofxTwitter::getNextTweet() {
	return connector.getNextTweet();
}