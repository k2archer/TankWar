#ifndef __GMAINMENU_H__
#define __GMAINMENU_H__

#include "cocos2d.h"
USING_NS_CC;

class GMainMenu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuStartCallback(CCObject* pSender);
    void menu1PlayerCallback(CCObject* pSender);
    void menu2PlayerCallback(CCObject* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GMainMenu);
};

#endif //__GMAINMENU_H__

