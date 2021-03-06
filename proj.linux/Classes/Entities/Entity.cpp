#ifndef CONST_ENTITY
#define CONST_ENTITY

#include "Entity.h"
#include "AppDelegate.h"
#include "EntityManager.h"
#include "Preloader.h"

void Entity::init(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, CCNode* pParent)
{
	CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();

	this->initWithFile(pszFileName);

	if(pParent)
	{
		pParent->addChild(this);
	}

	this->mWidth  = this->getTextureRect().size.width;
	this->mHeight = this->getTextureRect().size.height;

	this->mFrameWidth = this->mWidth / pHorizontalFramesCount;
	this->mFrameHeight = this->mHeight / pVerticalFramesCount; 

	this->mFramesCount = pHorizontalFramesCount * pVerticalFramesCount;

	this->mHorizontalFramesCount = pHorizontalFramesCount;
	this->mVerticalFramesCount   = pVerticalFramesCount;

	this->mWasTouched = false;

	/**
	 *
	 * We must remember all coordinates of each frame
	 * for quick get x and y of it.
	 *
	 */

	this->mFramesCoordinatesX = new int[this->mVerticalFramesCount];
	this->mFramesCoordinatesY = new int[this->mHorizontalFramesCount];

	int counter = 0;

	for(int i = 0; i < this->mVerticalFramesCount; i++)
	{
		for(int j = 0; j < this->mHorizontalFramesCount; j++, counter++)
		{
			this->mFramesCoordinatesX[counter] = j * (this->mWidth / this->mHorizontalFramesCount);
			this->mFramesCoordinatesY[counter] = i * (this->mHeight / this->mVerticalFramesCount);
		}
	}

	/**
	 *
	 * Setting zero frame
	 *
	 */

	this->setCurrentFrameIndex(0);

	/**
	 *
	 *
	 * Take care about an animations
	 *
	 */

	this->mAnimationScaleDownTime = 0.2;
	this->mAnimationScaleUpTime = 0.2;

	this->mAnimationScaleDownFactor = 0.8;
	this->mAnimationScaleUpFactor = 1.0;

	this->mIsRegisterAsTouchable = false;

	this->scheduleUpdate();
}


Entity::Entity()
{
}

Entity::Entity(const char* pszFileName)
{
	this->init(pszFileName, 1, 1, NULL);
}

Entity::Entity(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount)
{
	this->init(pszFileName, pHorizontalFramesCount, pVerticalFramesCount, NULL);
}

Entity::Entity(const char* pszFileName, CCNode* pParent)
{
	this->init(pszFileName, 1, 1, pParent);
}

Entity::Entity(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, CCNode* pParent)
{
	this->init(pszFileName, pHorizontalFramesCount, pVerticalFramesCount, pParent);
}
		
/**
 *
 * Take care about careful position
 *
 */

void Entity::setPosition(const CCPoint& pPosition)
{
    CCSprite::setPosition(ccp(pPosition.x + this->mWidth / 2, pPosition.y - this->mHeight / 2));
}

void Entity::setCenterPosition(int pX, int pY)
{
    CCSprite::setPosition(ccp(pX, pY));
}

/**
 *
 * Take care about EntityManager
 *
 */

Entity* Entity::create()
{
	this->setVisible(true);

	return this;
}

void Entity::destroy(bool pManage)
{
	this->setVisible(false);

	if(pManage)
	{
		if(this->hasEntityManager())
		{
			this->getEntityManager()->destroy(this->id);
		}
	}
}

void Entity::destroy()
{
	this->destroy(true);
}

void Entity::setEntityManager(EntityManager* pEntityManager)
{
	this->mEntityManager = pEntityManager;
}

EntityManager* Entity::getEntityManager()
{
	return this->mEntityManager;
}

bool Entity::hasEntityManager()
{
	return this->mEntityManager != NULL;
}

void Entity::setEntityManagerId(int pId)
{
	this->id = pId;
}

int Entity::getEntityManagerId()
{
	return this->id;
}

/**
 *
 * Take care about animation
 *
 */

int Entity::getCurrentFrameIndex()
{
	return this->mCurrentFrameIndex;
}

void Entity::setCurrentFrameIndex(int pIndex)
{
	if(pIndex < this->mHorizontalFramesCount * this->mVerticalFramesCount && pIndex >= 0)
	{
		this->setTextureRect(CCRectMake(this->mFramesCoordinatesX[pIndex], this->mFramesCoordinatesY[pIndex], this->mWidth / this->mHorizontalFramesCount, this->mHeight / this->mVerticalFramesCount));

		this->mCurrentFrameIndex = pIndex;
	}
	else
	{
		this->setCurrentFrameIndex(0);
	}
}

void Entity::nextFrameIndex()
{
	int potencialNextFrame = this->getCurrentFrameIndex() + 1;

	this->setCurrentFrameIndex(potencialNextFrame > this->mFramesCount ? 0 : potencialNextFrame);
}

void Entity::changeTexture(Texture* pTexture)
{
	CCRect textureRectanle = CCRect(0, 0, pTexture->getTexture()->getContentSize().width, pTexture->getTexture()->getContentSize().height);

	this->setTexture(pTexture->getTexture());
	this->setTextureRect(textureRectanle);

	this->mWidth  = this->getTextureRect().size.width;
	this->mHeight = this->getTextureRect().size.height;

	this->mFrameWidth = this->mWidth / pTexture->mHorizontalFramesCount;
	this->mFrameHeight = this->mHeight / pTexture->mVerticalFramesCount; 

	this->mFramesCount = pTexture->mHorizontalFramesCount * pTexture->mVerticalFramesCount;

	this->mHorizontalFramesCount = pTexture->mHorizontalFramesCount;
	this->mVerticalFramesCount   = pTexture->mVerticalFramesCount;

	int counter = 0;

	for(int i = 0; i < this->mVerticalFramesCount; i++)
	{
		for(int j = 0; j < this->mHorizontalFramesCount; j++, counter++)
		{
			this->mFramesCoordinatesX[counter] = j * (this->mWidth / this->mHorizontalFramesCount);
			this->mFramesCoordinatesY[counter] = i * (this->mHeight / this->mVerticalFramesCount);
		}
	}

	this->setCurrentFrameIndex(0);
}

/**
 *
 * Checing for touch detector
 *
 */

void Entity::onEnter()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCSprite::onEnter();
}

void Entity::onExit()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}

bool Entity::ccTouchBegan(CCTouch* touch, CCEvent* event)
		{
	if(!this->mIsRegisterAsTouchable || !this->isVisible() || !this->getParent()->isVisible())
	{
		return false;
	}

	if(containsTouchLocation(touch))
	{
		this->mWasTouched = true;

		this->runAction(CCScaleTo::create(this->mAnimationScaleDownTime, this->mAnimationScaleDownFactor));

		return true;
	}

	return false;
}

void Entity::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	if(!containsTouchLocation(touch))
	{
		if(this->mWasTouched)
		{
		if(this->getScale() < this->mAnimationScaleUpFactor)
			{
				this->runAction(CCScaleTo::create(this->mAnimationScaleUpTime, this->mAnimationScaleUpFactor));

				this->mWasTouched = false;
			}
		}
	}
}

void Entity::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	if(this->mWasTouched)
	{
		this->onTouch(touch, event);

		this->runAction(CCScaleTo::create(this->mAnimationScaleUpTime, this->mAnimationScaleUpFactor));
	}

	this->mWasTouched = false;
}

bool Entity::containsTouchLocation(CCTouch* touch)
{
	return CCRectMake(-this->mFrameWidth/ 2, -this->mFrameHeight / 2, this->mFrameWidth, this->mFrameHeight).containsPoint(convertTouchToNodeSpaceAR(touch));
}

void Entity::setRegisterAsTouchable(bool pTouchable)
{
	this->mIsRegisterAsTouchable = pTouchable;
}

void Entity::onTouch(CCTouch* touch, CCEvent* event)
{
}

void Entity::update(float pDeltaTime)
{
}

/**
 *
 * Let's take care about object copy
 *
 */

Entity* Entity::deepCopy()
{
	return this;
}

#endif