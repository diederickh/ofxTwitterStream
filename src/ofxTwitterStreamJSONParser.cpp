#include "ofxTwitterStreamJSONParser.h"


ofxTwitterStreamJSONParser::ofxTwitterStreamJSONParser(bool bLog)
:log(bLog)
{
}

void ofxTwitterStreamJSONParser::onTweet(ofxTwitterStreamTweetRaw &rTweet) {
	// construct the parser: whenever a message has a carriage return
	// the twitter streaming api breaks!
	json_error_t error;
	json_t *root = json_loads(rTweet.data.c_str(),&error);
	if(!root) {
		
		cout	<< "ERROR: Cannot load json from string at line: << "
				<< error.line
				<< ", "
				<< error.text
				<< "\n";
		//std::cout << "JSON STRING IS" <<std::endl;
		//std::cout << rTweet.data << std::endl;
		return;
	}
	//std::cout << rTweet.data << std::endl;
	// Create and fill the ofxTwitterStreamTweet.
	// ------------------------------------------
	
	// Get the tweet ID.
	ofxTwitterStreamTweet tweet;
	stringstream id_stream;
	id_stream << json.getValueS(root, "id_str", "0");
	uint64_t tweet_id;
	id_stream >> tweet_id;

	tweet.id					= tweet_id;
	tweet.id_str				= json.getValueS(root, "id_str", ""); 
	tweet.text					= json.getValueS(root, "text", "");
	tweet.favorited				= json.getValueB(root, "favorited", false);
	tweet.contributors			= json.getValueI(root, "contributors",0);
	tweet.in_reply_to_user_id	= json.getValueI(root, "in_reply_to_user_id", 0);
	tweet.created_at			= json.getValueS(root, "created_at","0");
	
	json_t* geo = json_object_get(root, "geo");
	if(json_is_object(geo)) {
		json_t* geo_coords = json_object_get(geo, "coordinates");
		if(json_is_array(geo_coords)) {
			// interesting: http://dev.twitter.com/doc/get/geo/reverse_geocode
			if(json_array_size(geo_coords) == 2) {
				json_t* lng_json = json_array_get(geo_coords,0);
				json_t* lat_json = json_array_get(geo_coords,1);
				tweet.geo.x = json_real_value(lng_json);
				tweet.geo.y = json_real_value(lat_json);
				
				if(log) {
					std::cout << "longitude:" << tweet.geo.x << std::endl;
					std::cout << "latitude: " << tweet.geo.y << std::endl;
				}
			}
		} 
	}

	if(log) {
		std::cout << "id: " << tweet.id_str << std::endl;
		std::cout << "text: " << tweet.text << std::endl;
		std::cout << "created_at: " << tweet.created_at << std::endl;
	}
	
	// Get entities
	json_t* entities = json_object_get(root, "entities");
	if(json_is_object(entities)) {
		json_t* urls = json_object_get(entities, "urls");
		if(json_is_array(urls)) {
			int size = json_array_size(urls);
			for(int i = 0; i < size; ++i) {
				json_t* url_entry = json_array_get(urls, i);
				std::string the_url = json.getValueS(url_entry, "url","");
				if(the_url != "") {
					tweet.entities.urls.add(the_url);
				}
			}
		}
	}
	/*
	  "entities": {
        "hashtags": [{
            "text": "Leidsemarkt",
            "indices": [101, 113]
        },
        {
            "text": "kerstboodschappen",
            "indices": [121, 139]
        }],
        "user_mentions": [],
        "urls": [{
            "indices": [46, 71],
            "expanded_url": null,
            "url": "http:\/\/twitpic.com\/3j58a2"
        }],

    },

	*/
	
	// Get user specific data.
	json_t* user = json_object_get(root, "user");
	if(json_is_object(user)) {
		tweet.user.profile_image_url	= json.getValueS(user, "profile_image_url","");
		tweet.user.screen_name			= json.getValueS(user, "screen_name","");
		tweet.user.geo_enabled			= json.getValueB(user, "geo_enabled",false);
		tweet.user.lang					= json.getValueS(user, "lang", "");
		tweet.user.time_zone			= json.getValueS(user, "time_zone","");
		tweet.user.utc_offset			= json.getValueI(user, "utc_offset",0);
		tweet.user.id_str				= json.getValueS(user, "id_str","-1");
	}
		
	// Get place information.
	json_t* place = json_object_get(root, "place");
	if(json_is_object(place)) {
		tweet.place.country_code = json.getValueS(place, "country_code",	"");
		tweet.place.place_type   = json.getValueS(place, "place_type",		"");
		tweet.place.full_name	 = json.getValueS(place, "full_name",		"");
		tweet.place.name		 = json.getValueS(place, "name",			"");
		tweet.place.id			 = json.getValueS(place, "id",				"");
		tweet.place.url			 = json.getValueS(place, "url",				"");
		tweet.place.id			 = json.getValueS(place, "id",				"");
		tweet.place.country		 = json.getValueS(place, "country",			"");
		tweet.place.place_type	 = json.getValueS(place, "place_type",		"");				
		
		if(log) {
			std::cout << "place: " << tweet.place.name << std::endl;
			std::cout << "raw:\n" << rTweet.data << std::endl;
		}

		// Parse the bouding box.
		ofxTwitterBoundingBox box;
		json_t* bounding_box = json_object_get(place, "bounding_box");
		if(json_is_object(bounding_box)) {


			json_t* coordinates = json_object_get(bounding_box, "coordinates");
			if(json_is_array(coordinates)) {
				unsigned int num_coord_groups = json_array_size(coordinates);
				for(int i = 0; i < num_coord_groups; ++i) {
					json_t* points = json_array_get(coordinates,i);
					if(json_is_array(points)) {
						unsigned int points_size = json_array_size(points);
						for(int j = 0; j < points_size; ++j) {
							json_t* point = json_array_get(points, j);
							unsigned int coord_size = json_array_size(point);
							if(coord_size == 2) {
								ofxTwitterCoordinate twitter_coord;
								twitter_coord.x = json_real_value(json_array_get(point,0));
								twitter_coord.y = json_real_value(json_array_get(point,1));
								tweet.place.bounding_box.coordinates.push_back(twitter_coord);
							}
						}
					}
				}
			}
		}
		
	}
	client->notifyTweet(tweet);
	json_decref(root);
	if(log)
		std::cout << "--------------------------------------" << std::endl;
}

// Format spec: http://dev.twitter.com/pages/tweet_entities


/* Example data
--------------------------------------------------------------------------------------------------------------------
{
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
}


{
    "id_str": "15880683964604416",
    "in_reply_to_screen_name": null,
    "in_reply_to_user_id": null,
    "text": "Wietse Havenaar liep door de bos en chillde hem hard, hij flikkerde met zijn face in de sneeuw en stierf.",
    "in_reply_to_status_id_str": null,
    "contributors": null,
    "retweet_count": 0,
    "in_reply_to_user_id_str": null,
    
	 "entities": {
        "hashtags": [{
            "text": "Leidsemarkt",
            "indices": [101, 113]
        },
        {
            "text": "kerstboodschappen",
            "indices": [121, 139]
        }],
        "user_mentions": [],
        "urls": []
    },
    "coordinates": {
        "type": "Point",
        "coordinates": [4.477062, 52.128959]
    },
    , "entities": {
        "user_mentions": [],
        "urls": [{
            "indices": [46, 71],
            "expanded_url": null,
            "url": "http:\/\/twitpic.com\/3j58a2"
        }],
        "hashtags": []
    },
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
    "retweeted": false,
    "source": "web",
    "in_reply_to_status_id": null,
    "truncated": false,
    "geo": null,
    "user": {
        "id_str": "165016961",
        "follow_request_sent": null,
        "lang": "en",
        "profile_use_background_image": true,
        "statuses_count": 1711,
        "following": null,
        "profile_background_color": "000000",
        "profile_background_image_url": "http:\/\/a0.twimg.com\/profile_background_images\/178525836\/bannerfans_8776648.jpg",
        "description": "I'm a dutch mc from The Lyric Collectors. \r\n\r\nwww.thelyriccollectors.hyves.nl support us yaw!",
        "listed_count": 2,
        "location": "Heerlen (Park City)",
        "profile_text_color": "871f1f",
        "followers_count": 85,
        "verified": false,
        "favourites_count": 1,
        "profile_sidebar_fill_color": "000000",
        "profile_image_url": "http:\/\/a1.twimg.com\/profile_images\/1188250502\/Rugged__nd_Raw_normal.jpg",
        "profile_background_tile": false,
        "time_zone": "Amsterdam",
        "friends_count": 48,
        "protected": false,
        "is_translator": false,
        "show_all_inline_media": false,
        "geo_enabled": true,
        "url": "http:\/\/www.kd045.hyves.nl",
        "screen_name": "DamiannTLC",
        "name": "Damiann.",
        "contributors_enabled": false,
        "created_at": "Sat Jul 10 10:43:00 +0000 2010",
        "profile_link_color": "871f1f",
        "id": 165016961,
        "notifications": null,
        "utc_offset": 3600,
        "profile_sidebar_border_color": "871f1f"
    },
    "favorited": false,
    "id": 15880683964604416,
    "created_at": "Fri Dec 17 21:27:04 +0000 2010"
}

#include <string>
using namespace std;


struct ofxTwitterBoundingBox {
	std::string	type;
	std::map<float, float> coordinates;
};

struct ofxTwitterStreamPlace {
	string country_code;
	string place_type;
	ofxTwitterBoundingBox bounding_box;
	string full_name;
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
	string text;
	bool favorited;
	long in_reply_of_user_id;
	string source;
	string created_at;
	string coordinates;
	string in_reply_to_screen_name;
	string place;
	ofxTwitterStreamTweetUser user;
	bool truncated;
	long id;
	string geo;
	long in_reply_to_status_id;
};
--------------------------------------------------------------------------------------------------------------------
*/
