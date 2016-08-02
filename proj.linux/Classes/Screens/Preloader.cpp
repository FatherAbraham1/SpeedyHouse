#ifndef CONST_PRELOADER
#define CONST_PRELOADER

#include "Preloader.h"

Preloader::Preloader(void)
{
	this->mNumberOfLoadedSprites = 0;
	this->mNumberOfSprites = 1;

	Entity* mBackground = new Entity("start-preloader-bg.png", this);

	Entity* progressBackgroundLayer1 = new Entity("start-preloader-down.png");
	Entity* progressBackgroundLayer2 = new Entity("start-preloader-fill.png");
	Entity* progressBackgroundLayer3 = new Entity("start-preloader-up.png");

	this->mProgressTimer = CCProgressTimer::create(progressBackgroundLayer2);
	this->mProgressTimer->setType(kCCProgressTimerTypeBar);
	this->mProgressTimer->setMidpoint(ccp(0, 0));
	this->mProgressTimer->setBarChangeRate(ccp(1, 0));
	this->mProgressTimer->setPercentage(0);

	this->addChild(progressBackgroundLayer1);
	this->addChild(this->mProgressTimer);
	this->addChild(progressBackgroundLayer3);

	this->mProgressTimer->runAction(CCProgressTo::create(3.5, 100));

	mBackground->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
	progressBackgroundLayer1->setCenterPosition(Options::CAMERA_CENTER_X, Utils::coord(44));
	progressBackgroundLayer3->setCenterPosition(Options::CAMERA_CENTER_X, Utils::coord(40));
	this->mProgressTimer->setPosition(ccp(Options::CAMERA_CENTER_X + Utils::coord(5), Utils::coord(40)));

	CCTextureCache::sharedTextureCache()->addImageAsync("start-preloader-bg.png", this, callfuncO_selector(Preloader::loadingCallBack));	
}

void Preloader::loadingCallBack(CCObject *obj)
{
	++mNumberOfLoadedSprites;

	//this->mProgressTimer->setPercentage((int)(((float)mNumberOfLoadedSprites / mNumberOfSprites) * 100));

	if(mNumberOfLoadedSprites == mNumberOfSprites)
	{
		if(this->checkIsTexturesLoaded())
		{
			CCDirector::sharedDirector()->replaceScene(new MainMenu());
		}
	}
	else
	{
				
	}
}

bool Preloader::checkIsTexturesLoaded()
{
	return this->mProgressTimer->getPercentage() >= 100;
}

void Preloader::update(float pDeltaTime)
{
	if(this->checkIsTexturesLoaded())
	{
		CCDirector::sharedDirector()->replaceScene(new MainMenu());
	}
}

#endif