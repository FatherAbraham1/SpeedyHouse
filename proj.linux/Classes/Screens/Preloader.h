#ifndef CONST_PRELOADER_H
#define CONST_PRELOADER_H

#include "cocos2d.h"

#include "Screen.h"
#include "MainMenu.h"
#include "Options.h"

using namespace cocos2d;

class Preloader : public Screen
{
	private:
		int mNumberOfSprites;
		int mNumberOfLoadedSprites;

		CCProgressTimer* mProgressTimer;

	public:
		Preloader(void);

		void loadingCallBack(CCObject *obj);
		bool checkIsTexturesLoaded();

		virtual void update(float pDeltaTime);
};

#endif