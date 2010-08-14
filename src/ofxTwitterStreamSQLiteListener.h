/**
 * Add this listener when you want to store new tweets
 * in a SQLite database.  See ofxTwitterStreamSQLiteListener.cpp for 
 * the structure of the table in which we store the tweets.
 *
 * @author	Diederick Huijbers <diederick@apollomedia.nl>
 */
 
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
	ofxTwitterStreamTweet getRandomTweet(); // get the next best tweet
	bool hasTweets();
	bool hasNextTweet();
	void markTweetAsUsed(std::string nID);
	ofxSQLite sqlite;
};
#endif