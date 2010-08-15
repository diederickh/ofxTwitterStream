#include "ofxTwitterStreamClient.h"
#include "ofxTwitterStreamClientJSON.h"
#include "ofxTwitterStreamClientJSONThread.h"
#include <boost/asio.hpp>

/**
 * Just a helper to include all the necessary files you need to create
 * a ofxTwitterStreamClientJSONThread object which connects to the twitter
 * server and starts listening to tweets.
 *
 * The ofxTwitterStream depends on a couple of addons:
 *
 * - ofxThread				Used to start collecting data in a custom thread
 * - ofxJansson				c-based json parser
 * - ofxAsio				kind of standardized way for networking
 * - ofxBoost				Boost hpp files (necessary for ofxAsio)
 * - ofxStringEncoders		base64 string encoders form the google code
 *							stringencoders lib. You'll find only the
 *							files neccesary to encode base64
 */
