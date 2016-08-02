#include "cocos2d.h"
#include "VisibleRect.cpp"
#include "Test.cpp"
#include "./Entities/Car.cpp"



Settings settings;

class Test;
class Box2DView : public CCLayer
{
    Car*        mCar;
public:
    Box2DView(CCScene* pScene) {

    CCDirector* pDirector = CCDirector::sharedDirector();
    CCPoint visibleOrigin = pDirector->getVisibleOrigin();
    CCSize visibleSize = pDirector->getVisibleSize();

    this->setTouchEnabled(true);
    this->setKeypadEnabled(true);

    schedule(schedule_selector(Box2DView::update));

    mCar = new Car(pScene);

    this->autorelease();

    this->setScale(35);
    this->setAnchorPoint(ccp(0, 0));
    this->setPosition(
            ccp(visibleOrigin.x + visibleSize.width / 2,
                    visibleOrigin.y + visibleSize.height / 3));
    }



void registerWithTouchDispatcher() {
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, -10, true);
}
   
bool ccTouchBegan(CCTouch* touch, CCEvent* event) {
    CCPoint touchLocation = touch->getLocation();

    CCPoint nodePosition = convertToNodeSpace(touchLocation);

    return mCar->MouseDown(b2Vec2(nodePosition.x, nodePosition.y));
}

void ccTouchMoved(CCTouch* touch, CCEvent* event) {
    CCPoint touchLocation = touch->getLocation();
    CCPoint nodePosition = convertToNodeSpace(touchLocation);

    mCar->MouseMove(b2Vec2(nodePosition.x, nodePosition.y));
}

void ccTouchEnded(CCTouch* touch, CCEvent* event) {
    CCPoint touchLocation = touch->getLocation();
    CCPoint nodePosition = convertToNodeSpace(touchLocation);

    mCar->MouseUp(b2Vec2(nodePosition.x, nodePosition.y));
}




    void update(float pDeltaTime) {

    mCar->Step(&settings);
    }

    void draw() {

    CCLayer::draw();

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position);

    kmGLPushMatrix();

    mCar->m_world->DrawDebugData();

    kmGLPopMatrix();

    CHECK_GL_ERROR_DEBUG();
    }
};









class Level : public Screen
{
public:
	Level() {

Box2DView* view = new Box2DView(this);
    
    this->addChild(view, 10);
    }
};