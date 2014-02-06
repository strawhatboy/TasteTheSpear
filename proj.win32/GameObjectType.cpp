#include "GameObjectType.h"


GameObjectType::GameObjectType(CCDictionary* dict)
{
	this->m_pszName = dict->valueForKey(STR_GAMEOBJECT_NAME)->getCString();
	this->m_pszDescription = dict->valueForKey(STR_GAMEOBJECT_DESCRIPTION)->getCString();
	this->m_pszTypeID = dict->valueForKey(STR_GAMEOBJECT_TYPEID)->getCString();
	this->m_pszTexture = dict->valueForKey(STR_GAMEOBJECT_TEXTURE)->getCString();
	//this->m_Animations = dynamic_cast<CCArray*>(dict->objectForKey(STR_GAMEOBJECT_ANIMATION));
}

GameObjectType::~GameObjectType(void)
{
}
