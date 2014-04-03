#pragma once
#include "TexturedGameObjectType.h"
#include "LevelType.h"

#define STR_DISTRICT_LEVELS "levels"

class DistrictType :
	public TexturedGameObjectType
{
	CC_SYNTHESIZE_READONLY(vector<LevelType*>*, m_Levels, Levels);

public:
	~DistrictType(void);
	// returns HERO, UNIT, MISSILE, LEVEL, DISTRICT
	virtual string getObjectType(void) const
	{
		return STR_DISTRICT;
	}

	CREATE_WITH_DICT(DistrictType);

	virtual bool loadTexture(
		CCObject* target = NULL,
		SEL_SCHEDULE selector = NULL) const;
};

