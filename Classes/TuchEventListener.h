

#ifndef __TOUCH_CCONTROL_H__
#define __TOUCH_CCONTROL_H__

#include "cocos2d.h"
USING_NS_CC;

#include "CControl.h"

class TuchEventListener : public Controller
{
public:
	bool init();

	static TuchEventListener* create(CCLayer *scene);
	EventListenerTouchOneByOne* _listener;

	bool onTouchBegan(Touch *touch, Event *unused_event);
	bool onTouchEnded(Touch *touch, Event *unused_event);

	void addEventListenerByScene(EventDispatcher*  eventDispatcher);

	void setSpeed(int iSpeed);

	virtual void update(float dt);  // schedualUpdate();

private:
	LayerColor* keys[5];

	int m_iSpeed;

	bool key[5];
	int keyNum;

};

TuchEventListener* TuchEventListener::create(CCLayer *scene)
{
	TuchEventListener *pRet = new(std::nothrow) TuchEventListener();

	if (pRet && pRet->init())
	{
		scene->addChild(pRet->keys[0]);
		scene->addChild(pRet->keys[1]);
		scene->addChild(pRet->keys[2]);
		scene->addChild(pRet->keys[3]);
		scene->addChild(pRet->keys[4]);

		//pRet->addEventListenerByScene(scene);
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

void TuchEventListener::addEventListenerByScene(EventDispatcher*  eventDispatcher)
{
	eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, keys[0]);
	eventDispatcher->addEventListenerWithSceneGraphPriority(_listener->clone(), keys[1]);
	eventDispatcher->addEventListenerWithSceneGraphPriority(_listener->clone(), keys[2]);
	eventDispatcher->addEventListenerWithSceneGraphPriority(_listener->clone(), keys[3]);
	eventDispatcher->addEventListenerWithSceneGraphPriority(_listener->clone(), keys[4]);
}

bool TuchEventListener::init()
{
	/* 默认速度为0 */
	this->m_iSpeed = 0;

	/* 定时调用update */
	this->scheduleUpdate();

	keys[0] = LayerColor::create(Color4B::RED, 80, 80);
	keys[0]->setPosition(Vec2(160, 240));
	//addChild(pLayerUp);

	keys[1] = LayerColor::create(Color4B::GREEN, 80, 80);
	keys[1]->setPosition(Vec2(160, 80));
	//addChild(pLayerDown);

	keys[2] = LayerColor::create(Color4B::BLUE, 80, 80);
	keys[2]->setPosition(Vec2(80, 160));
	//addChild(pLayerLeft);

	keys[3] = LayerColor::create(Color4B::YELLOW, 80, 80);
	keys[3]->setPosition(Vec2(240, 160));
	//addChild(pLayerRight);

	keys[4] = LayerColor::create(Color4B::ORANGE, 100, 100);
	keys[4]->setPosition(Vec2(1100, 150));
	//addChild(pLayerRight);

	// 创建一个事件监听器类型为OneByOne的单点触摸
	_listener = EventListenerTouchOneByOne::create();

	// 设置是否吞没事件，在onTouchBegan方法返回true时吞没
	_listener->setSwallowTouches(true);
	_listener->onTouchBegan = CC_CALLBACK_2(TuchEventListener::onTouchBegan, this);
	_listener->onTouchEnded = CC_CALLBACK_2(TuchEventListener::onTouchEnded, this);

	return true;
}

bool TuchEventListener::onTouchBegan(Touch *touch, Event *unused_event)
{
	// 获取事件所绑定的 target 
	auto target = static_cast<Layer*>(unused_event->getCurrentTarget());
	if (target == nullptr) {
		return true;
	}

	// 获取当前点击点所在相对按钮的位置坐标
	// getLocation得到的是openGL坐标系，也就是世界坐标系
	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	// 点击范围判断检测
	if (rect.containsPoint(locationInNode))
	{
		log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
		target->setOpacity(180);

		Color3B c = target->getColor();
		if (c == Color4B::RED) {
			CCLOG("RED");
			if (!this->key[K_UP])
			{
				//CCLOG("KEY_DOWN VK_DOWN");
				m_controllerListener->Crun();
				m_controllerListener->CchangeDirection(UP);
				this->key[K_UP] = 1;
			}
		}
		else if (c == Color4B::GREEN) {
			CCLOG("GREEN");
			if (!this->key[K_DOWN])
			{
				//CCLOG("KEY_UP VK_DOWN");
				m_controllerListener->Crun();
				m_controllerListener->CchangeDirection(DOWN);
				this->key[K_DOWN] = 1;
			}
		}
		else if (c == Color4B::BLUE) {
			CCLOG("BLUE");
			if (!this->key[K_LEFT])
			{
				//CCLOG("KEY_DOWN VK_LEFT");
				m_controllerListener->Crun();
				m_controllerListener->CchangeDirection(LEFT);
				this->key[K_LEFT] = 1;
			}
		}
		else if (c == Color4B::YELLOW) {
			CCLOG("YELLOW");
			if (!this->key[K_RIGHT])
			{
				//CCLOG("KEY_DOWN VK_RIGHT");
				m_controllerListener->Crun();
				m_controllerListener->CchangeDirection(RIGHT);
				this->key[K_RIGHT] = 1;
			}
		}
		else if (c == Color4B::ORANGE) {
			CCLOG("GRAY");
			//CCLOG("VK_LCONTROL VK_DOWN");
			if (!this->key[K_LCONTROL]) {
				m_controllerListener->Cfire();
				this->key[K_LCONTROL] = true;
			}

		}
		return true;
	}
	return false;
}

bool TuchEventListener::onTouchEnded(Touch *touch, Event *unused_event)
{
	// 获取事件所绑定的 target 
	auto target = static_cast<Layer*>(unused_event->getCurrentTarget());
	if (target == nullptr) {
		return true;
	}

	// 获取当前点击点所在相对按钮的位置坐标
	// getLocation得到的是openGL坐标系，也就是世界坐标系
	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	// 点击范围判断检测
	if (rect.containsPoint(locationInNode))
	{
		log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
		target->setOpacity(180);

		Color3B c = target->getColor();
		if (c == Color4B::RED) {
			CCLOG("RED");
			if (this->key[K_UP])
			{
				//CCLOG("KEY_UP VK_DOWN");
				m_controllerListener->Cstop();
				this->key[K_UP] = 0;
			}
		}
		else if (c == Color4B::GREEN) {
			CCLOG("GREEN");
			if (this->key[K_DOWN])
			{
				//CCLOG("KEY_UP VK_DOWN");
				m_controllerListener->Cstop();
				this->key[K_DOWN] = 0;
			}
		}
		else if (c == Color4B::BLUE) {
			CCLOG("BLUE");
			if (this->key[K_LEFT])
			{
				//CCLOG("KEY_UP VK_LEFT");
				m_controllerListener->Cstop();
				this->key[K_LEFT] = 0;
			}
		}
		else if (c == Color4B::YELLOW) {
			CCLOG("YELLOW");
			if (this->key[K_RIGHT])
			{
				//CCLOG("KEY_UP VK_RIGHT");
				m_controllerListener->Cstop();
				this->key[K_RIGHT] = 0;
			}
		}
		else if (c == Color4B::ORANGE) {
			CCLOG("GRAY");
			//CCLOG("VK_LCONTROL VK_DOWN");
			if ( this->key[K_LCONTROL] )
				this->key[K_LCONTROL] = false;
		}
		return true;
	}
	return false;
}

void TuchEventListener::update(float dt)
{
	///* 增加移动对象的x坐标值 */
	Point pos = m_controllerListener->getTagPosition();

	//pos.x += m_iSpeed;
	pos += m_controllerListener->getiDirection();

	///* 被控制的对象 */
	m_controllerListener->setTagPosition(pos.x, pos.y);

}

void TuchEventListener::setSpeed(int iSpeed)
{
	this->m_iSpeed = iSpeed;
}

#endif // __TOUCH_CCONTROL_H__