#include "TexturedGameObjectType.h"


TexturedGameObjectType::TexturedGameObjectType(CCDictionary* dict) : GameObjectType(dict)
{
	this->m_pszTexture = dict->valueForKey(STR_GAMEOBJECT_TEXTURE)->getCString();
}


TexturedGameObjectType::~TexturedGameObjectType(void)
{
}