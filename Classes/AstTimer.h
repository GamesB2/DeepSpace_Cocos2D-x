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

private:
	cocos2d::Label* _timerLabel;
	cocos2d::Node*  _rootNode;
	std::string _timeElapsed;
	cocos2d::LabelBMFont


	int seconds;
	int minutes;
};

