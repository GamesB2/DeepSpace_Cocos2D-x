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


	auto winsize = cocos2d::Director::getInstance()->getVisibleSize();
	this->setPosition(0.0, 0.0);
	this->setAnchorPoint(cocos2d::Vec2(winsize.width / 2, winsize.height / 2));

	_timerLabel = cocos2d::Label::create("Time: ", "Arial", 30.0f);
	addChild(_timerLabel);
	_timerLabel->setVisible(false);
	_timerLabel->setPosition((winsize.width / 10) * 9, (winsize.height / 10) * 9);
	_timerLabel->setString("Time: 00:00");

	this->schedule(schedule_selector(AstTimer::update), 1.0f);

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
			sprintf(buffer, "Time: %02d:%02d", minutes, seconds);
			_timeElapsed = buffer;
			_timerLabel->setString(_timeElapsed);
		}
	}
}

void AstTimer::reset()
{
	seconds = 0;
	minutes = 0;
}


