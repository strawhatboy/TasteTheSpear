#include "HeroType.h"


HeroType::~HeroType(void)
{
}

HeroType::HeroType(CCDictionary* dict) : FightingUnitType(dict)
{
	this->m_nHandling = dict->valueForKey(STR_HERO_HANDLING)->intValue();
}