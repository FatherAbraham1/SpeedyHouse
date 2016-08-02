#ifndef CONST_DIFICULT
#define CONST_DIFICULT

#include "Difficult.h"

void Difficult::init(CCNode* pParent)
{
	if(pParent != NULL)
	{
		pParent->addChild(this);
	}
	
	//this->mBackground   = new Entity(240, 160, "difficulty-menu-popup.png", this);

	//this->mEasyButton   = new EasyButton(165, 200, "difficulty-menu-btn-easy.png", this->mBackground, this);
	//this->mNormalButton = new NormalButton(165, 150, "difficulty-menu-btn-normal.png", this->mBackground, this);
	//this->mHardButton   = new HardButton(165, 100, "difficulty-menu-btn-expert.png", this->mBackground, this);

	//this->mBackButton   = new BackButton(40, 40, "difficulty-menu-btn-back.png", this, this);

	//this->create();
}

Difficult::Difficult()
{
	this->init(NULL);
}

Difficult::Difficult(CCNode* pParent)
{
	this->init(pParent);
}

#endif