#include "FightingUnit_Runtime.h"


FightingUnit_Runtime::FightingUnit_Runtime(void)
{
}


FightingUnit_Runtime::~FightingUnit_Runtime(void)
{
}

	bool FightingUnit_Runtime::setLifeWithCountdown(float life, float countdown)
	{
		return true;
	}
	bool FightingUnit_Runtime::setDefenseWithCountdown(float defense, float countdown)
	{
		return true;
	}
	bool FightingUnit_Runtime::setAttackWithCountdown(float attack, float countdown)
	{
		return true;
	}
	bool FightingUnit_Runtime::setFireRateWithCountdown(float fireRate, float countdown)
	{
		return true;
	}

	bool FightingUnit_Runtime::hasItem(const char* itemID) const
	{
		return true;
	}
	bool FightingUnit_Runtime::hasAbility(const char* abilityID) const
	{
		return true;
	}
	bool FightingUnit_Runtime::hasBuff(const char* buffID) const
	{
		return true;
	}
		 
	bool FightingUnit_Runtime::addItemByID(const char* itemID)
	{
		return true;
	}
	bool FightingUnit_Runtime::addBuffByID(const char* buffID)
	{
		return true;
	}
	bool FightingUnit_Runtime::addAbilityByID(const char* abilityID)
	{
		return true;
	}
		 
	bool FightingUnit_Runtime::removeItemByID(const char* itemID)
	{
		return true;
	}
	bool FightingUnit_Runtime::removeBuffByID(const char* buffID)
	{
		return true;
	}
	bool FightingUnit_Runtime::removeAbilityByID(const char* buffID)
	{
		return true;
	}
		 
	bool FightingUnit_Runtime::isAbilityInCD(const char* abilityID)
	{
		return true;
	}