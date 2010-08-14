#include "ofxTwitterStreamSQLiteListener.h"

ofxTwitterStreamSQLiteListener::ofxTwitterStreamSQLiteListener(
	std::string sDBName
):sqlite(sDBName)
{
	createDB();
}

void ofxTwitterStreamSQLiteListener::createDB() {
	if (SQLITE_OK != sqlite.simpleQuery(""\
		"CREATE TABLE IF NOT EXISTS  tweets( " \
			" id INTEGER PRIMARY KEY AUTOINCREMENT" \
			",text VARCHAR(150)" \
			",screen_name VARCHAR(30)" \
			",profile_image_url VARCHAR(200)" \
			",date_used DATETIME" \
			",created_at DATETIME" \
			",date_inserted DATETIME DEFAULT CURRENT_TIMESTAMP" \
		");"
	)) {
		cout << "ERROR CREATING TWEET TABLE\n";
	}
}


void ofxTwitterStreamSQLiteListener::onTweet(ofxTwitterStreamTweet &rTweet) {
	if(rTweet.text == "")
		return;
	
	int result = sqlite.insert("tweets")
			.use("text", rTweet.text)
			.use("screen_name",rTweet.user.screen_name)
			.use("profile_image_url", rTweet.user.profile_image_url)
			.use("created_at", rTweet.created_at)
		.execute();	
	if(result != SQLITE_OK) {
		std::cout << "ERROR: cannot insert tweet: " << rTweet.text << std::endl;
	}
}


ofxTwitterStreamTweet ofxTwitterStreamSQLiteListener::getNextTweet() {
	ofxSQLiteSelect sel = sqlite.select("text, id")
		.from("tweets")
		.whereNull("date_used")
		.limit(1)
		.order("date_inserted", "asc")
		.execute().begin();
	ofxTwitterStreamTweet tweet;
	tweet.text = sel.getString();
	tweet.id = sel.getString();
	return tweet;
}

void ofxTwitterStreamSQLiteListener::markTweetAsUsed(std::string nID) {
	sqlite.update("tweets")
		.use("date_used", ofxSQLiteTypeNow())
		.where("id", nID)
		.execute();
}