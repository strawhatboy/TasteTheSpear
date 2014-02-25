#pragma once
#include "cocos2d.h"
#include "FightingUnitType.h"

USING_NS_CC;

#define STR_HERO_HANDLING "handling"

class HeroType
	: public FightingUnitType
{
	CC_SYNTHESIZE_READONLY(int, m_nHandling, Handling);

public:
	~HeroType(void);
	
	// returns HERO, UNIT, MISSILE, LEVEL, DISTRICT
	virtual const char* getObjectType(void) const
	{
		return STR_HERO;
	}

	CREATE_WITH_DICT(HeroType);
};

