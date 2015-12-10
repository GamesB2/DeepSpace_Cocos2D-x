#include "Credits.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

cocos2d::Scene* Credits::createScene()
{
	// 'scene' is an autorelease object
	auto scene = cocos2d::Scene::create();

	// 'layer' is an autorelease object
	auto layer = Credits::create();// this method goes through the cocos .dll and calls your init using the CREATE_FUC()

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Credits::init()
{
	if (!Layer::init())
	{
		return false;
	}

	rootNode = CSLoader::createNode("Credits.csb");
	addChild(rootNode);
	SetUpTextboxes();

	backButton = static_cast<ui::Button*>(rootNode->getChildByName("Backbutton"));
	backButton->setTitleText("Back");

	backButton->setVisible(true);
	backButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			Director::getInstance()->popToRootScene();
			break;
		case ui::Widget::TouchEventType::ENDED:
			break;
		case ui::Widget::TouchEventType::CANCELED:
			break;
		case ui::Widget::TouchEventType::MOVED:
			break;
		}
	}
	);

	return true;
}

void Credits::SetUpTextboxes()
{

	labels[0] = rootNode->getChildByName<Label*>("Title1");
	addChild(labels[0]);
	labels[1] = rootNode->getChildByName<Label*>("Title1");
	addChild(labels[1]);
	labels[2] = rootNode->getChildByName<Label*>("Title1");
	addChild(labels[2]);
	labels[3] = rootNode->getChildByName<Label*>("Title1");
	addChild(labels[3]);
	labels[4] = rootNode->getChildByName<Label*>("Title1");
	addChild(labels[4]);
	labels[5] = rootNode->getChildByName<Label*>("Title1");
	addChild(labels[5]);
}

