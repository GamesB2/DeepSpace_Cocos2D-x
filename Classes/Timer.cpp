#include "Timer.h"

Timer::Timer()
{
	this->init();
}

Timer::~Timer()
{
}

Timer* Timer::create()
{
	Timer* _timer = new Timer();
	if (_timer->init())
	{
		_timer->autorelease();
		return _timer;
	}
	else
	{
		CC_SAFE_DELETE(_timer);
		return nullptr;
	}
}

bool Timer::init()
{
	if (!Node::init())
	{
		return false;
	}

	_rootNode = cocos2d::CSLoader::createNode("Timer.csb");
	addChild(_rootNode);

	_timerLabel = _rootNode->getChildByName<cocos2d::Label*>("Timer");
	addChild(_timerLabel);
	_timerLabel->setVisible(false);

	this->schedule(schedule_selector(Timer::update), 1.0f);

	seconds = 0;
	minutes = 0;

	return true;
}

void Timer::update(float deltaTime)
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
			_timerLabel->setString(cocos2d::StringUtils::format("%d", ));
		}
	}
}


