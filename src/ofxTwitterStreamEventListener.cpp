#include "ofxTwitterStreamEventListener.h"
#include "ofxTwitterStreamClient.h"

ofxTwitterStreamEventListener::ofxTwitterStreamEventListener()	
	:client(NULL)
{
}

// handle a nicely parsed tweet event.
void ofxTwitterStreamEventListener::onTweet(
	 const void* pSender
	,ofxTwitterStreamTweet &rTweet
)
{
	onTweet(rTweet);
}

// handle a raw tweet data event.
void ofxTwitterStreamEventListener::onTweet(
	const void* pSender
	,ofxTwitterStreamTweetRaw &rTweet
)
{
	onTweet(rTweet);
}

void ofxTwitterStreamEventListener::onTweet(
	ofxTwitterStreamTweet &rTweet
)
{
}

void ofxTwitterStreamEventListener::onTweet(
	ofxTwitterStreamTweetRaw &rTweet
) 
{
}

// is called when this listener is added to the ofxTwitterStreamClient
void ofxTwitterStreamEventListener::setTwitterStreamClient(
	ofxTwitterStreamClient* pClient
)
{
	client = pClient;
}


