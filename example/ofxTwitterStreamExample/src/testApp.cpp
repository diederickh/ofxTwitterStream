#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	// create the thread in which we listen for new tweets.
	// ----------------------------------------------------
	string filter = "/1/statuses/filter.json?track=love";
	twitter_thread = new ofxTwitterStreamClientJSONThread(
		io_service // the IO for network communication 
		,"stream.twitter.com"  // the streaming twitter server which pushes new tweets.
		,filter // url of messages/filter 
		,"YOUR_TWITTER_USERNAME_HERE"
		,"YOUR_TWITTER_PASSWORD_HERE"
	);
	
	
	// Set the name of this application so the twitter server 
	// knows who we are.
	// -------------------------------------------------------
	twitter_thread->getClient()->setApplicationName("openFrameworks TwitterStream");
	
	// Add us as an event listener so we get notified when new
	// twitter messages are sent from the twitter stream server
	// to our client. (Note that this happens from another 
	// thread).
	twitter_thread->getClient()->addEventListener(this);
	
	// When everything is setup, we can start the thread.
	twitter_thread->start();
}

// Must nicely shutdown...
testApp::~testApp() {
	twitter_thread->stop();
}

void testApp::onTweet(ofxTwitterStreamTweet& rTweet) {
	cout << "From: " << rTweet.user.screen_name << endl;
	cout << "ID: " << rTweet.user.id_str << endl;
	cout << "Message: " << rTweet.text << endl;
	cout << "Geo coords: " << rTweet.coordinates << endl;
	cout << "-------------------------------------------" << endl;
	
}


//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}