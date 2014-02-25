#include "TextureType.h"


TextureType::TextureType(CCDictionary* dict) : GameObjectType(dict)
{
	this->m_pszExportJson = dict->valueForKey(STR_TEXTURE_EXPORTJSON)->getCString();
	this->m_pszExportPlist = dict->valueForKey(STR_TEXTURE_EXPORTPLIST)->getCString();
	this->m_pszExportPNG = dict->valueForKey(STR_TEXTURE_EXPORTPNG)->getCString();
}


TextureType::~TextureType(void)
{
}
