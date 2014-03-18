#pragma once

#include "myLib.h"
#include "cocos2d.h"

class UserDefaultUtils
{
public:
	//UserDefaultUtils(void);
	~UserDefaultUtils(void);

	bool isUserDefaultInitialized();
	bool isFirstRun();
	void setFirstRun(bool isFirstRun);

	int getHeroLevel(const char* ID);
	void setHeroLevel(const char* ID, int level);
	bool isDistrictUnlocked(const char* ID);
	bool isLevelUnlocked(const char* ID);
	void setDistrictUnlocked(const char* ID, bool value);
	void setLevelUnlocked(const char* ID, bool value);
	void setLevelHighScore(const char* ID, int score);
	void setLevelHighScoreUsername(const char* ID, const char* username);
	void setLevelHighScoreDate(const char* ID, struct tm* time);
	int getLevelHighScore(const char* ID);
	string getLevelHighScoreUsername(const char* ID);
	struct tm getLevelHighScoreDate(const char* ID);

	// returns the ID.
	string getLastUsedHero();
	void setLastUsedHero(const char* ID);

	CC_SHARED_CREATE_FUNC(UserDefaultUtils);
};

