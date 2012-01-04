#pragma once 
#include <string>
#include <deque>
#include <iostream>
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/String.h"
#include "Poco/RegularExpression.h"
#include "Poco/RWLock.h"
#include "modp_b64.h"
#include "jansson.h"
#include "ofxTweet.h"

using namespace std;

class ofxTwitterConnector : public Poco::Runnable {
public:
	ofxTwitterConnector();
	void setup(
		 string sUsername
		,string sPassword
		,string sStreamServer
		,string sFilterURL
	);
	
	virtual void run();
	void parseBuffer(vector<char> sBuffer);
	void parseTweetJSON(string sLine);
	bool hasNewTweets();
	ofxTweet getNextTweet();
	void stop();
private:
	Poco::Net::StreamSocket* socket_ptr;
	string username;
	string password;
	string server;
	string filter;
	bool is_connected;
	deque<ofxTweet> tweets;
	Poco::RWLock lock;
};