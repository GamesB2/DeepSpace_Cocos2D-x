#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Asteroid.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

	cocos2d::Vec2 createStartVector(); { return Vec2 }

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	cocos2d::Label* labelTouchInfo;
};

#endif // __HELLOWORLD_SCENE_H__
