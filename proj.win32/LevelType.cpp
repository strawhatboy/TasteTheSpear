#include "LevelType.h"


LevelType::LevelType(CCDictionary* dict) : TexturedGameObjectType(dict)
{	
	this->m_Script = dict->valueForKey(STR_LEVEL_SCRIPT)->getCString();
}


LevelType::~LevelType(void)
{
}
