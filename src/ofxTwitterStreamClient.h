#ifndef OFXTWITTERSTREAMCLIENTH
#define OFXTWITTERSTREAMCLIENTH

//+++

//+++

#include "ofMain.h"

#undef check  // need to do this else boost won't compile on mac
#include <iostream>
#include <istream>
#include <ostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

// Using stringencoders to encode base64.
// To use this project, checkout the source from:
// http://code.google.com/p/stringencoders/source/checkout
//
// Then cd to the directory and:
// $ ./configure
// $ make
//
// this will create a files: modp_b64_data.h which is created for your
// system and holds some optimized data that necessary to use these functions.
#include "modp_b64.h"

// We're trying to make use of ofxJSON. When you want to use this, follow these
// points
// • add the json addon to the search paths: ../../../addons/ofxJSON/include

#include "ofxTwitterStreamTweet.h"
#include "ofxTwitterStreamEventManager.h"

class ofxTwitterStreamEventListener;

using boost::asio::ip::tcp;

class ofxTwitterStreamClient {
	public:
		ofxTwitterStreamClient(
			boost::asio::io_service& rIOService
			,const string sServer
			,const string sPath
			,const string sUser
			,const string sPassword
		);

		void connect();

		void handleResolve(
			const boost::system::error_code& oError
			,tcp::resolver::iterator oEndPointIterator
		);

		void handleConnect(
			const boost::system::error_code& oError
			,tcp::resolver::iterator oEndPointIterator
		);

		void handleWriteRequest(
			const boost::system::error_code& oError
		);


		void handleReadStatusLine(
			const boost::system::error_code& oError
		);

		void handleReadHeaders(
			const boost::system::error_code& oError
		);

		void handleReadContent(
			const boost::system::error_code& oError
		);

		void addEventListener(
			ofxTwitterStreamEventListener* pListener
		);

		void notifyTweet(
			ofxTwitterStreamTweet& rTweet
		);
		
		void setApplicationName(std::string sName);

		std::string getApplicationName();


	protected:
		tcp::resolver resolv;
		tcp::socket sock;
		boost::asio::streambuf request;
		boost::asio::streambuf response;
		boost::asio::io_service& asio_io_service;
		const string server;
		const string path;
		const string username;
		const string password;
		std::string application_name;
		ofxTwitterStreamEventManager* event_manager;


};
#endif
