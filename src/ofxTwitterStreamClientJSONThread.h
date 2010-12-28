#ifndef OFXTWITTERSTREAMCLIENTTHREADH
#define OFXTWITTERSTREAMCLIENTTHREADH

#undef check  // need to do this else boost won't compile on mac
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <string>

using namespace std;
class ofxTwitterStreamClientJSON;

class ofxTwitterStreamClientJSONThread {
public:
	ofxTwitterStreamClientJSONThread(
		boost::asio::io_service& rIOService
		,const string sServer
		,const string sPath
		,const string sUser
		,const string sPassword
	);
	~ofxTwitterStreamClientJSONThread();
	void start();
	void stop();
	
	
	// Get the client which connects to the twitter server.
	ofxTwitterStreamClientJSON* getClient();
protected:
	bool is_stopped;
	virtual void threadedFunction();
	ofxTwitterStreamClientJSON* client;
	boost::asio::io_service& io_service;
	boost::shared_ptr<boost::thread> thread_ptr;
};
#endif
