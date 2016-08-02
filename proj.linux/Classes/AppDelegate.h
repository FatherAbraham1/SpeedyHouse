#ifndef CONST_APPDELEGATE_H
#define CONST_APPDELEGATE_H

#include "cocos2d.h"

#include <vector>

#include "Screen.h"
#include "Preloader.h"
#include "Options.h"

using namespace std;
using namespace cocos2d;

typedef struct tagResource {
	CCSize size;
	char directory[100];
} Resource;

static Resource Resources480x320  	= { CCSizeMake(610, 380),  "480x320"   };
static Resource Resources1024x720 	= { CCSizeMake(1024, 720), "1024x720"  };
static Resource Resources2048x1536  = { CCSizeMake(2048, 1536),"2048x1536" };
static CCSize designResolutionSize  = CCSizeMake(610, 380);

class AppDelegate : private CCApplication
{
	public:
		bool applicationDidFinishLaunching();

		void applicationDidEnterBackground();
		void applicationWillEnterForeground();
};

#endif