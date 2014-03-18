#include "UserDefaultUtils.h"

#define LOAD_INT CCUserDefault::sharedUserDefault()->getIntegerForKey
#define LOAD_BOOL CCUserDefault::sharedUserDefault()->getBoolForKey
#define LOAD_FLOAT CCUserDefault::sharedUserDefault()->getFloatForKey
#define LOAD_DOUBLE CCUserDefault::sharedUserDefault()->getDoubleForKey
#define LOAD_STRING CCUserDefault::sharedUserDefault()->getStringForKey

#define SAVE_INT CCUserDefault::sharedUserDefault()->setIntegerForKey
#define SAVE_BOOL CCUserDefault::sharedUserDefault()->setBoolForKey
#define SAVE_FLOAT CCUserDefault::sharedUserDefault()->setFloatForKey
#define SAVE_DOUBLE CCUserDefault::sharedUserDefault()->setDoubleForKey
#define SAVE_STRING CCUserDefault::sharedUserDefault()->setStringForKey

CC_SHARED_CREATE_IMPL(UserDefaultUtils);

UserDefaultUtils::UserDefaultUtils(void)
{
}


UserDefaultUtils::~UserDefaultUtils(void)
{
}

bool UserDefaultUtils::isUserDefaultInitialized()
{
	if (LOAD_BOOL("FIRST_LOAD") == false)
	{
		SAVE_BOOL("FIRST_LOAD", true);
		return false;
	}

	return true;
}

bool UserDefaultUtils::isFirstRun()
{
	return LOAD_BOOL("FIRST_RUN");
}

void UserDefaultUtils::setFirstRun(bool isFirstRun)
{
	SAVE_BOOL("FIRST_RUN", isFirstRun);
}

int UserDefaultUtils::getHeroLevel(const char* ID)
{
	return LOAD_INT(CCString::createWithFormat("%s_LEVEL", ID)->getCString());
}

void UserDefaultUtils::setHeroLevel(const char* ID, int level)
{
	SAVE_INT(CCString::createWithFormat("%s_LEVEL", ID)->getCString(), level);
}

bool UserDefaultUtils::isDistrictUnlocked(const char* ID)
{
	return !LOAD_BOOL(CCString::createWithFormat("%s_LOCKED", ID)->getCString());
}

bool UserDefaultUtils::isLevelUnlocked(const char* ID)
{
	return !LOAD_BOOL(CCString::createWithFormat("%s_LOCKED", ID)->getCString());
}

void UserDefaultUtils::setDistrictUnlocked(const char* ID, bool value)
{
	SAVE_BOOL(CCString::createWithFormat("%s_LOCKED", ID)->getCString(), !value);
}

void UserDefaultUtils::setLevelUnlocked(const char* ID, bool value)
{
	SAVE_BOOL(CCString::createWithFormat("%s_LOCKED", ID)->getCString(), !value);
}

void UserDefaultUtils::setLevelHighScore(const char* ID, int score)
{
	SAVE_INT(CCString::createWithFormat("%s_HIGHSCORE", ID)->getCString(), score);
}

void UserDefaultUtils::setLevelHighScoreUsername(const char* ID, const char* username)
{
	SAVE_STRING(CCString::createWithFormat("%s_HIGHSCORE_USR", ID)->getCString(), string(username));
}

void UserDefaultUtils::setLevelHighScoreDate(const char* ID, struct tm* date)
{
	SAVE_STRING(CCString::createWithFormat("%s_HIGHSCORE_DATE_SEC", ID)->getCString(), 
		CCString::createWithFormat("%d", date->tm_sec)->getCString());
	SAVE_STRING(CCString::createWithFormat("%s_HIGHSCORE_DATE_MIN", ID)->getCString(), 
		CCString::createWithFormat("%d", date->tm_min)->getCString());
	SAVE_STRING(CCString::createWithFormat("%s_HIGHSCORE_DATE_HOUR", ID)->getCString(), 
		CCString::createWithFormat("%d", date->tm_hour)->getCString());
	SAVE_STRING(CCString::createWithFormat("%s_HIGHSCORE_DATE_DAY", ID)->getCString(), 
		CCString::createWithFormat("%d", date->tm_mday)->getCString());
	SAVE_STRING(CCString::createWithFormat("%s_HIGHSCORE_DATE_MON", ID)->getCString(), 
		CCString::createWithFormat("%d", date->tm_mon)->getCString());
	SAVE_STRING(CCString::createWithFormat("%s_HIGHSCORE_DATE_YEAR", ID)->getCString(), 
		CCString::createWithFormat("%d", date->tm_year)->getCString());
}

int UserDefaultUtils::getLevelHighScore(const char* ID)
{
	return LOAD_INT(CCString::createWithFormat("%s_HIGHSCORE", ID)->getCString());
}

string UserDefaultUtils::getLevelHighScoreUsername(const char* ID)
{
	return LOAD_STRING(CCString::createWithFormat("%s_HIGHSCORE_USR", ID)->getCString());
}

struct tm UserDefaultUtils::getLevelHighScoreDate(const char* ID)
{
	struct tm time;
	time.tm_sec = CCString::create(LOAD_STRING(CCString::createWithFormat("%s_HIGHSCORE_DATE_SEC", ID)->getCString()))->intValue();
	time.tm_min = CCString::create(LOAD_STRING(CCString::createWithFormat("%s_HIGHSCORE_DATE_MIN", ID)->getCString()))->intValue();
	time.tm_hour = CCString::create(LOAD_STRING(CCString::createWithFormat("%s_HIGHSCORE_DATE_HOUR", ID)->getCString()))->intValue();
	time.tm_mday = CCString::create(LOAD_STRING(CCString::createWithFormat("%s_HIGHSCORE_DATE_DAY", ID)->getCString()))->intValue();
	time.tm_mon = CCString::create(LOAD_STRING(CCString::createWithFormat("%s_HIGHSCORE_DATE_MON", ID)->getCString()))->intValue();
	time.tm_year = CCString::create(LOAD_STRING(CCString::createWithFormat("%s_HIGHSCORE_DATE_YEAR", ID)->getCString()))->intValue();
	return time;
}

string UserDefaultUtils::getLastUsedHero()
{
	return LOAD_STRING("HERO_LAST_USED");
}

void UserDefaultUtils::setLastUsedHero(const char* ID)
{
	SAVE_STRING("HERO_LAST_USED", string(ID));
}