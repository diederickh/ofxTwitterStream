#ifndef OFXTWITTERSTREAMSQLITELISTENERH
#define OFXTWITTERSTREAMSQLITELISTENERH

#include "ofxSQLiteHeaders.h"
#include "ofxTwitterStreamEventListener.h"
#include "ofxTwitterStreamTweet.h"
#include <string>
								

class ofxTwitterStreamSQLiteListener : public ofxTwitterStreamEventListener {
public:
	ofxTwitterStreamSQLiteListener(std::string sDBName);
	void createDB();
	virtual void onTweet(ofxTwitterStreamTweet &rTweet);
	ofxTwitterStreamTweet getNextTweet(); // get the next best tweet
	void markTweetAsUsed(std::string nID);
	ofxSQLite sqlite;
	
};
#endif