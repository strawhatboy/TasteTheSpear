#include "GameObjectTypesLoader.h"

CC_SHARED_CREATE_IMPL(GameObjectTypesLoader);

GameObjectTypesLoader::GameObjectTypesLoader(void)
{
	INIT_POINTER(this->m_HeroTypes);


	this->m_HeroTypes = new vector<HeroType*>();
}


GameObjectTypesLoader::~GameObjectTypesLoader(void)
{
}


	bool GameObjectTypesLoader::loadHeroTypes()
	{
		bool bRet = true;
		auto dict = CCDictionary::createWithContentsOfFile(STR_HERO_TYPES_CONFIG_FILE_NAME);
		auto heroArray = dynamic_cast<CCArray*>(dict->objectForKey("heros"));
		CCLog("Got heros array, count: %d", heroArray->count());
		CCObject* obj;
		CCARRAY_FOREACH(heroArray, obj)
		{
			CCDictionary* objDict = dynamic_cast<CCDictionary*>(obj);
			auto heroType = HeroType::createWithDict(objDict);
			this->m_HeroTypes->push_back(heroType);
		}
		return bRet;
	}
	bool GameObjectTypesLoader::loadAbilityTypes()
	{
		bool bRet = true;
		return bRet;
	}
	bool GameObjectTypesLoader::loadAnimationsTypes()
	{
		bool bRet = true;
		return bRet;
	}
	bool GameObjectTypesLoader::loadLevelTypes()
	{
		bool bRet = true;
		return bRet;
	}
	bool GameObjectTypesLoader::loadFightingUnitTypes()
	{
		bool bRet = true;
		return bRet;
	}
	bool GameObjectTypesLoader::loadItemTypes()
	{
		bool bRet = true;
		return bRet;
	}
	
	bool GameObjectTypesLoader::loadAllTypes()
	{
		bool bRet = true;
		return loadHeroTypes() 
			&& loadAbilityTypes() 
			&& loadAnimationsTypes()
			&& loadLevelTypes()
			&& loadFightingUnitTypes()
			&& loadItemTypes();
		return bRet;
	}