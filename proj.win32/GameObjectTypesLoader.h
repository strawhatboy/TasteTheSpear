#pragma once

#include "myLib.h"
#include "HeroType.h"
#include "FightingUnitType.h"
#include "MissileType.h"
#include "LevelType.h"
#include "DistrictType.h"
#include "TextureType.h"
#include "StringResourceType.h"

#include "cocos-ext.h"
USING_NS_CC_EXT;

#define STR_HERO_TYPES_CONFIG_FILE_NAME "hero_config.plist"
#define STR_LEVEL_TYPES_CONFIG_FILE_NAME "level_config.plist"
#define STR_TEXTURE_TYPES_CONFIG_FILE_NAME "texture_config.plist"
#define STR_STRINGRESOURCE_TYPES_CONFIG_FILE_NAME "stringResources.plist"

class GameObjectTypesLoader
{
	CC_SYNTHESIZE_READONLY(CCDictionary*, m_HeroTypes, HeroTypes);
	CC_SYNTHESIZE_READONLY(CCDictionary*, m_FightingUnitTypes, FightingUnitTypes);
	CC_SYNTHESIZE_READONLY(CCDictionary*, m_MissileTypes, MissileTypes);
	CC_SYNTHESIZE_READONLY(CCDictionary*, m_DistrictTypes, DistrictTypes);
	CC_SYNTHESIZE_READONLY(CCDictionary*, m_TextureTypes, TextureTypes);
	CC_SYNTHESIZE_READONLY(CCDictionary*, m_Armatures, Armatures);
	CC_SYNTHESIZE_READONLY(CCDictionary*, m_StringResources, StringResources);

private:


	//CCDictionary* m_HeroTypes;
	////vector<HeroType*>* m_HeroTypes;
	//CCDictionary* m_FightingUnitTypes;
	//CCDictionary* m_MissileTypes;
	//CCDictionary* m_DistrictTypes;
	//CCDictionary* m_TextureTypes;

	//// key: typeid of texturedgameobjecttype, value: the name used to create armature
	//CCDictionary* m_Armatures;
	
	bool loadHeroTypes();
	bool loadAbilityTypes();
	bool loadAnimationsTypes();
	bool loadLevelTypes();
	bool loadFightingUnitTypes();
	bool loadItemTypes();
	bool loadTextureTypes();
	bool loadStringResourceTypes();

	int loadArmaturesWithDict(const CCDictionary* dict);
	int loadArmaturesWithDictAsync(const CCDictionary* dict, CCObject* target, SEL_SCHEDULE selector);
	int loadArmaturesWithDict_Common(const CCDictionary* dict, CCObject* target, SEL_SCHEDULE selector);

	template <class T>
	bool loadTypeFromFile(const char* pszFileName, const char* pszFirstKeyName, CCDictionary* result);
	int loadArmaturesFromTextureConfig();
	int loadArmaturesFromTextureConfigAsync(CCObject* target, SEL_SCHEDULE selector);

public:
	~GameObjectTypesLoader(void);
	bool loadAllTypes();

	HeroType* getHeroTypeByID(const char* pszID);
	FightingUnitType* getFightingUnitTypeByID(const char* pszID);
	MissileType* getMissileTypeByID(const char* pszID);
	DistrictType* getDistrictTypeByID(const char* pszID);
	TextureType* getTextureTypeByID(const char* pszID);
	StringResourceType* getStringResourceTypeByID(const char* pszID);

	const char* getArmatureNameByID(const char* pszID);

	// create an armature type object by TypeID
	CCArmature* createArmatureByID(const char* pszID);

	// return count that loaded for the async method.
	int loadArmatures();
	int loadArmaturesAsync(CCObject* target, SEL_SCHEDULE selector);

	void setArmaturePairs(CCObject* obj, const string& key);
	
	CC_SHARED_CREATE_FUNC(GameObjectTypesLoader);
};

