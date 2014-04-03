#pragma once

#include "GameObjectType.h"

#define STR_TEXTURE_EXPORTPNG "ExportPNG"
#define STR_TEXTURE_EXPORTPLIST "ExportPlist"
#define STR_TEXTURE_EXPORTJSON "ExportJson"

class TextureType :
	public GameObjectType
{
	CC_SYNTHESIZE_READONLY(string, m_pszExportPNG, ExportPNG);
	CC_SYNTHESIZE_READONLY(string, m_pszExportPlist, ExportPlist);
	CC_SYNTHESIZE_READONLY(string, m_pszExportJson, ExportJson);

public:
	//TextureType(CCDictionary* dict);
	~TextureType(void);
	virtual string getObjectType(void) const
	{
		return STR_TEXTURE;
	}

	CREATE_WITH_DICT(TextureType);
};

