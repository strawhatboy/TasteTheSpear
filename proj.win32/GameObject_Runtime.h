#pragma once
#include "GameObjectType.h"
//#include "Hero_Runtime.h"
//#include "FightingUnit_Runtime.h"
//#include "Missile_Runtime.h"
#include "myLib.h"
#include "cocos2d.h"

class GameObject_Runtime 
	: public CCSprite
{
	CC_SYNTHESIZE(CCDictionary*, m_pAdditionalProperties, AdditionalProperties);

protected:
	GameObjectType* m_GameObjectType;

public:
	GameObject_Runtime(void);
	~GameObject_Runtime(void);

protected:
	virtual bool initWithGameObjectType(GameObjectType* type);

	RUNTIME_OBJ_CREATE(GameObject_Runtime, GameObjectType);

	//static GameObject_Runtime* create(GameObjectType* type)
	//{
	//	auto pszType = type->getObjectType();
	//	if (strcmp(pszType, STR_FIGHTINGUNIT))
	//	{
	//		auto fightUnitType = dynamic_cast<FightingUnitType*>(type);
	//		return (GameObject_Runtime*)FightingUnit_Runtime::create(fightUnitType);
	//	}
	//	else if (strcmp(pszType, STR_HERO))
	//	{
	//		auto heroType = dynamic_cast<HeroType*>(type);
	//		return (GameObject_Runtime*)Hero_Runtime::create(heroType);
	//	}
	//	else if (strcmp(pszType, STR_MISSILE))
	//	{
	//		auto missileType = dynamic_cast<MissileType*>(type);
	//		return (GameObject_Runtime*)Missile_Runtime::create(missileType);
	//	}
	//}

	// returns HERO, UNIT, MISSILE, BOSS
	virtual string getObjectType(void) const
	{
		return m_GameObjectType->getObjectType();
	}

	virtual string getTypeID(void) const
	{
		return m_GameObjectType->getTypeID();
	}

	virtual string getName(void) const
	{
		return m_GameObjectType->getName();
	}

	virtual CCObject* getAdditionalProperty(const string& key) const
	{
		return m_pAdditionalProperties->objectForKey(key);
	}

	virtual void setAdditionalProperty(const string& key, CCObject* value)
	{
		m_pAdditionalProperties->setObject(value, key);
	}
};

