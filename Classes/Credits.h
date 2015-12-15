#pragma once 
#include "cocos2d.h"
#include "Asteroid.h"
#include "game_player.h"
#include "GameManager.h"
#include "ui/CocosGUI.h"

class Credits : public cocos2d::Layer
{
private:
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Credits);
	void SetUpTextboxes();
	cocos2d::ui::Button*  backButton;
	cocos2d::Node* rootNode;
	cocos2d::Label* labels[8];
};

