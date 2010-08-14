#include "ofxTwitterStreamClientJSONThread.h"
#include "ofxTwitterStreamClientJSON.h"

ofxTwitterStreamClientJSONThread::ofxTwitterStreamClientJSONThread(
		boost::asio::io_service& rIOService
		,const string sServer
		,const string sPath
		,const string sUser
		,const string sPassword
):io_service(rIOService)
{
	client = new ofxTwitterStreamClientJSON(rIOService,sServer,sPath,sUser,sPassword);
}

void ofxTwitterStreamClientJSONThread::threadedFunction() {
	client->connect();
	io_service.run();
}


