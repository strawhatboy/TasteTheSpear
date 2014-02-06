#include "FightingUnitType.h"


FightingUnitType::FightingUnitType(CCDictionary* dict) : GameObjectType(dict)
{
	this->m_Life = dict->valueForKey(STR_FIGHTINGUNIT_LIFE)->floatValue();
	this->m_Attack = dict->valueForKey(STR_FIGHTINGUNIT_ATTACK)->floatValue();
	this->m_Defense = dict->valueForKey(STR_FIGHTINGUNIT_DEFENSE)->floatValue();
	this->m_FireRate = dict->valueForKey(STR_FIGHTINGUNIT_FIRERATE)->floatValue();
	this->m_LifeDelta = dict->valueForKey(STR_FIGHTINGUNIT_LIFE_DELTA)->floatValue();
	this->m_AttackDelta = dict->valueForKey(STR_FIGHTINGUNIT_ATTACK_DELTA)->floatValue();
	this->m_DefenseDelta = dict->valueForKey(STR_FIGHTINGUNIT_DEFENSE_DELTA)->floatValue();
	this->m_FireRateDelta = dict->valueForKey(STR_FIGHTINGUNIT_FIRERATE_DELTA)->floatValue();
	this->m_Abilities = dynamic_cast<CCArray*>(dict->objectForKey(STR_FIGHTINGUNIT_ABILITIES));
}

FightingUnitType::~FightingUnitType(void)
{
}
