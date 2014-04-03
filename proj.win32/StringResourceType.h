#pragma once
#include "GameObjectType.h"

#define STR_STRINGRESOURCE_STRINGS "strings"

class StringResourceType :
	public GameObjectType
{
	CC_SYNTHESIZE_READONLY(CCDictionary* , m_Strings, Strings);

public:
	//StringResourceType(void);
	~StringResourceType(void);
	virtual string getObjectType(void) const
	{
		return STR_STRINGRESOURCE;
	}

	string getStringByKey(int nKey);

	CREATE_WITH_DICT(StringResourceType);
};

