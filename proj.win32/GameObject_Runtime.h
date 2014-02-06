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
	virtual const char* getObjectType(void) const
	{
		return m_GameObjectType->getObjectType();
	}

	virtual const char* getTypeID(void) const
	{
		return m_GameObjectType->getTypeID();
	}

	virtual const char* getName(void) const
	{
		return m_GameObjectType->getName();
	}
};

