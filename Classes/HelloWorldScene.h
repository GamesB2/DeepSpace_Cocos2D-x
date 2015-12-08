#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Asteroid.h"
#include "game_player.h"
#include "GameManager.h"
#include "ui/CocosGUI.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	virtual void update(float);

	bool getTouchTarget();

	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);

	cocos2d::Sprite*        game_Ship;
	cocos2d::Vec2			trajectory;

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	cocos2d::Sprite*        invisibleTarget;

	cocos2d::Sprite*        visibleTarget;
	cocos2d::ui::Button*    startButton;
	bool targetingOnline;
	bool _gameStart;
};

#endif // __HELLOWORLD_SCENE_H__
