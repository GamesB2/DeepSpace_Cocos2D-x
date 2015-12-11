#pragma once
#include "HelloWorldScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio\CocoStudio.h"

class Timer : public cocos2d::Node
{
public:
	Timer();
	~Timer();

	Timer* create();
	virtual bool init() override;
	virtual void update(float);

private:
	cocos2d::Label* _timerLabel;
	cocos2d::Node*  _rootNode;
	cocos2d::String _timeElapsed;

	int seconds;
	int minutes;
};

