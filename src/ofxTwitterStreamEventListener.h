#ifndef OFXTWITTERSTREAMEVENTLISTENERH
#define OFXTWITTERSTREAMEVENTLISTENERH

#include "ofxTwitterStreamTweet.h"
#include "ofxTwitterStreamTweetRaw.h"

class ofxTwitterStreamClient;
class ofxTwitterStreamEventListener {
public:
		ofxTwitterStreamEventListener();
		void setTwitterStreamClient(ofxTwitterStreamClient* pClient);
		void onTweet(const void* pSender, ofxTwitterStreamTweet &rTweet);
		void onTweet(const void* pSender, ofxTwitterStreamTweetRaw &rTweet);
		virtual void onTweet(ofxTwitterStreamTweet &rTweet);
		virtual void onTweet(ofxTwitterStreamTweetRaw &rTweet);
			
		ofxTwitterStreamClient* client;
};
#endif