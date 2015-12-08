#include "Asteroid.h"
#include "cocostudio\CocoStudio.h"
#include <stdlib.h>     
#include <time.h>  

using namespace cocos2d;
// debug stuff
char array[10];

Asteroid::Asteroid(int num)
{
	_initialStart = num;
	this->init();
}

Asteroid::~Asteroid()
{

}

Asteroid* Asteroid::create()
{
	Asteroid* _asteroid = new Asteroid(_initialStart);
	if (_asteroid->init())
	{
		_asteroid->autorelease();
		return _asteroid;
	}
	else
	{
		CC_SAFE_DELETE(_asteroid);
		return nullptr;
	}
}

bool Asteroid::init()
{
	if (!Node::init())
	{
		return false;
	}

	auto _rootNode = CSLoader::createNode("Asteroid.csb");
	addChild(_rootNode);

	srand(time(NULL));

	_asteroidRect = new Rect();

	_winSize = Director::getInstance()->getVisibleSize();

	_startpoints[1] = Vec2(_winSize.width / 3, -50.0f);
	_startpoints[2] = Vec2((_winSize.width / 3) * 2, -50.0f);
	_startpoints[3] = Vec2(_winSize.width + 50, (_winSize.height / 3));
	_startpoints[4] = Vec2(_winSize.width + 50, (_winSize.height / 3) * 2);
	_startpoints[5] = Vec2((_winSize.width / 3), _winSize.height + 50);
	_startpoints[6] = Vec2((_winSize.width / 3) * 2, _winSize.height + 50);
	_startpoints[7] = Vec2(-50.0f, (_winSize.height / 3));
	_startpoints[8] = Vec2(-50.0f, (_winSize.height / 3) * 2);
	
	this->setPosition(0.0,0.0);
	this->setAnchorPoint(Vec2(_winSize.width/2, _winSize.height/2));
	this->scheduleUpdate();

	_sprite = Sprite::create("Asteroids_32x32_003.png");
	_rootNode->addChild(_sprite);
	_sprite->setPosition(_startpoints[_initialStart]);
	CreateEndPoint(_initialStart);

	_asteroidRect->size = _sprite->getBoundingBox().size;

	_collisionAsteroid = false;

	_speed = 150;
	_rotation = 0;
	return true;

}

void Asteroid::update(float deltaTime)
{
	_currentPoint = Vec2(_sprite->getPositionX(), _sprite->getPositionY());

	_sprite->setPosition(_currentPoint + (_trajectory * _speed) * deltaTime);

	CheckOutsideScreen();

	_rotation = _rotation + 1;

	_sprite->setRotation(_rotation);

	_asteroidRect->origin = convertToWorldSpaceAR(_sprite->getBoundingBox().origin);
	
	if (_rotation == 360)
	{
		_rotation = 0;
	}

	if (_outsideScreen == true)
	{
		Reset();
		_outsideScreen = false;
	}
}

void Asteroid::CheckOutsideScreen()
{
	if (_sprite->getPositionX() > (_winSize.width + 80.0f) || _sprite->getPositionY() > (_winSize.height + 80.0f))
	{
		_outsideScreen = true;
	}
	if (_sprite->getPositionY() < -80.0f || (_sprite->getPositionX() < -80.0f))
	{
		_outsideScreen = true;
	}
}

void Asteroid::Reset()
{
	_rotation = 0;
	_sprite->setPosition(CreateStartPoint());
}

cocos2d::Vec2 Asteroid::CreateStartPoint()
{
	_randStart = cocos2d::RandomHelper::random_int(1, 8);
	CreateEndPoint(_randStart);
	return _startpoints[_randStart];
}

void Asteroid::CreateEndPoint(int start)
{
	// Bottom start
	if (start == 1 || start == 2)
	{
		_randEnd = ((float)rand() / (float)(RAND_MAX)* _winSize.width);
		_endPoint = Vec2(_randEnd, _winSize.height + 100);
	}
	// Right start
	if (start == 3 || start == 4)
	{
		_randEnd = ((float)rand() / (float)(RAND_MAX)* _winSize.height);
		_endPoint = Vec2(-100.0f, _randEnd);
	}
	// Top start
	if (start == 5 || start == 6)
	{
		_randEnd = ((float)rand() / (float)(RAND_MAX)* _winSize.width);
		_endPoint = Vec2(_randEnd, -100.0f);
	}
	// Left start
	if (start == 7 || start == 8)
	{
		_randEnd = ((float)rand() / (float)(RAND_MAX)* _winSize.height);
		_endPoint = Vec2(_winSize.width + 100, _randEnd);
	}

	SetTrajectory();
}

void Asteroid::SetTrajectory()
{
	_trajectory = (_endPoint - _currentPoint);
	_trajectory.normalize();
}

bool Asteroid::HasCollidedWithAsteroid(cocos2d::Rect* collisionBoxToCheck)
{
	if (!_collisionAsteroid)
	{
		if (_asteroidRect->intersectsRect(*collisionBoxToCheck))
		{
			_collisionAsteroid = true;
			return true;
		}
	}

	if (!_asteroidRect->intersectsRect(*collisionBoxToCheck))
	{
		_collisionAsteroid = false;
	}
	
	return false;
}

Rect* Asteroid::GetBoundingBox()
{
	return _asteroidRect;
}

void Asteroid::AsteroidBounce(Vec2 bounceVector, Vec2 collisionPos)
{
	Vec2 n = _currentPoint - collisionPos;
	n.normalize();

	float a1 = _trajectory.dot(n);
	float a2 = bounceVector.dot(n);

	float optimizedP = (2.0 * (a1 - a2)) / 2;

	_trajectory = _trajectory - optimizedP * n;
}

Vec2 Asteroid::GetVec()
{
	return _trajectory;
}

Vec2 Asteroid::GetPos()
{
	return _currentPoint;
}