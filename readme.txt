ofxTWitterStream
================

Installation Windows (Code::Blocks)
===================================
- Intall these addons:
* ofxThread
* ofxBoost
* ofxStringEncoders
* ofxJansson
* ofxSQLite
- Project > Build options > Search Paths, add this:
..\..\..\addons_diederick\ofxBoost\src\lib
..\..\..\addons_diederick\ofxStringEncoders\src\lib
..\..\..\addons_diederick\ofxStringEncoders\src\lib\stringencoders
..\..\..\addons\ofxThread\src
..\..\..\addons_diederick\ofxJansson\src
..\..\..\addons_diederick\ofxJansson\src\lib\jansson


- Project > Build Options > Compiler Settings > Defines tab, add:
BOOST_USE_WINDOWS_H
_WIN32_WINNT=0x0502
POCO_NO_UNWINDOWS

(POCO_NO_UNWINDOWS is necessary as boost uses ::CreateEvent)





