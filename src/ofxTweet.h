#pragma once
//include "ofMain.h"
#include <string>
using namespace std;
class ofxTweet {
public: 
	ofxTweet();
	
	inline string getText() 					{ return text; 				}
	inline string getID()	 					{ return id; 				}
	inline string getScreenName()				{ return screen_name;		}
	inline string getAvatar()					{ return avatar; 			}
	inline string getUserID()					{ return user_id; 			}
	
	inline ofxTweet& setText(string sText) 			{ text = sText; 			return *this;}
	inline ofxTweet& setID(string sID) 				{ id = sID; 				return *this;}
	inline ofxTweet& setAvatar(string sURL) 		{ avatar = sURL;			return *this;} 
	inline ofxTweet& setScreenName(string sName) 	{ screen_name = sName;		return *this;}
	inline ofxTweet& setUserID(string sID)			{ user_id = sID;			return *this;}
	
private:	
	string text;
	string id;
	string screen_name;
	string avatar;
	string user_id;
};

/*
A nicely formatted twitter message; 
// --------------------------------
"in_reply_to_status_id_str": "73829792671215616",
    "geo": null,
    "retweet_count": 0,
    "text": "@Cutie4Nkotbsb @DonnieWahlberg I love him to the moon and back!!!...",
    "id_str": "73829941053108224",
    "in_reply_to_screen_name": "Cutie4Nkotbsb",
    "in_reply_to_user_id_str": "21703864",
    "coordinates": null,
    "contributors": null,
    "retweeted": false,
    "created_at": "Thu May 26 19:16:44 +0000 2011",
    "source": "web",
    "truncated": false,
    "entities": {
        "user_mentions": [{
            "indices": [0, 14],
            "screen_name": "Cutie4Nkotbsb",
            "id_str": "21703864",
            "name": "Allison",
            "id": 21703864
        }, {
            "indices": [15, 30],
            "screen_name": "DonnieWahlberg",
            "id_str": "24776235",
            "name": "Donnie Wahlberg",
            "id": 24776235a
        }],
        "urls": [],
        "hashtags": []
    },
    "in_reply_to_user_id": 21703864,
    "place": null,
    "in_reply_to_status_id": 73829792671215616,
    "user": {
        "location": "Louisiana",
        "id_str": "305617428",
        "default_profile": true,
        "profile_text_color": "333333",
        "screen_name": "DdubsbabyBug",
        "is_translator": false,
        "profile_sidebar_fill_color": "DDEEF6",
        "listed_count": 2,
        "notifications": null,
        "profile_background_tile": false,
        "created_at": "Thu May 26 14:32:50 +0000 2011",
        "description": "Donnies baby bug Lola..  from Louisiana figuring out what I want in this world.  Live for tomorrow, hope for today and never miss a chance to say I love you.",
        "show_all_inline_media": false,
        "geo_enabled": false,
        "followers_count": 40,
        "contributors_enabled": false,
        "friends_count": 108,
        "profile_link_color": "0084B4",
        "profile_sidebar_border_color": "C0DEED",
        "default_profile_image": false,
        "lang": "en",
        "statuses_count": 86,
        "time_zone": "Central Time (US & Canada)",
        "protected": false,
        "profile_use_background_image": true,
        "favourites_count": 1,
        "url": null,
        "name": "Lola Venice",
        "verified": false,
        "profile_background_color": "C0DEED",
        "id": 305617428,
        "follow_request_sent": null,
        "following": null,
        "profile_background_image_url": "http:\/\/a0.twimg.com\/images\/themes\/theme1\/bg.png",
        "utc_offset": -21600,
        "profile_image_url": "http:\/\/a3.twimg.com\/profile_images\/1369940852\/2506567-4cda1e4d70e28-full_normal.jpg"
    },
    "id": 73829941053108224,
    "favorited": false

*/