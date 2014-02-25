#include "DistrictType.h"


DistrictType::DistrictType(CCDictionary* dict) : TexturedGameObjectType(dict)
{
	this->m_Levels = new vector<LevelType*>();
	auto levels = dynamic_cast<CCArray*>(dict->objectForKey(STR_DISTRICT_LEVELS));
	CCObject* obj = NULL;
	CCARRAY_FOREACH(levels, obj)
	{
		auto dict = dynamic_cast<CCDictionary*>(obj);
		if (dict != NULL)
		{
			this->m_Levels->push_back(LevelType::createWithDict(dict));
		}
	}
}


DistrictType::~DistrictType(void)
{
	//TODO: remove its levelTypes
	DELETE_CPP_ARRAY(this->m_Levels, LevelType);
}
