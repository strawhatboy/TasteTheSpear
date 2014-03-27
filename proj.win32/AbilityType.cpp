#include "AbilityType.h"


AbilityType::AbilityType(CCDictionary* dict) : TexturedGameObjectType(dict)
{
	m_Data = dynamic_cast<CCDictionary*>(dict->objectForKey(STR_ABILITY_DATA));
	m_Data->retain();
}


AbilityType::~AbilityType(void)
{
	CC_SAFE_RELEASE(m_Data);
}
