#ifndef OFXTWITTERSTREAMEVENTMANAGERH
#define OFXTWITTERSTREAMEVENTMANAGERH

#include "Poco/BasicEvent.h"
#include "ofxTwitterStreamTweet.h"
#include "ofxTwitterStreamTweetRaw.h"

class ofxTwitterStreamClient;
class ofxTwitterStreamEventListener;

class ofxTwitterStreamEventManager {
public:
	ofxTwitterStreamEventManager(ofxTwitterStreamClient* pSender);
	void notifyTweet(ofxTwitterStreamTweet oTweet);
	void notifyTweet(ofxTwitterStreamTweetRaw oTweet);
	void addListener(ofxTwitterStreamEventListener* pListener);
private:
	Poco::BasicEvent<ofxTwitterStreamTweet> tweet_event;
	Poco::BasicEvent<ofxTwitterStreamTweetRaw> tweet_raw_event;
	ofxTwitterStreamClient* sender;
};
#endif