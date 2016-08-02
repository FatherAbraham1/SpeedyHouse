#ifndef CONST_DIFICULT_H
#define CONST_DIFICULT_H

#include "cocos2d.h"

#include "PopupScreen.h"
#include "Utils.h"

using namespace cocos2d;

class Difficult : public PopupScreen
{
	class ChoiseButton : public Entity
	{
		protected:
			float mAnimationTime;
			float mAnimationElapsedTime;
			float mAnimationPosition;

			bool mIsAnimationReverse;

			CCNode* mParent;
			CCNode* mParentClass;

		public:
			ChoiseButton(const char* pszFileName, CCNode* pParent, CCNode* pParentClass) :
				Entity(pszFileName, pParent)
				{
					this->setRegisterAsTouchable(true);

					this->mIsAnimationReverse = false;

					this->mAnimationElapsedTime = 1000;
					this->mAnimationTime = Utils::randomf(1.4, 3.5);

					this->mAnimationPosition = 0;

					this->mParent = pParent;
					this->mParentClass = pParentClass;
				};

			virtual void update(float pDeltaTime)
			{
				if(this->mAnimationPosition == 0)
				{
					this->mAnimationPosition = this->getPosition().y;
				}
				else
				{
					this->mAnimationElapsedTime += pDeltaTime;

					if(this->mAnimationElapsedTime >= this->mAnimationTime)
					{
						this->mAnimationElapsedTime = 0;

						if(this->mIsAnimationReverse)
						{
							this->runAction(CCMoveTo::create(this->mAnimationTime, ccp(this->getPosition().x, this->mAnimationPosition + 5)));
						}
						else
						{
							this->runAction(CCMoveTo::create(this->mAnimationTime, ccp(this->getPosition().x, this->mAnimationPosition - 5)));
						}

						this->mIsAnimationReverse = !this->mIsAnimationReverse;
					}
				}
			}
	};

	class EasyButton : public ChoiseButton
	{
		public:
			EasyButton(const char* pszFileName, CCNode* pParent, CCNode* pParentClass) :
				ChoiseButton(pszFileName, pParent, pParentClass)
				{
				};

			void onTouch(CCTouch* touch, CCEvent* event)
			{
			}
	};

	class NormalButton : public ChoiseButton
	{
		public:
			NormalButton(const char* pszFileName, CCNode* pParent, CCNode* pParentClass) :
				ChoiseButton(pszFileName, pParent, pParentClass)
				{
				};

			void onTouch(CCTouch* touch, CCEvent* event)
			{
			}
	};

	class HardButton : public ChoiseButton
	{
		public:
			HardButton(const char* pszFileName, CCNode* pParent, CCNode* pParentClass) :
				ChoiseButton(pszFileName, pParent, pParentClass)
				{
				};

			void onTouch(CCTouch* touch, CCEvent* event)
			{
			}
	};

	class BackButton : public Entity
	{
		protected:
			Difficult* mParentClass;

		public:
			BackButton(const char* pszFileName, CCNode* pParent, Difficult* pParentClass) :
				Entity(pszFileName, pParent)
				{
					this->mParentClass = pParentClass;

					this->setRegisterAsTouchable(true);
				};

			void onTouch(CCTouch* touch, CCEvent* event)
			{
				this->mParentClass->hide();
			}
	};

	private:
		EasyButton* mEasyButton;
		NormalButton* mNormalButton;
		HardButton* mHardButton;

		BackButton* mBackButton;

	public:
		Difficult();
		Difficult(CCNode* pParent);

		virtual void init(CCNode* pParent);
};

#endif