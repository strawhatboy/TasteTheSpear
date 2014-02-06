#include "myLib.h"
//! convert from wstring to UTF8 using self-coding-converting
void WStrToUTF8(std::string& dest, const std::wstring& src)
{
	dest.clear();
	for (size_t i = 0; i < src.size(); i++)
	{
		wchar_t w = src[i];
		if (w <= 0x7f)
		dest.push_back((char)w);
		else if (w <= 0x7ff)
		{
			dest.push_back(0xc0 | ((w >> 6)& 0x1f));
			dest.push_back(0x80| (w & 0x3f));
		}
		else if (w <= 0xffff)
		{
			dest.push_back(0xe0 | ((w >> 12)& 0x0f));
			dest.push_back(0x80| ((w >> 6) & 0x3f));
			dest.push_back(0x80| (w & 0x3f));
		}
		else if (sizeof(wchar_t) > 2 && w <= 0x10ffff)
		{
			dest.push_back(0xf0 | ((w >> 18)& 0x07)); // wchar_t 4-bytes situation
			dest.push_back(0x80| ((w >> 12) & 0x3f));
			dest.push_back(0x80| ((w >> 6) & 0x3f));
			dest.push_back(0x80| (w & 0x3f));
		}
		else
			dest.push_back('?');
	}
}
		
//! simple warpper
std::string WStrToUTF8(const std::wstring& str)
{
	std::string result;
	WStrToUTF8(result, str);
	return result;
}

//
//bool ShowTuTsauMsg(const char* msg)
//{
//	return ShowTuTsauMsg(STR_TUTSAU_TYPE_WUGU, msg);
//}
//
//bool ShowTuTsauMsg(const char* msgType, const char* msg)
//{
//
//	auto pDirector = CCDirector::sharedDirector();
//	auto pCurrentScene = pDirector->getRunningScene();
//	auto pLayer = CCLayerColor::create(ccc4(0, 0, 0, 50)); //grey
//	auto pChildLayer = CCLayerColor::create(ccc4(255, 255, 255, 255)); //white
//
//	// stop all animations and all backgroud sounds
//	pDirector->stopAnimation();
//	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
//
//	// we'll put image and msg into the childLayer
//	auto visibleSize = pDirector->getVisibleSize();
//	auto origin = pDirector->getVisibleOrigin();
//	auto center = ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
//	pLayer->setContentSize(visibleSize);
//	
//	CCSprite* sprite = CCSprite::create(CCString::createWithFormat("%s/%s%s", FOLDER_TUTSAU, msgType, STR_TUTSAU_FILE_SUFFIX)->getCString());
//	// sprite and the words should occupy 4/5 of the width.
//
//	auto childLayerContentWidth = 0.8 * visibleSize.width;
//	auto spriteSize = sprite->getContentSize();
//	auto wordsWidth = childLayerContentWidth - spriteSize.width;
//	CCLabelTTF* label = CCLabelTTF::create(msg, STR_TUTSAU_FONTS, FONT_SIZE_TUTSAU, CCSizeMake(wordsWidth, 0),
//		CCTextAlignment::kCCTextAlignmentLeft, CCVerticalTextAlignment::kCCVerticalTextAlignmentTop);
//	label->setColor(ccc3(0, 0, 0));
//	auto childLayerContentHeight = max(spriteSize.height, label->getContentSize().height) + 20;
//
//	auto spritePosition = ccp(center.x - childLayerContentWidth / 2 + spriteSize.width / 2,
//		childLayerContentHeight / 2);
//	auto wordsPosition = ccp(center.x + childLayerContentWidth / 2 - wordsWidth /2,
//		childLayerContentHeight / 2);
//	sprite->setPosition(spritePosition);
//	label->setPosition(wordsPosition);
//	pChildLayer->setContentSize(CCSizeMake(visibleSize.width, childLayerContentHeight));
//	pChildLayer->addChild(sprite, 100);
//	pChildLayer->addChild(label, 100);
//	pChildLayer->setPosition(ccp(center.x - visibleSize.width / 2, center.y - childLayerContentHeight / 2));
//
//	pLayer->addChild(pChildLayer, 99);
//
//	pCurrentScene->addChild(pLayer, 98, TAG_TUTSAU);
//
//	return true;
//}
//
//
//bool ShowTuTsauMsg(int msgID)
//{
//	return ShowTuTsauMsg(msgID, false);
//}
//
//bool ShowTuTsauMsg(int msgID, bool force)
//{
//	return true;
//}


// Copied from CCSprite.cpp line 1081+
static unsigned char cc_2x2_white_image[] = {
    // RGBA8888
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF
};

#define CC_2x2_WHITE_IMAGE_KEY  "cc_2x2_white_image"
CCTexture2D* getEmptyWhiteTexture()
{
    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->textureForKey(CC_2x2_WHITE_IMAGE_KEY);
    // If texture wasn't in cache, create it from RAW data.
    if (NULL == texture)
    {
		CCImage* image = new CCImage();
        bool isOK = image->initWithImageData(cc_2x2_white_image, sizeof(cc_2x2_white_image), CCImage::kFmtRawData, 2, 2, 8);
        CCAssert(isOK, "The 2x2 empty texture was created unsuccessfully.");
		
		texture = CCTextureCache::sharedTextureCache()->addUIImage(image, CC_2x2_WHITE_IMAGE_KEY);
        CC_SAFE_RELEASE(image);
	}

	return texture;
	
}