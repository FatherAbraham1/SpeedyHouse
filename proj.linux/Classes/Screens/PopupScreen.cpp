#ifndef CONST_POPUPSCREEN
#define CONST_POPUPSCREEN

#include "PopupScreen.h"

void PopupScreen::init(CCNode* pParent)
{
	if(pParent != NULL)
	{
		pParent->addChild(this);
	}

	this->mIsAttached = false;
	this->mAnimationNeedShow = false;
	this->mAnimationNeedHide = false;

	this->mBackgroundCircle = new Entity("circle.png", this);
	this->mBackgroundCircle->setScale(2);

	this->mAnimationTimeElapsed = 0;
	this->mAnimationTimeToHide = 0.3;

	this->mElementsCreateTime = 0.2;
	this->mElementsCreateTimeElapsed = 0;

	this->mAnimationNeedHide = false;

	this->mAnimationElements = new EntityManager(100, new Spiral(), this);
	
	this->mAnimationElementsTexture1 = new Texture("popup-sprite-1.png", 6, 1);
	this->mAnimationElementsTexture2 = new Texture("popup-sprite-2.png", 4, 1);
	this->mAnimationElementsTexture3 = new Texture("popup-sprite-3.png", 4, 1);
	this->mAnimationElementsTexture4 = new Texture("popup-sprite-4.png", 4, 1);
	this->mAnimationElementsTexture5 = new Texture("popup-sprite-5.png", 4, 1);
	this->mAnimationElementsTexture6 = new Texture("popup-sprite-6.png", 4, 1);
	this->mAnimationElementsTexture7 = new Texture("popup-sprite-7.png", 4, 1);

	this->scheduleUpdate();
}

PopupScreen::PopupScreen()
{
	this->init(NULL);
}

PopupScreen::PopupScreen(CCNode* pParent)
{
	this->init(pParent);
}

void PopupScreen::create()
{
	this->mBackground->setScale(0);
	this->setVisible(false);
}

void PopupScreen::show()
{
	this->setVisible(true);

	this->mBackground->runAction(CCScaleTo::create(this->mAnimationTimeToHide, 1.0));
	this->mBackgroundCircle->runAction(CCScaleTo::create(this->mAnimationTimeToHide, 0));

	this->mAnimationNeedShow = true;

	this->onShowStarted();
}

void PopupScreen::hide()
{
	this->mBackground->runAction(CCScaleTo::create(this->mAnimationTimeToHide, 0));
	this->mBackgroundCircle->runAction(CCScaleTo::create(this->mAnimationTimeToHide, 2));

	this->mAnimationNeedHide = true;

	this->onCloseStarted();
}

EntityManager* PopupScreen::getPopupScreenElements()
{
	return this->mAnimationElements;
}

void PopupScreen::onShowStarted()
{
	switch(Utils::random(1, 7))
	{
		case 1:
			this->mAnimationElements->changeTexture(this->mAnimationElementsTexture1);
		break;
		case 2:
			this->mAnimationElements->changeTexture(this->mAnimationElementsTexture2);
		break;
		case 3:
			this->mAnimationElements->changeTexture(this->mAnimationElementsTexture3);
		break;
		case 4:
			this->mAnimationElements->changeTexture(this->mAnimationElementsTexture4);
		break;
		case 5:
			this->mAnimationElements->changeTexture(this->mAnimationElementsTexture5);
		break;
		case 6:
			this->mAnimationElements->changeTexture(this->mAnimationElementsTexture6);
		break;
		case 7:
			this->mAnimationElements->changeTexture(this->mAnimationElementsTexture7);
		break;
	}
}

void PopupScreen::onShowFinished()
{
	this->mIsAttached = true;
}

void PopupScreen::onCloseStarted()
{
	for(int i = 0; i < this->mAnimationElements->getCount(); i++)
	{
		((Spiral*) this->mAnimationElements->objectAtIndex(i))->hide();
	}
}

void PopupScreen::onCloseFinished()
{
	this->mIsAttached = false;

	this->mAnimationElements->clear();
}

void PopupScreen::update(float pDeltaTime)
{
	if(this->mAnimationNeedShow)
	{
		this->mAnimationTimeElapsed += pDeltaTime;

		if(this->mAnimationTimeElapsed >= this->mAnimationTimeToHide)
		{
			this->mAnimationNeedShow = false;
			this->mAnimationTimeElapsed = 0;

			this->onShowFinished();
		}
	}

	if(this->mAnimationNeedHide)
	{
		this->mAnimationTimeElapsed += pDeltaTime;

		if(this->mAnimationTimeElapsed >= this->mAnimationTimeToHide)
		{
			this->setVisible(false);

			this->mAnimationNeedHide = false;
			this->mAnimationTimeElapsed = 0;

			this->onCloseFinished();
		}
	}

	if(this->mIsAttached)
	{
		this->mElementsCreateTimeElapsed += pDeltaTime;

		if(this->mElementsCreateTimeElapsed >= this->mElementsCreateTime)
		{
			this->mElementsCreateTimeElapsed = 0;

			if(this->mAnimationElements->getCount() < 100)
			{
				((Spiral*) this->mAnimationElements->create())->show();
			}
		}
	}
}

void PopupScreen::draw()
{
	if(this->isVisible())
	{
		int x = this->mBackgroundCircle->getPosition().x;
		int y = this->mBackgroundCircle->getPosition().y;

		int width = this->mBackgroundCircle->getTextureRect().size.width * this->mBackgroundCircle->getScale();
		int height = this->mBackgroundCircle->getTextureRect().size.height * this->mBackgroundCircle->getScale();

		int padding = 5;
		int size = 1000;

		CCPoint vertices1[] = {
			ccp(x - width / 2 + padding, y - height - size),
			ccp(x - size - width / 2 + padding, y - height),
			ccp(x - size - width / 2 + padding, y + height + height / 2),
			ccp(x - width / 2 + padding, y + height + height / 2 + size)
		};

		CCPoint vertices2[] = {
			ccp(x + width/2 - padding, y - height - size),
			ccp(x + size + width / 2 - padding, y - height),
			ccp(x + size + width / 2 - padding, y + height + height / 2),
			ccp(x + width/2 - padding, y + height + height / 2 + size)
		};

		CCPoint vertices3[] = {
			ccp(x - width / 2, y - height / 2),
			ccp(x, y - height - size),
			ccp(x + width / 2, y - height / 2),
			ccp(x, y - height - size)
		};

		CCPoint vertices4[] = {
			ccp(x - width / 2, y + height / 2),
			ccp(x, y - height + size),
			ccp(x + width / 2, y + height / 2),
			ccp(x, y - height + size)
		};

		ccDrawSolidPoly(vertices1, 4, ccc4f(255.0f / 255.0f, 252.0f / 255.0f, 232.0f / 255.0f, 1));
		ccDrawSolidPoly(vertices2, 4, ccc4f(255.0f / 255.0f, 252.0f / 255.0f, 232.0f / 255.0f, 1));
		ccDrawSolidPoly(vertices3, 4, ccc4f(255.0f / 255.0f, 252.0f / 255.0f, 232.0f / 255.0f, 1));
		ccDrawSolidPoly(vertices4, 4, ccc4f(255.0f / 255.0f, 252.0f / 255.0f, 232.0f / 255.0f, 1));
	}
}

#endif