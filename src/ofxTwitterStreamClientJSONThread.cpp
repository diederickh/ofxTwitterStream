#include "ofxTwitterStreamClientJSONThread.h"
#include "ofxTwitterStreamClientJSON.h"


ofxTwitterStreamClientJSONThread::ofxTwitterStreamClientJSONThread(
		boost::asio::io_service& rIOService
		,const string sServer
		,const string sPath
		,const string sUser
		,const string sPassword
):io_service(rIOService)
,is_stopped(true)
{
	client = new ofxTwitterStreamClientJSON(rIOService,sServer,sPath,sUser,sPassword);
}

void ofxTwitterStreamClientJSONThread::threadedFunction() {
	client->connect();
	io_service.run();
}

void ofxTwitterStreamClientJSONThread::stop() {
	if(is_stopped)
		return; // already stopped.
	is_stopped = true;
	client->disconnect();
	thread_ptr->join();
}

ofxTwitterStreamClientJSONThread::~ofxTwitterStreamClientJSONThread() {
	stop();
	delete client;
}

void ofxTwitterStreamClientJSONThread::start() {
	if(!is_stopped) 
		return;
	is_stopped = false;
	thread_ptr = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(
		&ofxTwitterStreamClientJSONThread::threadedFunction, this))
	);
}


ofxTwitterStreamClientJSON* ofxTwitterStreamClientJSONThread::getClient() {
	return client;
}