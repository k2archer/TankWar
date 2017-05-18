#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
// #include "proj.win32/Player.h"

class FirstBattle : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
	void setMap(const char* mapName);
	void addPlayer(const char* pszFileName, const char* objectPointName);
	void addEnemy(const char* pszFileName, const char* objectPointName);

	void update(float delta);
	void timeUpate(float dt);

	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

    // implement the "static node()" method manually
    CREATE_FUNC(FirstBattle);

private:
	CCTMXTiledMap* _map;
};

#endif // __HELLOWORLD_SCENE_H__
