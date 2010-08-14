#ifndef OFXTWITTERSTREAMCLIENTTHREADH
#define OFXTWITTERSTREAMCLIENTTHREADH

#undef check  // need to do this else boost won't compile on mac
#include <boost/asio.hpp>
#include "ofxThread.h"

class ofxTwitterStreamClientJSON;

class ofxTwitterStreamClientJSONThread : public ofxThread {
public:
	ofxTwitterStreamClientJSONThread(
		boost::asio::io_service& rIOService
		,const string sServer
		,const string sPath
		,const string sUser
		,const string sPassword
	);

	virtual void threadedFunction();
	ofxTwitterStreamClientJSON* client;
	boost::asio::io_service& io_service;
};
#endif
