#ifndef OFXTWITTERSTREAMTWEETH
#define OFXTWITTERSTREAMTWEETH


/*
Representing:
	"contributors": null, 
	"favorited": false, 
	"text": "朝からSystem Of A Down！しかしSOADギター髪の毛昔はあったんだな・・・髪の毛ある時と最近の映像はなんか違う。でもかっこいい。", 
	"in_reply_to_user_id": null, 
	"source": "<a href=\"http://movatwitter.jugem.jp/\" rel=\"nofollow\">www.movatwi.jp</a>", 
	"created_at": "Sat Jun 19 20:25:46 +0000 2010", 
	"coordinates": null, 
	"in_reply_to_screen_name": null, 
	"place": null, 
	"user": {
		"notifications": null, 
		"time_zone": null, 
		"profile_link_color": "0000ff", 
		"url": "http://pr.cgiboy.com/14753859", 
		"profile_background_image_url": "http://s.twimg.com/a/1276197224/images/themes/theme1/bg.png", 
		"statuses_count": 13, 
		"profile_sidebar_fill_color": "e0ff92", 
		"description": "高三女子", 
		"profile_background_tile": false, 
		"contributors_enabled": false, 
		"profile_sidebar_border_color": "87bc44", 
		"lang": "ja", 
		"geo_enabled": false, 
		"created_at": "Sat Apr 24 10:00:30 +0000 2010", 
		"followers_count": 6, 
		"following": null, 
		"friends_count": 38, 
		"protected": false, 
		"profile_image_url": "http://s.twimg.com/a/1276197224/images/default_profile_2_normal.png", 
		"verified": false, 
		"profile_background_color": "9ae4e8", 
		"location": "谷塚駅", 
		"name": "古賀瞳", 
		"favourites_count": 0, 
		"screen_name": "hitomi_ossann", 
		"id": 136584114, 
		"utc_offset": null, 
		"profile_text_color": "000000"
	}, 
	"truncated": false, 
	"id": 16569582600, 
	"geo": null, 
	"in_reply_to_status_id": null
*/

#include <string>
#include <vector>

using namespace std;

/*
 "place": {
        "country_code": "NL",
        "place_type": "city",
        "bounding_box": {
            "type": "Polygon",
            "coordinates": [
                [
                    [5.8955157, 50.8183644],
                    [6.0263774, 50.8183644],
                    [6.0263774, 50.936387],
                    [5.8955157, 50.936387]
                ]
            ]
        },
        "attributes": {},
        "full_name": "Heerlen, Limburg",
        "name": "Heerlen",
        "url": "http:\/\/api.twitter.com\/1\/geo\/id\/fec750e635427c4d.json",
        "id": "fec750e635427c4d",
        "country": "The Netherlands"
    },

*/

struct ofxTwitterCoordinate {
	double x;
	double y;
};

struct ofxTwitterBoundingBox {
	std::string	type;
	std::vector<ofxTwitterCoordinate> coordinates;
};

struct ofxTwitterStreamPlace {
	string country_code;
	string place_type;
	ofxTwitterBoundingBox bounding_box;
	string full_name;
	string name;
	string url;
	string id;
	string country;
};


struct ofxTwitterStreamTweetUser {
	bool notifications;
	string time_zone;
	string profile_link_color;
	string url;
	string profile_background_image_url;
	int statuses_count;
	string profile_sidebar_fill_color;
	string description;
	bool profile_background_tile;
	string lang;
	bool geo_enabled;
	string created_at;
	int followers_count;
	int following;
	int friends_count;
	bool is_protected;
	string profile_image_url;
	bool verified;
	string profile_background_color;
	string location;
	string name;
	int favourites_count;
	string screen_name;
	long id;
	int utc_offset;
	string profile_text_color;
};

struct ofxTwitterStreamTweet {
	ofxTwitterStreamTweet():text(""){}
	int contributors;
	string text;
	bool favorited;
	long in_reply_to_user_id;
	string source;
	string created_at;
	string coordinates;
	string in_reply_to_screen_name;
	ofxTwitterStreamPlace place;
	ofxTwitterStreamTweetUser user;
	bool truncated;
	string id;
	string id_str;
	ofxTwitterCoordinate geo;
	long in_reply_to_status_id;
};
#endif