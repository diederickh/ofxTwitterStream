#pragma once

#include "ofMain.h"

// Includes for ofxTwitterStream
// ------------------------------
#include "ofxTwitterStream.h"
#include <boost/asio.hpp>

class testApp : public ofBaseApp, ofxTwitterStreamEventListener { // note we implement the twitter event listener.

	public:
		~testApp();
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		
		// ofxTwitterStreamEventListener 
		virtual void onTweet(ofxTwitterStreamTweet& rTweet);
		
		// ofxTwitterStream members
		// ---------------------------
		boost::asio::io_service io_service;		// for network io.
		ofxTwitterStreamClientJSONThread* twitter_thread; // thread into which we receive tweets from (JSON) server.
		
};
