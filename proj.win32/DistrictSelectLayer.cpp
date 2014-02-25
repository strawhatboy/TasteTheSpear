#include "DistrictSelectLayer.h"
#include "AppMacros.h"

bool DistrictSelectLayer::init()
{
	bool bRet = false;
	do 
	{
		auto typesLoader = GameObjectTypesLoader::sharedInstance();
		auto districtList = typesLoader->getDistrictTypes();
		auto arrLayer = CCArray::create();

		CCDictElement* el = NULL;
		int count = 0;
		CCDICT_FOREACH(districtList, el)
		{
			auto district = dynamic_cast<DistrictType*>(el->getObject());
			CC_CONTINUE_IF(district == NULL);

			CCLayer* layer = CCLayer::create();
			layer->setTag(count++);
			auto armature = typesLoader->createArmatureByID(district->getTypeID().c_str());
			
			armature->setPosition(ccpSub(ccpSub(designResolutionSize, ccpMult(armature->getContentSize(), 0.5f)), ccp(0, 100)));
			layer->addChild(armature);

			// Add Name Label
			CCLabelTTF* label = CCLabelTTF::create(district->getName().c_str(), "Segoe UI", 50.f,
				armature->getContentSize(), kCCTextAlignmentLeft, kCCVerticalTextAlignmentBottom);
			label->setPosition(ccpAdd(armature->getPosition(), ccp(20, 20)));
			layer->addChild(label);

			// Add Description Label
			CCLabelTTF* labelD = CCLabelTTF::create(district->getDescription().c_str(), "Segoe UI", 40.f,
				CCSizeMake(designResolutionSize.width - 40, designResolutionSize.height - armature->getContentSize().height -140),
				kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
			labelD->setPosition(ccpAdd(ccp(20, 20), ccpMult(labelD->getContentSize(), 0.5f)));
			layer->addChild(labelD);
					

			arrLayer->addObject(layer);
		}

		// adjust the screen
		auto pos = CCPDesignZero;

		auto scrollLayer = ScrollLayer::createWithLayers(arrLayer, CCSizeZero, pos);
		this->addChild(scrollLayer);
		scrollLayer->registerSelectEvent(this, callfuncO_selector(DistrictSelectLayer::districtSelected));

		
			// Add Title Label
		CCLabelTTF* labelT = CCLabelTTF::create(GameDirector::sharedInstance()->getUIStringByID(10000).c_str(),
			"Segoe UI", 60.f, CCSizeMake(designResolutionSize.width, 100),
			kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
		labelT->setPosition(ccpAdd(CCPDesignZero, ccpSub(designResolutionSize, ccpMult(labelT->getContentSize(), 0.5f))));
		this->addChild(labelT);

		bRet = true;
	} while (0);

	return bRet;
}

DistrictSelectLayer::DistrictSelectLayer(void)
{
}


DistrictSelectLayer::~DistrictSelectLayer(void)
{
}

void DistrictSelectLayer::districtSelected(CCObject* obj)
{
	auto layer = dynamic_cast<CCLayer*>(obj);
	if (layer == NULL)
		return;

	int index = layer->getTag();

	CCLog("District Selected with index %d.", index);
}