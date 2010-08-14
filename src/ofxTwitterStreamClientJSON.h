#ifndef OFXTWITTERSTREAMCLIENTJSONH
#define OFXTWITTERSTREAMCLIENTJSONH

#include "ofxTwitterStreamClient.h"
#include "ofxTwitterStreamJSONParser.h"

#undef check  // need to do this else boost won't compile on mac
//#include <iostream>
//#include <istream>
#include "ofMain.h"
#include <ostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>


class ofxTwitterStreamClientJSON : public ofxTwitterStreamClient {
public:
	ofxTwitterStreamClientJSON(
		boost::asio::io_service& rIOService
		,const string sServer
		,const string sPath
		,const string sUser
		,const string sPassword
	):ofxTwitterStreamClient(rIOService, sServer, sPath, sUser, sPassword) {
		if(event_manager != NULL) {
			addEventListener(new ofxTwitterStreamJSONParser());
		}
	}
};
#endif
