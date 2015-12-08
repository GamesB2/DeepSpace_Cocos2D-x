#pragma once

#ifndef __BaseLandscapeProject__game_Player__
#define __BaseLandscapeProject__game_Player__
#include "cocos2d.h"
#include <stdio.h>
#include "HelloWorldScene.h"
#include "GameManager.h"

class game_player : public cocos2d::Node
{
	
public:
	game_player();
	~game_player();
	virtual bool init() override;
	game_player* create();

	 
	virtual void update(float);
	bool asteroidCollision(cocos2d::Rect collisionBoxToCheck);
	void reset();
	void SetTrajectory(cocos2d::Vec2 touchPoint);
	
private:

	cocos2d::Sprite* game_Ship;
	bool _endpointReached;
	float _rotation;
	cocos2d::Vec2 _currentPosition;
	cocos2d::Vec2 _trajectory;
	float _currentSpeed;
	cocos2d::Vec2 _endPoint;
	float _maxSpeed;
	bool _dead;
	cocos2d::Size _winSize;
	//maybe if time
	//bool _rotationComplete;
	
};
#endif 


