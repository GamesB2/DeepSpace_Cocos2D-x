#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "game_player.h"

USING_NS_CC;
using namespace cocos2d;
//////////////////////


game_player* game_player::create()
{
	game_player* myNode = new game_player();
	if (myNode->init())
	{
		myNode->autorelease();
		return myNode;
	}
	else
	{
		CC_SAFE_DELETE(myNode);
		return nullptr;
	}
	return myNode;
}

//-------------------------------------------------------------------------

bool game_player::init()
{
	if (!Node::init())
	{
		return false;
	}

	//Load this object in from cocos studio.
	auto rootNode = CSLoader::createNode("Asteroid.csb");
	addChild(rootNode);

	//Position this container at left,centre. Anchor point should also be (0.0f, 0.5f).
	auto winSize = Director::getInstance()->getVisibleSize();
	this->setPosition(Vec2(0.0f, winSize.height*0.5f));
	this->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->scheduleUpdate();


	//Set references to the Sprite objects (pipes)
	game_Ship = (Sprite*)rootNode->getChildByName("game_Ship");

	_currentSpeed = 0.0f;
	_maxSpeed = 60.0f;
	_currentPosition = game_Ship->getPosition();
	_endPoint = nullptr;
	_endpointReached = true;
	_rotation = 0;

	return true;
}

void game_player::update (float updateTime)
{
	
}

game_player::game_player()
{
}



game_player::~game_player()
{

}
