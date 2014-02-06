#pragma once

#include "myLib.h"
#include "HeroType.h"
#include "FightingUnitType.h"
#include "MissileType.h"

#define STR_HERO_TYPES_CONFIG_FILE_NAME "hero_config.plist"

class GameObjectTypesLoader
{
private:
	vector<HeroType*>* m_HeroTypes;
	vector<FightingUnitType*>* m_FightingUnitTypes;
	vector<MissileType*>* m_MissileTypes;
	
	bool loadHeroTypes();
	bool loadAbilityTypes();
	bool loadAnimationsTypes();
	bool loadLevelTypes();
	bool loadFightingUnitTypes();
	bool loadItemTypes();

public:
	~GameObjectTypesLoader(void);
	bool loadAllTypes();
	
	CC_SHARED_CREATE_FUNC(GameObjectTypesLoader);
};

