#include "LevelSelectLayer.h"


bool LevelSelectLayer::init(const char* districtTypeID)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		auto typesLoader = GameObjectTypesLoader::sharedInstance();
		auto districtList = typesLoader->getDistrictTypes();
		if (strlen(districtTypeID) == 0)
		{
			// use the 1st district
			districtTypeID = "D001";
		}
		auto arrLayer = CCArray::create();

		//CCDictElement* el = NULL;
		int count = 0;

		auto district = dynamic_cast<DistrictType*>(districtList->objectForKey(string(districtTypeID)));
		CC_BREAK_IF(district == NULL);
		auto levels = district->getLevels();
		auto levelsIDs = this->m_LevelsIDs;
		for_each(levels->begin(), levels->end(), [&levelsIDs, &count, &arrLayer, typesLoader](const LevelType* levelType){
			

			CCLayer* layer = CCLayer::create();
			layer->setTag(count++);
			auto armature = typesLoader->createArmatureByID(levelType->getTypeID().c_str());
			
			armature->setPosition(ccpSub(ccpSub(designResolutionSize, ccpMult(armature->getContentSize(), 0.5f)), ccp(0, 100)));
			layer->addChild(armature);

			// Add Name Label
			CCLabelTTF* label = CCLabelTTF::create(levelType->getName().c_str(), "Segoe UI", 50.f,
				armature->getContentSize(), kCCTextAlignmentLeft, kCCVerticalTextAlignmentBottom);
			label->setPosition(ccpAdd(armature->getPosition(), ccp(20, 20)));
			layer->addChild(label);

			// Add Description Label
			CCLabelTTF* labelD = CCLabelTTF::create(levelType->getDescription().c_str(), "Segoe UI", 40.f,
				CCSizeMake(designResolutionSize.width - 40, designResolutionSize.height - armature->getContentSize().height -140),
				kCCTextAlignmentLeft, kCCVerticalTextAlignmentTop);
			labelD->setPosition(ccpAdd(ccp(20, 20), ccpMult(labelD->getContentSize(), 0.5f)));
			layer->addChild(labelD);
					
			levelsIDs->push_back(levelType->getTypeID());
			arrLayer->addObject(layer);
		});

		// adjust the screen
		auto pos = CCPDesignZero;

		auto scrollLayer = ScrollLayer::createWithLayers(arrLayer, CCSizeZero, pos);
		this->addChild(scrollLayer);
		scrollLayer->registerSelectEvent(this, callfuncO_selector(LevelSelectLayer::levelSelected));

		
			// Add Title Label
		CCLabelTTF* labelT = CCLabelTTF::create(GameDirector::sharedInstance()->getUIStringByID(10001).c_str(),
			"Segoe UI", 60.f, CCSizeMake(designResolutionSize.width, 100),
			kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
		labelT->setPosition(ccpAdd(CCPDesignZero, ccpSub(designResolutionSize, ccpMult(labelT->getContentSize(), 0.5f))));
		this->addChild(labelT);


		// Add HOME menuitem
		bRet = true;
	} while (0);

	return bRet;
}

LevelSelectLayer::LevelSelectLayer(void)
{
	INIT_POINTER(m_LevelsIDs);
	m_LevelsIDs = new vector<string>();
}


LevelSelectLayer::~LevelSelectLayer(void)
{
	CC_SAFE_DELETE(m_LevelsIDs);
}

void LevelSelectLayer::levelSelected(CCObject* obj)
{
	
	auto layer = dynamic_cast<CCLayer*>(obj);
	if (layer == NULL)
		return;

	int index = layer->getTag();
	auto levelID = this->m_LevelsIDs->at(index);
	GameDirector::sharedInstance()->setCurrentLevel(levelID);
	// move to hero select scene.
	auto heroScene = HeroSelectScene::create();
	CCDirector::sharedDirector()->replaceScene(heroScene);
	CCLog("Level Selected with index %d.", index);
}