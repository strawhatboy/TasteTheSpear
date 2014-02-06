// The runtime fighting unit, can be the hero, the boss, the normal enemy.
#pragma once
#include "cocos2d.h"
#include "myLib.h"
#include "FightingUnitType.h"
#include "GameObject_Runtime.h"


class FightingUnit_Runtime
	: public GameObject_Runtime
{
protected:
	CC_SYNTHESIZE(float, m_Life_Runtime, CurrentLife);
	CC_SYNTHESIZE(float, m_Defense_Runtime, CurrentDefense);
	CC_SYNTHESIZE(float, m_Attack_Runtime, CurrentAttack);
	CC_SYNTHESIZE(float, m_FireRate_Runtime, CurrentFireRate);
	CC_SYNTHESIZE(float, m_Life_Max_Runtime, CurrentMaxLife);
	CC_SYNTHESIZE(int, m_Level, CurrentLevel);
	CCArray* m_Items;
	CCArray* m_Buffs;
	CCArray* m_Abilities;

public:
	FightingUnit_Runtime(void);
	~FightingUnit_Runtime(void);

	virtual bool setLifeWithCountdown(float life, float countdown);

	virtual bool setDefenseWithCountdown(float defense, float countdown);

	virtual bool setAttackWithCountdown(float attack, float countdown);

	virtual bool setFireRateWithCountdown(float fireRate, float countdown);

	virtual bool hasItem(const char* itemID) const;
	virtual bool hasAbility(const char* abilityID) const;
	virtual bool hasBuff(const char* buffID) const;

	virtual bool addItemByID(const char* itemID);
	virtual bool addBuffByID(const char* buffID);
	virtual bool addAbilityByID(const char* abilityID);

	virtual bool removeItemByID(const char* itemID);
	virtual bool removeBuffByID(const char* buffID);
	virtual bool removeAbilityByID(const char* buffID);

	virtual bool isAbilityInCD(const char* abilityID);

	RUNTIME_OBJ_CREATE(FightingUnit_Runtime, FightingUnitType);

};

