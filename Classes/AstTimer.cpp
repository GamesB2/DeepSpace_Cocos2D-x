#include "AstTimer.h"

char buffer[5];

AstTimer::AstTimer()
{
	this->init();
}

AstTimer::~AstTimer()
{
}

AstTimer* AstTimer::create()
{
	AstTimer* _AstTimer = new AstTimer();
	if (_AstTimer->init())
	{
		_AstTimer->autorelease();
		return _AstTimer;
	}
	else
	{
		CC_SAFE_DELETE(_AstTimer);
		return nullptr;
	}
}

bool AstTimer::init()
{
	if (!Node::init())
	{
		return false;
	}

	_rootNode = cocos2d::CSLoader::createNode("AstTimer.csb");
	addChild(_rootNode);

	_timerLabel = _rootNode->getChildByName<cocos2d::Label*>("AstTimer");
	addChild(_timerLabel);
	_timerLabel->setVisible(false);

	this->schedule(schedule_selector(AstTimer::update), 1.0f);

	_timerLabel->setString("00:00");

	seconds = 0;
	minutes = 0;

	return true;
}

void AstTimer::update(float deltaTime)
{
	if (GameManager::sharedGameManager()->isGameLive)
	{
		if (GameManager::sharedGameManager()->_died != true)
		{
			_timerLabel->setVisible(true);
			seconds = seconds + 1;
			if (seconds > 59)
			{
				seconds = 0;
				minutes = minutes + 1;
			}
			sprintf(buffer, "%d:%d", minutes, seconds);
			_timeElapsed = buffer;
			_timerLabel->setString(_timeElapsed);
		}
	}
}


