#include "ofxTwitterStreamClient.h"
#include "ofxTwitterStreamEventListener.h"


ofxTwitterStreamClient::ofxTwitterStreamClient(
	boost::asio::io_service& rIOService
	,const string sServer
	,const string sPath
	,const string sUser
	,const string sPassword
)
	:resolv(rIOService)
	,sock(rIOService)
	,asio_io_service(rIOService)
	,server(sServer)
	,path(sPath)
	,event_manager(NULL)
	,username(sUser)
	,password(sPassword)
{
	cout << "Creating client\n";

	event_manager = new ofxTwitterStreamEventManager(this);
}

void ofxTwitterStreamClient::connect() {
	string str_src = username +":" +password;
	string encoded = modp::b64_encode(str_src);

	std::ostream request_stream(&request);
	request_stream << "GET " << path << " HTTP/1.0\r\n";
	request_stream << "Host: " << server << "\r\n";
	request_stream << "User-Agent: test_with_stream\r\n";
	request_stream << "Accept:*/*\r\n";
	request_stream << "Authorization: Basic " << encoded << "\r\n";
	request_stream << "\r\n\r\n";

	// start async resolve to translate the server and service names
	tcp::resolver::query query(server, "http");
	resolv.async_resolve(
		 query
		,boost::bind(
			 &ofxTwitterStreamClient::handleResolve
			,this
			,boost::asio::placeholders::error
			,boost::asio::placeholders::iterator
		)
	);
}

void ofxTwitterStreamClient::handleResolve(
	const boost::system::error_code& oError
	,tcp::resolver::iterator oEndPointIterator
)
{
	if(!oError) {
		tcp::endpoint end_point = *oEndPointIterator;
		sock.async_connect(
			end_point
			,boost::bind(
				&ofxTwitterStreamClient::handleConnect
				,this
				,boost::asio::placeholders::error
				,++oEndPointIterator
			)
		);
	}
	else {
		cout << "Error: " << oError.message() << "\n";
	}
}



void ofxTwitterStreamClient::handleConnect(
 	const boost::system::error_code& oError
	,tcp::resolver::iterator oEndPointIterator
)
{
	if (!oError) {
		cout << "TWITTER: Connected\n";
		boost::asio::async_write(
			sock
			,request
			,boost::bind(
				&ofxTwitterStreamClient::handleWriteRequest
				,this
				,boost::asio::placeholders::error
			)
		);
	}
	else if (oEndPointIterator != tcp::resolver::iterator()) {
		cout << "TWITTER: Could not connect, try again...\n";
		sock.close();
		tcp::endpoint end_point = *oEndPointIterator;
		sock.async_connect(
			end_point
			,boost::bind(
				&ofxTwitterStreamClient::handleConnect
				,this
				,boost::asio::placeholders::error
				,++oEndPointIterator
			)
		);
	}
	else {
		cout << "TWITTER: Error: " << oError.message() << "\n";
	}
}

void ofxTwitterStreamClient::handleWriteRequest(
	const boost::system::error_code& oError
)
{
	if(!oError) {
		cout << "Handle write request\n";
		boost::asio::async_read_until(
			sock
			,response
			,"\r\n"
			,boost::bind(
				&ofxTwitterStreamClient::handleReadStatusLine
				,this
				,boost::asio::placeholders::error
			)
		);

	}
	else {
		cout << "Error: " << oError.message() << "\n";
	}
}


void ofxTwitterStreamClient::handleReadStatusLine(
	const boost::system::error_code& oError
)
{
	if (!oError) {
		istream response_stream(&response);

		string http_version;
		response_stream >> http_version;

		unsigned int status_code;
		response_stream >> status_code;

		string status_message;
		getline(response_stream, status_message);
		
		string content_type;
		getline(response_stream, content_type);
		
		string server;
		getline(response_stream, server);

		cout << "Got http version: " << http_version << "\n";
		cout << "Got status code: " << status_code << "\n";
		cout << "Got status message: " << status_message  << "\n";
		cout << "Got content type: " << content_type  << "\n";
		cout << "Got server: " << server  << "\n";

		if(!response_stream || http_version.substr(0,5) != "HTTP/") {
			cout << "Invalid response!\n";
			return;
		}

		if(status_code != 200) {
			cout << "Response returned with status code: " << status_code << "\n";
			return;
		}

		boost::asio::async_read_until(
			sock
			,response
			,"\r\n"
			,boost::bind(
				&ofxTwitterStreamClient::handleReadHeaders
				,this
				,boost::asio::placeholders::error
			)
		);


	}
	else {
		cout << "Error: " << oError.message() << "\n";
	}
}


void ofxTwitterStreamClient::handleReadHeaders(
	const boost::system::error_code& oError
)
{
	if(!oError) {
		std::istream response_stream(&response);
		string header;
		response_stream >> std::ws;

		// start reading remaining data until EOF.
		boost::asio::async_read_until(
			sock
			,response
			,'\r'
			,boost::bind(
				&ofxTwitterStreamClient::handleReadContent
				,this
				,boost::asio::placeholders::error
			)
		);

	}
	else {
		cout << "Error: " << oError.message() << "\n";
	}
}


void ofxTwitterStreamClient::handleReadContent(
	const boost::system::error_code& oError
)
{
	if(!oError) {
		// @important:
		// note that async_read_until reads until the character given BUT
		// it can add some more characters to the end of the buffer for
		// perfomance reasons. This is done by asio and therefore you must
		// take care of this yourself.
		//
		// Also make use of streams to get data from te buffer! If I'm correct
		// this resets the stream position internally.
		std::istream response_stream(&response);
		string data;
		std::getline(response_stream, data, '\r');
	
		ofxTwitterStreamTweetRaw tweet_raw(data);
		event_manager->notifyTweet(tweet_raw);

		boost::asio::async_read_until(
			sock
			,response
			,'\r'
			,boost::bind(
				&ofxTwitterStreamClient::handleReadContent
				,this
				,boost::asio::placeholders::error
			)
		);


	}
	else if (oError != boost::asio::error::eof) {
		cout << "Error: " << oError << "\n";
	}
}


void ofxTwitterStreamClient::addEventListener(
	ofxTwitterStreamEventListener* pListener)
{
	pListener->setTwitterStreamClient(this);
	event_manager->addListener(pListener);

}

void ofxTwitterStreamClient::notifyTweet(
	ofxTwitterStreamTweet& rTweet
)
{
	event_manager->notifyTweet(rTweet);
}
