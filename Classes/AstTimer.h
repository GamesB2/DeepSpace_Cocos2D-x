#pragma once
#include "HelloWorldScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio\CocoStudio.h"

class AstTimer : public cocos2d::Node
{
public:
	AstTimer();
	~AstTimer();

	AstTimer* create();
	virtual bool init() override;
	virtual void update(float);
	void reset();

private:
	cocos2d::Label* _timerLabel;
	cocos2d::Node*  _rootNode;
	std::string _timeElapsed;

	int seconds;
	int minutes;
};

