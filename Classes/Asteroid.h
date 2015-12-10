#pragma once

#include "HelloWorldScene.h"
#include "cocos2d.h"

class Asteroid : public cocos2d::Node
{
public:
	// Object Constructors
	Asteroid(int num);
	~Asteroid();
	Asteroid* create();
	virtual bool init() override;

	// Update
	virtual void update(float);

	// Collision Detection
	bool CheckOutsideScreen();
	bool HasCollidedWithAsteroid(cocos2d::Rect* collisionBoxToCheck);

	// Movement
	void Reset();
	cocos2d::Vec2 CreateStartPoint();
	void CreateEndPoint(int start);
	void SetTrajectory();
	cocos2d::Rect* GetBoundingBox();
	void AsteroidBounce(cocos2d::Vec2 bounceVector, cocos2d::Vec2 collisionPos);
	cocos2d::Vec2 GetVec();
	cocos2d::Vec2 GetPos();

private:
	// Asteroid Variables
	float _rotation;
	float _speed;
	int   _randStart;
	float _randEnd;
	bool  _collisionAsteroid; 

	int   _initialStart;

	// Cocos Variables
	cocos2d::Sprite* _sprite;
	cocos2d::Node*	 _rootNode;
	cocos2d::Size	 _winSize;
	cocos2d::Vec2	 _start;
	cocos2d::Vec2	 _endPoint;
	cocos2d::Vec2	 _startpoints[8];
	cocos2d::Vec2    _currentPoint;
	cocos2d::Vec2    _trajectory;
	cocos2d::Rect*  _asteroidRect;
};

