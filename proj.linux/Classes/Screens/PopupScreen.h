#ifndef CONST_POPUPSCREEN_H
#define CONST_POPUPSCREEN_H

#include "cocos2d.h"

#include "Entity.h"
#include "EntityManager.h"
#include "Texture.h"
#include "Utils.h"

using namespace cocos2d;

class PopupScreen : public CCLayer
{
	class Spiral : public Entity
	{
		protected:
			float mAnimationScaleTime;

			float mAnimationLifeTime;
			float mAnimationLifeTimeElaped;

			float mAnimationHideX;
			float mAnimationHideY;
			float mAnimationHideSpeed;

			float mAnimationRotationSpeed;

			bool isAnimationLifeTimeElapsed;
			bool isAnimationHide;

		public:
			Spiral() :
				Entity()
				{
				};

			Spiral(const char* pszFileName) :
				Entity(pszFileName)
				{
				};

			Spiral(const char* pszFileName, int pHorizontalFramesCount, int pVerticalFramesCount) :
				Entity(pszFileName, pHorizontalFramesCount, pVerticalFramesCount)
				{
				};

			void show()
			{
				this->setPosition(ccp(Utils::randomf(0, 480), Utils::randomf(0, 320)));
				this->setCurrentFrameIndex(Utils::randomf(0, 4));

				this->mAnimationRotationSpeed = Utils::randomf(-2.0, 2.0);
				this->mAnimationScaleTime = Utils::randomf(1.0, 8.0);
				this->mAnimationLifeTime = this->mAnimationScaleTime + Utils::randomf(0.5, 6.0);
				this->mAnimationLifeTimeElaped = 0;
				this->mAnimationHideSpeed = 15;

				this->isAnimationLifeTimeElapsed = false;
				this->isAnimationHide = false;

				this->setScale(0);

				this->runAction(CCScaleTo::create(this->mAnimationScaleTime, 1));
			}

			void hide()
			{
				this->isAnimationHide = true;

				this->mAnimationHideX = this->getPosition().x > 240 ? this->mAnimationHideSpeed : -this->mAnimationHideSpeed;
				this->mAnimationHideY = this->getPosition().y > 160 ? this->mAnimationHideSpeed : -this->mAnimationHideSpeed;
			}

			virtual Entity* deepCopy()
			{
				return new Spiral("blank.png");
			}

			virtual void update(float pDeltaTime)
			{
				if(this->isVisible())
				{
					this->setRotation(this->getRotation() + this->mAnimationRotationSpeed);

					this->mAnimationLifeTimeElaped += pDeltaTime;

					if(this->mAnimationLifeTimeElaped >= this->mAnimationLifeTime && !this->isAnimationLifeTimeElapsed)
					{
						this->isAnimationLifeTimeElapsed = true;

						this->runAction(CCScaleTo::create(this->mAnimationScaleTime, 0));
					}

					if(this->isAnimationLifeTimeElapsed)
					{
						if(this->getScale() <= 0)
						{
							this->destroy();
						}
					}

					if(this->isAnimationHide)
					{
						this->setPosition(ccp(this->getPosition().x + this->mAnimationHideX, this->getPosition().y + this->mAnimationHideY));

						if(this->getPosition().x < 0 || this->getPosition().x > 480 || this->getPosition().y < 0 || this->getPosition().y > 320)
						{
							this->destroy();
						}
					}
				}
			}
	};
		
	protected:
		float mAnimationTimeElapsed;
		float mAnimationTimeToHide;
		bool mAnimationNeedShow;
			
		float mElementsCreateTime;
		float mElementsCreateTimeElapsed;

		bool mAnimationNeedHide;
		bool mIsAttached;

		Entity* mBackgroundCircle;
		Entity* mBackground;
		
		EntityManager* mAnimationElements;

		Texture* mAnimationElementsTexture1;
		Texture* mAnimationElementsTexture2;
		Texture* mAnimationElementsTexture3;
		Texture* mAnimationElementsTexture4;
		Texture* mAnimationElementsTexture5;
		Texture* mAnimationElementsTexture6;
		Texture* mAnimationElementsTexture7;

	public:
		PopupScreen();
		PopupScreen(CCNode* pParent);

		virtual void init(CCNode* pParent);
		
		void create();
		void show();
		void hide();

		void onShowStarted();
		void onShowFinished();

		void onCloseStarted();
		void onCloseFinished();

		virtual void update(float pDeltaTime);
		virtual void draw();

		EntityManager* getPopupScreenElements();
};

#endif