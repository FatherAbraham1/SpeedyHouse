#ifndef CONST_MAINMENU
#define CONST_MAINMENU

#include "MainMenu.h"

MainMenu::MainMenu(void)
{
	this->mBackground1 = new Entity("main-menu-bg.png");
	this->mBackground2 = new Entity("main-menu-bg-spots.png");

	this->mShopButton = new Entity("main-menu-btn-shop.png");
	this->mAchievementsButton = new Entity("main-menu-btn-achievement.png");

	this->mPlayButtonBackground	= new Entity("main-menu-btn-play-bg.png");
	this->mPlayButton = new PlayButton("main-menu-btn-play.png", this);

	this->mBackground1->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
	this->mBackground2->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
	this->mShopButton->setCenterPosition(Options::CAMERA_CENTER_X + Utils::coord(50), Options::CAMERA_CENTER_Y - Utils::coord(50));
	this->mAchievementsButton->setCenterPosition(Options::CAMERA_CENTER_X - Utils::coord(50), Options::CAMERA_CENTER_Y - Utils::coord(50));
	this->mPlayButtonBackground->setCenterPosition(Options::CAMERA_CENTER_X, Options::CAMERA_CENTER_Y);
	this->mPlayButton->setCenterPosition(Options::CAMERA_CENTER_X + Utils::coord(5), Options::CAMERA_CENTER_Y - Utils::coord(1));

	this->addChild(this->mBackground1);
	this->addChild(this->mBackground2);
	this->addChild(this->mShopButton);
	this->addChild(this->mAchievementsButton);
	this->addChild(this->mPlayButtonBackground);
	this->addChild(this->mPlayButton);

	//this->mSocialButtonsBackground 	= new Entity(Options::SCREEN_WIDTH - 120, 40, "main-menu-soc-bg.png", this);
	//this->mMoreGamesButton 			= new Entity(Options::SCREEN_WIDTH - 178, 45, "main-menu-btn-more.png", this);
	//this->mFacebookButton 			= new Entity(Options::SCREEN_WIDTH - 123, 42, "main-menu-btn-fb.png", this);
	//this->mTwitterButton 			= new Entity(Options::SCREEN_WIDTH - 67, 45, "main-menu-btn-tw.png", this);

	//this->mSoundButton 				= new SoundButton(			 "main-menu-btn-sound-sprite.png", 1, 2, this->mBackground2);
	//this->mMusicButton 				= new MusicButton(			 "main-menu-btn-melody-sprite.png", 1, 2, this->mBackground2);
	//this->mCreditsButton 			= new CreditsButton(		 "main-menu-btn-credits.png", this->mBackground2);

	//this->mSettingsButtonBackground = new Entity(70, 40, "main-menu-btn-settings-bg.png", this);
	//this->mSettingsButton 			= new SettingsButton(67, 46, "main-menu-btn-settings.png", this, this);

	//this->mBestScorePanel 			= new Entity(0, Options::SCREEN_CENTER_Y, "main-menu-best-score-popup.png", this);

									  //new Entity(150, 240, "main-menu-name-s-first-bg.png", this->mBackground2);
									  //new Entity(190, 260, "main-menu-name-i-bg.png", this->mBackground2);
									  //new Entity(240, 270, "main-menu-name-g-bg.png", this->mBackground2);
									  //new Entity(290, 260, "main-menu-name-n-bg.png", this->mBackground2);
									  //new Entity(340, 230, "main-menu-name-s-last-bg.png", this->mBackground2);

	/**
	 *
	 * Popup screen management
	 *
	 */

	//this->mDifficultScreen = new Difficult(this);
}

#endif