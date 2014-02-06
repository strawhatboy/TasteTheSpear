#pragma once
#include "gameobjecttype.h"

#define STR_FIGHTINGUNIT_LIFE "life"
#define STR_FIGHTINGUNIT_ATTACK "attack"
#define STR_FIGHTINGUNIT_DEFENSE "defense"
#define STR_FIGHTINGUNIT_FIRERATE "fireRate"
#define STR_FIGHTINGUNIT_ABILITIES "abilities"

#define STR_FIGHTINGUNIT_LIFE_DELTA "lifeDelta"
#define STR_FIGHTINGUNIT_ATTACK_DELTA "attackDelta"
#define STR_FIGHTINGUNIT_DEFENSE_DELTA "defenseDelta"
#define STR_FIGHTINGUNIT_FIRERATE_DELTA "fireRateDelta"

class FightingUnitType :
	public GameObjectType
{
	CC_SYNTHESIZE_READONLY(float, m_Life, Life);
	CC_SYNTHESIZE_READONLY(float, m_Attack, Attack);
	CC_SYNTHESIZE_READONLY(float, m_Defense, Defense);
	CC_SYNTHESIZE_READONLY(float, m_FireRate, FireRate);
	//CC_SYNTHESIZE(float, m_Damage, Damage);
	CC_SYNTHESIZE_READONLY(CCArray*, m_Abilities, Abilities);

	CC_SYNTHESIZE_READONLY(float, m_LifeDelta, LifeDelta);
	CC_SYNTHESIZE_READONLY(float, m_AttackDelta, AttackDelta);
	CC_SYNTHESIZE_READONLY(float, m_DefenseDelta, DefenseDelta);
	CC_SYNTHESIZE_READONLY(float, m_FireRateDelta, FireRateDelta);

public:
	~FightingUnitType(void);
	
	// returns HERO, UNIT, MISSILE, BOSS
	virtual const char* getObjectType(void) const
	{
		return STR_FIGHTINGUNIT;
	}

	CREATE_WITH_DICT(FightingUnitType);
};

