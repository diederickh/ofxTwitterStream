#pragma once
#include <string>
#include <Poco/Thread.h>
#include "ofxTwitterConnector.h"
#include "ofxTweet.h"
using namespace std;

class ofxTwitter {
public:
	ofxTwitter();
	~ofxTwitter();
	void connect(
		 string sUsername
		,string sPassword
		,string sStreamServer
		,string sFilterURL
	);
	bool hasNewTweets();
	ofxTweet getNextTweet();	
private:
	ofxTwitterConnector connector;
	Poco::Thread thread;
};