#include "StringResourceType.h"


StringResourceType::StringResourceType(CCDictionary* dict) : GameObjectType(dict)
{
	this->m_Strings = dynamic_cast<CCDictionary*>(dict->objectForKey(STR_STRINGRESOURCE_STRINGS));
	this->m_Strings->retain();
}


StringResourceType::~StringResourceType(void)
{
	this->m_Strings->release();
}

string StringResourceType::getStringByKey(int nKey)
{
	return this->m_Strings->valueForKey(string(CCString::createWithFormat("%d", nKey)->getCString()))->getCString();
}
