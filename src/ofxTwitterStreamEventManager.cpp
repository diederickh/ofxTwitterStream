#include "ofxTwitterStreamEventManager.h"
#include "ofxTwitterStreamClient.h"
#include "ofxTwitterStreamEventListener.h"

ofxTwitterStreamEventManager::ofxTwitterStreamEventManager(
	ofxTwitterStreamClient* pSender
)
	:sender(pSender)
{
}


void ofxTwitterStreamEventManager::notifyTweet(
	ofxTwitterStreamTweet oTweet
) 
{
	tweet_event.notify(sender,oTweet);

}

void ofxTwitterStreamEventManager::notifyTweet(
	ofxTwitterStreamTweetRaw oTweet
) 
{
	tweet_raw_event.notify(sender, oTweet);
}

void ofxTwitterStreamEventManager::addListener(
	ofxTwitterStreamEventListener* pListener
)
{
	tweet_raw_event += Poco::Delegate<ofxTwitterStreamEventListener, ofxTwitterStreamTweetRaw>(pListener, &ofxTwitterStreamEventListener::onTweet);
	tweet_event += Poco::Delegate<ofxTwitterStreamEventListener, ofxTwitterStreamTweet>(pListener, &ofxTwitterStreamEventListener::onTweet);
}
