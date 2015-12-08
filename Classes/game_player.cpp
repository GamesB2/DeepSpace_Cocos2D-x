#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "game_player.h"

USING_NS_CC;
using namespace cocos2d;
//////////////////////

game_player::game_player()
{
	this->init();
}

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
	auto rootNode = CSLoader::createNode("PlayerNode.csb");
	addChild(rootNode);

	//Position this container at left,centre. Anchor point should also be (0.0f, 0.5f).
	auto winSize = Director::getInstance()->getVisibleSize();
	this->setPosition(Vec2(0.0f, 0.0f));
	this->setAnchorPoint(Vec2(winSize.width/2, winSize.height/2));
	this->scheduleUpdate();

	_winSize = winSize;

	//Set references to the Sprite objects 
	game_Ship = Sprite::create("PlayerShip.png");
	rootNode->addChild(game_Ship);

	game_Ship->setPosition(_winSize.width / 2, _winSize.height / 2);
	_currentSpeed = 0.0f;
	_maxSpeed = 60.0f;
	_currentPosition = game_Ship->getPosition();
	_endPoint = Vec2(-1.0f, -1.0f);
	_endpointReached = true;
	_rotation = 0;
	_trajectory = Vec2(0, 0);
	_dead = false;

	return true;
}

void game_player::update (float deltaTime)
{
	if (GameManager::sharedGameManager()->isGameLive)
	{
		if (_dead == false)
		{
			if (_endPoint != Vec2(-1.0f,1.0f))
			{
				if (!_endpointReached)
				{
					_currentSpeed = _currentSpeed + 1;
					if (_currentSpeed >= _maxSpeed)
					{
						_currentSpeed = _maxSpeed;
					}
				}
				else if (_endpointReached)
				{
					_currentSpeed = _currentSpeed - 1;
					if (_currentSpeed <= 0)
					{
						_currentSpeed = 0;
					}
				}
				_currentPosition = game_Ship->getPosition();
				game_Ship->setPosition(_currentPosition + (_trajectory * _currentSpeed) * deltaTime);

				if (game_Ship->getBoundingBox().containsPoint(_endPoint))
				{
					_endpointReached = true;
				}
			}
		}
	}
}

game_player::~game_player()
{

}

bool game_player::asteroidCollision(cocos2d::Rect collisionBoxtoCheck)
{
	if (game_Ship->getBoundingBox().intersectsRect(collisionBoxtoCheck))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void game_player::reset()
{
	game_Ship->setPosition(_winSize.width / 2, _winSize.height / 2);
	_currentSpeed = 0.0f;
	_maxSpeed = 60.0f;
	_currentPosition = game_Ship->getPosition();
	_endPoint = nullptr;
	_endpointReached = true;
	_rotation = 0;
	_trajectory = (0, 0);
	_dead = false;
}

void game_player::SetTrajectory(cocos2d::Vec2 touchPoint)
{
	_endPoint = touchPoint;
	_trajectory = (_endPoint - _currentPosition);
	_rotation = CCPoint::dot(_currentPosition, _trajectory);
	game_Ship->setRotation(_rotation);
	_trajectory.normalize();
	_endpointReached = false;
}
