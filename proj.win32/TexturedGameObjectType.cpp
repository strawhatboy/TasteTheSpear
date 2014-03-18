#include "TexturedGameObjectType.h"
#include "GameObjectTypesLoader.h"

TexturedGameObjectType::TexturedGameObjectType(CCDictionary* dict) : GameObjectType(dict)
{
	this->m_pszTexture = dict->valueForKey(STR_GAMEOBJECT_TEXTURE)->getCString();
}


TexturedGameObjectType::~TexturedGameObjectType(void)
{
}

bool TexturedGameObjectType::loadArmature(
		CCObject* target,
		SEL_SCHEDULE selector) const
{
	do
	{
		auto id = this->getTypeID();
		auto loader = GameObjectTypesLoader::sharedInstance();
		if (strlen(loader->getArmatureNameByID(id.c_str())) == 0)
				{//There's no such armature available in the dict, so add it. otherwise skip it.

					// we won't add the armature to cache here but when looping the texture list.
					auto _t_type = loader->getTextureTypeByID(this->getTexture().c_str());
					string name;
					if (_t_type != NULL)
					{
						name = _t_type->getName();
					//	auto json = _t_type->getExportJson();
					//	auto png = _t_type->getExportPNG();
					//	auto plist = _t_type->getExportPlist();
					//	if (selector != NULL)
					//		CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(
					//			png.c_str(),
					//			plist.c_str(),
					//			json.c_str(),
					//			target,
					//			selector);
					//	else
					//		CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo(
					//			png.c_str(),
					//			plist.c_str(),
					//			json.c_str());

						//CCArmature* armature = CCArmature::create(name.c_str());
						//this->m_Armatures->setObject(CCString::create(name), id);
					}
					else
					{
						name = loader->getTextureTypeByID("T006")->getName();
					}
					loader->setArmaturePairs(CCString::create(name), id);
				}
	}while(0);

	return true;
}