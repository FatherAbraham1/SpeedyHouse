#ifndef CONST_MAINMENU_H
#define CONST_MAINMENU_H

#include "cocos2d.h"

#include "Screen.h"
#include "Difficult.h"
#include "Options.h"

using namespace cocos2d;

class MainMenu : public Screen
{
	class SoundButton : public Entity
	{
		protected:
			int mAnimationPositionX1;
			int mAnimationPositionX2;

			float mAnimationPositionTime;

			bool mIsMoved;

		public:
			SoundButton(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, CCNode* pParent) :
				Entity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount, pParent)
				{
					this->setRegisterAsTouchable(true);

					this->mAnimationPositionX1 = 40;
					this->mAnimationPositionX2 = 100;

					this->mAnimationPositionTime = 0.3;

					this->mIsMoved = false;

					this->setPosition(ccp(mAnimationPositionX1, 40));
				};

			void onTouch(CCTouch* touch, CCEvent* event)
			{
				this->nextFrameIndex();
			}

			void move()
			{
				if(this->mIsMoved)
				{
					this->runAction(CCMoveTo::create(this->mAnimationPositionTime, ccp(this->mAnimationPositionX1, 40)));

					this->mIsMoved = false;
				}
				else
				{
					this->runAction(CCMoveTo::create(this->mAnimationPositionTime, ccp(this->mAnimationPositionX2, 40)));

					this->mIsMoved = true;
				}
			}
	};

	class MusicButton : public Entity
	{
		protected:
			int mAnimationPositionX1;
			int mAnimationPositionX2;

			float mAnimationPositionTime;

			bool mIsMoved;

		public:
			MusicButton(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount, CCNode* pParent) :
				Entity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount, pParent)
				{
					this->setRegisterAsTouchable(true);

					this->mAnimationPositionX1 = 40;
					this->mAnimationPositionX2 = 150;

					this->mAnimationPositionTime = 0.3;

					this->mIsMoved = false;

					this->setPosition(ccp(mAnimationPositionX1, 40));
				};

			void onTouch(CCTouch* touch, CCEvent* event)
			{
				this->nextFrameIndex();
			}

			void move()
			{
				if(this->mIsMoved)
				{
					this->runAction(CCMoveTo::create(this->mAnimationPositionTime, ccp(this->mAnimationPositionX1, 40)));

					this->mIsMoved = false;
				}
				else
				{
					this->runAction(CCMoveTo::create(this->mAnimationPositionTime, ccp(this->mAnimationPositionX2, 40)));

					this->mIsMoved = true;
				}
			}
	};

	class CreditsButton : public Entity
	{
		protected:
			int mAnimationPositionX1;
			int mAnimationPositionX2;

			float mAnimationPositionTime;

			bool mIsMoved;

		public:
			CreditsButton(const char* pszFileName, CCNode* pParent) :
				Entity(pszFileName, 1, 1, pParent)
				{
					this->setRegisterAsTouchable(true);

					this->mAnimationPositionX1 = 40;
					this->mAnimationPositionX2 = 200;

					this->mAnimationPositionTime = 0.3;

					this->mIsMoved = false;

					this->setPosition(ccp(mAnimationPositionX1, 40));
				};

			void onTouch(CCTouch* touch, CCEvent* event)
			{
				this->nextFrameIndex();
			}

			void move()
			{
				if(this->mIsMoved)
				{
					this->runAction(CCMoveTo::create(this->mAnimationPositionTime, ccp(this->mAnimationPositionX1, 40)));

					this->mIsMoved = false;
				}
				else
				{
					this->runAction(CCMoveTo::create(this->mAnimationPositionTime, ccp(this->mAnimationPositionX2, 40)));

					this->mIsMoved = true;
				}
			}
	};

	class SettingsButton : public Entity
	{
		protected:
			float mAnimationRotationAngle;
			float mAnimationRotationTime;

			bool mIsRotated;

			MainMenu* mParentClass;
		public:
			SettingsButton(const char* pszFileName, MainMenu* pParentClass, CCNode* pParent) :
				Entity(pszFileName, 1, 1, pParent)
				{
					this->mParentClass = pParentClass;

					this->setRegisterAsTouchable(true);

					this->mAnimationRotationTime  = 0.3;
					this->mAnimationRotationAngle = 720.0;

					this->mIsRotated = false;
				};

			void onTouch(CCTouch* touch, CCEvent* event)
			{
				if(this->mIsRotated)
				{
					this->runAction(CCRotateTo::create(this->mAnimationRotationTime, -this->mAnimationRotationAngle));

					this->mParentClass->mSoundButton->move();
					this->mParentClass->mMusicButton->move();
					this->mParentClass->mCreditsButton->move();

					this->mIsRotated = false;
				}
				else
				{
					this->runAction(CCRotateTo::create(this->mAnimationRotationTime, this->mAnimationRotationAngle));

					this->mParentClass->mSoundButton->move();
					this->mParentClass->mMusicButton->move();
					this->mParentClass->mCreditsButton->move();

					this->mIsRotated = true;
				}
			}
	};

	class PlayButton : public Entity
	{
		protected:
			MainMenu* mParentClass;

		public:
			PlayButton(const char* pszFileName, MainMenu* pParentClass) :
				Entity(pszFileName)
				{
					this->mParentClass = pParentClass;

					this->setRegisterAsTouchable(true);
				};

			void onTouch(CCTouch* touch, CCEvent* event)
			{
				this->mParentClass->mDifficultScreen->show();
			}
	};


	public:
		Entity* mBackground1;
		Entity* mBackground2;
		Entity* mSocialButtonsBackground;

		Entity* mPlayButtonBackground;
		PlayButton* mPlayButton;
		Entity* mShopButton;
		Entity* mAchievementsButton;
		SettingsButton* mSettingsButton;
		Entity* mSettingsButtonBackground;
		Entity* mMoreGamesButton;
		Entity* mTwitterButton;
		Entity* mFacebookButton;
		SoundButton* mSoundButton;
		MusicButton* mMusicButton;
		CreditsButton* mCreditsButton;
		Entity* mBestScorePanel;

		Difficult* mDifficultScreen;

		MainMenu();
};

#endif