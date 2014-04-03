#include "GameObjectTypesLoader.h"

CC_SHARED_CREATE_IMPL(GameObjectTypesLoader);

#define __CREATE_OBJTYPE_ARRAYS(__V_OBJTYPE__) \
	__V_OBJTYPE__ = CCDictionary::create();\
	__V_OBJTYPE__->retain();

GameObjectTypesLoader::GameObjectTypesLoader(void)
{
	INIT_POINTER(this->m_HeroTypes);
	INIT_POINTER(this->m_FightingUnitTypes);
	INIT_POINTER(this->m_MissileTypes);
	INIT_POINTER(this->m_DistrictTypes);
	INIT_POINTER(this->m_TextureTypes);
	INIT_POINTER(this->m_Armatures);
	INIT_POINTER(this->m_StringResources);
	INIT_POINTER(this->m_Abilities);
	INIT_POINTER(this->m_Frames);

	__CREATE_OBJTYPE_ARRAYS(this->m_HeroTypes);
	__CREATE_OBJTYPE_ARRAYS(this->m_FightingUnitTypes);
	__CREATE_OBJTYPE_ARRAYS(this->m_MissileTypes);
	__CREATE_OBJTYPE_ARRAYS(this->m_DistrictTypes);
	__CREATE_OBJTYPE_ARRAYS(this->m_TextureTypes);
	__CREATE_OBJTYPE_ARRAYS(this->m_Armatures);
	__CREATE_OBJTYPE_ARRAYS(this->m_StringResources);
	__CREATE_OBJTYPE_ARRAYS(this->m_Abilities);
	__CREATE_OBJTYPE_ARRAYS(this->m_Frames);
}

GameObjectTypesLoader::~GameObjectTypesLoader(void)
{
	//DELETE_CPP_ARRAY(this->m_FightingUnitTypes, FightingUnitType);
	//DELETE_CPP_ARRAY(this->m_HeroTypes, HeroType);
	//DELETE_CPP_ARRAY(this->m_MissileTypes, MissileType);
	//DELETE_CPP_ARRAY(this->m_DistrictTypes, DistrictType);

	this->m_HeroTypes->release();
	this->m_FightingUnitTypes->release();
	this->m_MissileTypes->release();
	this->m_DistrictTypes->release();
	this->m_TextureTypes->release();
	this->m_Armatures->release();
	this->m_StringResources->release();
	this->m_Abilities->release();
	this->m_Frames->release();
}

// Macros are bad !!!
#define LOAD_CONFIG_FILE(__FILE_NAME__, __FIRST_KEY_NAME__, __TYPE__, __LOCAL_ARRAY__)\
		auto dict = CCDictionary::createWithContentsOfFile(__FILE_NAME__);\
		if (dict == NULL)\
			return false;\
		auto _array = dynamic_cast<CCArray*>(dict->objectForKey(__FIRST_KEY_NAME__));\
		CCLog("Got %s array, count: %d", __FIRST_KEY_NAME__, _array->count());\
		CCObject* obj;\
		CCARRAY_FOREACH(_array, obj)\
		{\
			CCDictionary* objDict = dynamic_cast<CCDictionary*>(obj);\
			if (objDict != NULL)\
			{\
				auto _type = __TYPE__::createWithDict(objDict);\
				__LOCAL_ARRAY__->push_back(_type);\
			}\
		}\
		return true;

	//template <class T>
	//bool GameObjectTypesLoader::loadTypeFromFile(const char* pszFileName, const char* pszFirstKeyName, vector<T*>* &result)
	//{
	//	static_assert(is_base_of<GameObjectType, T>::value, "T Should be typeof GameObjectType");
	//	auto dict = CCDictionary::createWithContentsOfFile(pszFileName);
	//	if (dict == NULL)
	//		return false;
	//	auto _array = dynamic_cast<CCArray*>(dict->objectForKey(pszFirstKeyName));
	//	CCLog("Got %s array, count: %d", pszFirstKeyName, _array->count());
	//	CCObject* obj;
	//	CCARRAY_FOREACH(_array, obj)
	//	{
	//		CCDictionary* objDict = dynamic_cast<CCDictionary*>(obj);
	//		if (objDict != NULL)
	//		{
	//			auto _type = T::createWithDict(objDict);
	//			result->push_back(_type);
	//		}
	//	}
	//	return true;
	//}

	template <class T>
	bool GameObjectTypesLoader::loadTypeFromFile(
		const char* pszFileName, 
		const char* pszFirstKeyName, 
		CCDictionary* result)
	{
		static_assert(is_base_of<GameObjectType, T>::value, "T Should be typeof GameObjectType");

		bool bRet = false;
		do 
		{
			auto dict = CCDictionary::createWithContentsOfFile(pszFileName);
			CC_BREAK_IF(!dict);
			auto _array = dynamic_cast<CCArray*>(dict->objectForKey(pszFirstKeyName));
			CC_BREAK_IF(!_array);
			CCLog("Got %s array, count: %d", pszFirstKeyName, _array->count());
			CCObject* obj;
			CCARRAY_FOREACH(_array, obj)
			{
				CCDictionary* objDict = dynamic_cast<CCDictionary*>(obj);
				if (objDict != NULL)
				{
					auto _typeObj = T::createWithDict(objDict);
					result->setObject(_typeObj, _typeObj->getTypeID());
				}
			}

			bRet = true;
		} while (false);
		return bRet;
	}

	bool GameObjectTypesLoader::loadHeroTypes()
	{
		return loadTypeFromFile<HeroType>(STR_HERO_TYPES_CONFIG_FILE_NAME, "heros", this->m_HeroTypes);
		//LOAD_CONFIG_FILE(STR_HERO_TYPES_CONFIG_FILE_NAME, "heros", HeroType, this->m_HeroTypes);
	}
	bool GameObjectTypesLoader::loadAbilityTypes()
	{
		return loadTypeFromFile<AbilityType>(STR_ABILITY_TYPES_CONFIG_FILE_NAME, "abilities", this->m_Abilities);
	}
	bool GameObjectTypesLoader::loadAnimationsTypes()
	{
		bool bRet = true;
		return bRet;
	}
	bool GameObjectTypesLoader::loadLevelTypes()
	{
		return loadTypeFromFile<DistrictType>(STR_LEVEL_TYPES_CONFIG_FILE_NAME, "districts", this->m_DistrictTypes);
		//LOAD_CONFIG_FILE(STR_LEVEL_TYPES_CONFIG_FILE_NAME, "districts", DistrictType, this->m_DistrictTypes);
		return true;
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

	bool GameObjectTypesLoader::loadTextureTypes()
	{
		return loadTypeFromFile<TextureType>(STR_TEXTURE_TYPES_CONFIG_FILE_NAME, "textures", this->m_TextureTypes);
	}

	bool GameObjectTypesLoader::loadStringResourceTypes()
	{
		return loadTypeFromFile<StringResourceType>(STR_STRINGRESOURCE_TYPES_CONFIG_FILE_NAME, "stringResources", this->m_StringResources);
	}
	
	
	int GameObjectTypesLoader::loadArmaturesWithDict_Common(const CCDictionary* dict,
		CCObject* target = NULL,
		SEL_SCHEDULE selector = NULL)
	{
		CCLog("armatures' count before: %d", this->m_Armatures->count());
		CCDictElement* el = NULL;
		CCDICT_FOREACH(dict, el)
		{
			auto _type = dynamic_cast<TexturedGameObjectType*>(el->getObject());
			if (_type != NULL)
			{
				//auto id = _type->getTypeID();
				//if (strlen(getArmatureNameByID(id.c_str())) == 0)
				//{//There's no such armature available in the dict, so add it. otherwise skip it.
				//	auto _t_type = getTextureTypeByID(_type->getTexture().c_str());
				//	if (_t_type != NULL)
				//	{
				//		auto name = _t_type->getName();
				//		auto json = _t_type->getExportJson();
				//		auto png = _t_type->getExportPNG();
				//		auto plist = _t_type->getExportPlist();
				//		if (selector != NULL)
				//			CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(
				//				png.c_str(),
				//				plist.c_str(),
				//				json.c_str(),
				//				target,
				//				selector);
				//		else
				//			CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
				//				png.c_str(),
				//				plist.c_str(),
				//				json.c_str());

				//		//CCArmature* armature = CCArmature::create(name.c_str());
				//		this->m_Armatures->setObject(CCString::create(name), id);
				//		count++;
				//	}
				//}
				string name;
				_type->loadTexture(target, selector);
			}
		}
		CCLog("armatures' count: %d", this->m_Armatures->count());
		return 1;
	}

	int GameObjectTypesLoader::loadArmaturesWithDict(const CCDictionary* dict)
	{
		return loadArmaturesWithDict_Common(dict);
	}

	int GameObjectTypesLoader::loadArmaturesWithDictAsync(const CCDictionary* dict, CCObject* target, SEL_SCHEDULE selector)
	{
		return loadArmaturesWithDict_Common(dict, target, selector);
	}
	


	int GameObjectTypesLoader::loadArmatures()
	{
		auto wtf = this->loadArmaturesWithDict(this->m_DistrictTypes)
			+ this->loadArmaturesWithDict(this->m_FightingUnitTypes)
			+ this->loadArmaturesWithDict(this->m_HeroTypes)
			+ this->loadArmaturesWithDict(this->m_MissileTypes)
			;

		return loadArmaturesFromTextureConfig();
	}

	int GameObjectTypesLoader::loadArmaturesAsync(CCObject* target, SEL_SCHEDULE selector)
	{
		auto wtf = this->loadArmaturesWithDictAsync(this->m_DistrictTypes, target, selector)
			+ this->loadArmaturesWithDictAsync(this->m_FightingUnitTypes, target, selector)
			+ this->loadArmaturesWithDictAsync(this->m_HeroTypes, target, selector)
			+ this->loadArmaturesWithDictAsync(this->m_MissileTypes, target, selector)
			;
		return loadArmaturesFromTextureConfigAsync(target, selector);
	}
	
	bool GameObjectTypesLoader::loadAllTypes()
	{
		bool bRet = true;
		return loadHeroTypes() 
			&& loadAbilityTypes() 
			&& loadAnimationsTypes()
			&& loadLevelTypes()
			&& loadFightingUnitTypes()
			&& loadItemTypes()
			&& loadTextureTypes()
			&& loadStringResourceTypes();
		return bRet;
	}

	
	HeroType* GameObjectTypesLoader::getHeroTypeByID(const char* pszID)
	{
		auto heroType = dynamic_cast<HeroType*>(this->m_HeroTypes->objectForKey(string(pszID)));
		if (heroType == NULL)
			CCLog("No such heroType '%s' loaded.", pszID);

		return heroType;
	}
	FightingUnitType* GameObjectTypesLoader::getFightingUnitTypeByID(const char* pszID)
	{
		auto fType = dynamic_cast<FightingUnitType*>(this->m_FightingUnitTypes->objectForKey(string(pszID)));
		if (fType == NULL)
			CCLog("No such fightingUnitType '%s' loaded.", pszID);

		return fType;
	}
	MissileType* GameObjectTypesLoader::getMissileTypeByID(const char* pszID)
	{
		auto mType = dynamic_cast<MissileType*>(this->m_MissileTypes->objectForKey(string(pszID)));
		if (mType == NULL)
			CCLog("No such MissileType '%s' loaded.", pszID);

		return mType;
	}
	DistrictType* GameObjectTypesLoader::getDistrictTypeByID(const char* pszID)
	{
		auto dType = dynamic_cast<DistrictType*>(this->m_DistrictTypes->objectForKey(string(pszID)));
		if (dType == NULL)
			CCLog("No such DistrictType '%s' loaded.", pszID);

		return dType;
	}
	TextureType* GameObjectTypesLoader::getTextureTypeByID(const char* pszID)
	{
		auto tType = dynamic_cast<TextureType*>(this->m_TextureTypes->objectForKey(string(pszID)));
		if (tType == NULL)
			CCLog("No such TextureType '%s' loaded.", pszID);

		return tType;
	}
	StringResourceType* GameObjectTypesLoader::getStringResourceTypeByID(const char* pszID)
	{
		auto sType = dynamic_cast<StringResourceType*>(this->m_StringResources->objectForKey(string(pszID)));
		if (sType == NULL)
			CCLog("No such StringResourceType '%s' loaded.", pszID);

		return sType;
	}

	AbilityType* GameObjectTypesLoader::getAbilityTypeByID(const char* pszID)
	{
		auto aType = dynamic_cast<AbilityType*>(this->m_Abilities->objectForKey(string(pszID)));
		if (aType == NULL)
			CCLog("No such AbilityType '%s' loaded.", pszID);

		return aType;
	}

	GameObjectType* GameObjectTypesLoader::getGameObjectTypeByID(const char* pszID)
	{
		GameObjectType* pRet = NULL;
		if ((pRet = getHeroTypeByID(pszID)) != NULL)
		{
			return pRet;
		}

		if ((pRet = getFightingUnitTypeByID(pszID)) != NULL)
		{
			return pRet;
		}

		if ((pRet = getMissileTypeByID(pszID)) != NULL)
		{
			return pRet;
		}
		
		if ((pRet = getDistrictTypeByID(pszID)) != NULL)
		{
			return pRet;
		}

		if ((pRet = getTextureTypeByID(pszID)) != NULL)
		{
			return pRet;
		}

		if ((pRet = getStringResourceTypeByID(pszID)) != NULL)
		{
			return pRet;
		}

		if ((pRet = getAbilityTypeByID(pszID)) != NULL)
		{
			return pRet;
		}

		return pRet;
	}


string GameObjectTypesLoader::getArmatureNameByID(const char* pszID)
{
	return string(this->m_Armatures->valueForKey(string(pszID))->getCString());
}

string GameObjectTypesLoader::getSpriteFrameNameByID(const char* pszID)
{
	return string(this->m_Frames->valueForKey(string(pszID))->getCString());
}


CCArmature* GameObjectTypesLoader::createArmatureByID(const char* pszID)
{
	auto armatureName = this->getArmatureNameByID(pszID);
	if (armatureName.length() == 0)
		return NULL;
	CCArmature* armature = CCArmature::create(armatureName.c_str());
	return armature;
}

CCSprite* GameObjectTypesLoader::createSpriteByID(const char* pszID)
{	
	auto spriteFrameName = this->getSpriteFrameNameByID(pszID);
	if (spriteFrameName.length() == 0)
		return NULL;
	CCSprite* sprite = CCSprite::createWithSpriteFrameName(spriteFrameName.c_str());
	return sprite;
}

void GameObjectTypesLoader::setArmaturePairs(CCObject* obj, const string& key)
{
	this->m_Armatures->setObject(obj, key);
	CCLog("Armature Pair set: %s : %s", key.c_str(), ((CCString*)obj)->getCString());
}

void GameObjectTypesLoader::setFrameParis(CCObject* obj, const string& key)
{
	this->m_Frames->setObject(obj, key);
	CCLog("Frame Pair set: %s : %s", key.c_str(), ((CCString*)obj)->getCString());
}

int GameObjectTypesLoader::loadArmaturesFromTextureConfig()
{
	CCDictElement* el = NULL;
	auto dict = this->m_TextureTypes;
	auto count = 0;
	CCDICT_FOREACH(dict, el)
	{
		auto _type = dynamic_cast<TextureType*>(el->getObject());
		if (_type != NULL)
		{
			auto png = _type->getExportPNG();
			auto plist = _type->getExportPlist();
			auto json = _type->getExportJson();
			CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
					png.c_str(),
					plist.c_str(),
					json.c_str());

			CCLog("Added armature '%s:%s' ('%s' '%s' '%s') without async.", _type->getTypeID().c_str(),
				_type->getName().c_str(),
				png.c_str(), plist.c_str(), json.c_str());
		}
		count++;
	}
	return count;
}



int GameObjectTypesLoader::loadArmaturesFromTextureConfigAsync(CCObject* target, SEL_SCHEDULE selector)
{
	CCDictElement* el = NULL;
	auto dict = this->m_TextureTypes;
	auto count = 0;
	CCDICT_FOREACH(dict, el)
	{
		auto _type = dynamic_cast<TextureType*>(el->getObject());
		if (_type != NULL)
		{
			auto png = _type->getExportPNG();
			auto plist = _type->getExportPlist();
			auto json = _type->getExportJson();
			CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(
					png.c_str(),
					plist.c_str(),
					json.c_str(),
					target,
					selector);

			CCLog("Added armature '%s:%s' ('%s' '%s' '%s') with async.", _type->getTypeID().c_str(),
				_type->getName().c_str(),
				png.c_str(), plist.c_str(), json.c_str());
		}
		count++;
	}
	return count;
}