#ifndef OFXTWITTERSTREAMJSONPARSERH
#define OFXTWITTERSTREAMJSONPARSERH

#include "ofxTwitterStreamTweetRaw.h"
#include "ofxTwitterStreamEventListener.h"
#include "ofxTwitterStreamClient.h"
#include "ofMain.h"

#include <jansson.h>
#include "ofxJansson.h"

class ofxTwitterStreamJSONParser : public ofxTwitterStreamEventListener {
public:
	ofxTwitterStreamJSONParser();
	virtual void onTweet(ofxTwitterStreamTweetRaw &rTweet);
	ofxJansson json;
};
#endif