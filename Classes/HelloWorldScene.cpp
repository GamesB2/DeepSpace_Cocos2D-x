#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

// Includes required for Pseudo Random Numbers
#include <cstdlib>
#include <ctime>


USING_NS_CC;

Asteroid* asteroids[5];
game_player* _player;
AstTimer* _timer;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	// First, lets create our seed for the random number generator
	srand(time(NULL));
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);

	//Schedule Update for when needed


	// Init Asteroids
	for (int i = 0; i < 5; i++)
	{
		asteroids[i] = new Asteroid(i);
		addChild(asteroids[i]);
	}

	//	game_player obj;
	// init here
	_player = new game_player();
	addChild(_player);

	visibleTarget = (Sprite*)rootNode->getChildByName("visibleTarget");
	visibleTarget->setOpacity(0);

	Title = (Sprite*)rootNode->getChildByName("Title");

	//Preload Music
	audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("DiscoCentury.wav");
	audio->preloadEffect("sandyrb-thecrash.wav");

	// Create a custom event listener
	auto touchListener = EventListenerTouchOneByOne::create();

	// Assign the event methods to the event listener (known as callbacks)
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);

	/* For more information on the eventdispatcher mechanism (and how events in Cocos work in general) go to http://www.cocos2d-x.org/wiki/EventDispatcher_Mechanism */
	// Add the event listener to the event dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	startButton = static_cast<ui::Button*>(rootNode->getChildByName("temp_Go"));
	startButton->setTitleText("Start!");

	exitButton = static_cast<ui::Button*>(rootNode->getChildByName("Exit"));
	exitButton->setTitleText("Exit");

	creditsButton = static_cast<ui::Button*>(rootNode->getChildByName("Credits"));
	creditsButton->setTitleText("Credits");

	SetUpbuttons();

	_timer = new AstTimer();
	addChild(_timer);
	
	GameManager::sharedGameManager()->_died = false;
	GameManager::sharedGameManager()->isGameLive = false;

	this->scheduleUpdate();
	
    return true;
}

void HelloWorld::update(float delta)
{
	if (GameManager::sharedGameManager()->isGameLive)
	{
		if (GameManager::sharedGameManager()->_died != true)
		{
			_player->update(delta);
			if (visibleTarget->getOpacity() > 0)
			{
				visibleTarget->setOpacity(visibleTarget->getOpacity() - 3);
				visibleTarget->setRotation(visibleTarget->getRotation() + 3);
			}

			for (int i = 0; i < 5; i++)
			{
				asteroids[i]->update(delta);
				if (_player->asteroidCollision(*asteroids[i]->GetBoundingBox()))
				{
					GameManager::sharedGameManager()->_died = true;
					audio->playEffect("sandyrb-thecrash.wav");
					SetUpbuttons();
				}
				for (int j = 0; j < 5; j++)
				{
					if (j != i)
					{
						if (asteroids[i]->HasCollidedWithAsteroid(asteroids[j]->GetBoundingBox()))
						{
							asteroids[i]->AsteroidBounce(asteroids[j]->GetVec(), asteroids[j]->GetPos());
							asteroids[j]->AsteroidBounce(asteroids[i]->GetVec(), asteroids[i]->GetPos());
						}
					}
				}
			}
		}
	}
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if (GameManager::sharedGameManager()->isGameLive == true)
	{
		if (GameManager::sharedGameManager()->_died != true)
		{
			_player->SetTrajectory(touch->getLocation());

			visibleTarget->setPosition(touch->getLocation());
			visibleTarget->setOpacity(255);
		}
	}
	return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if (GameManager::sharedGameManager()->isGameLive == true)
	{
		if (GameManager::sharedGameManager()->_died != true)
		{
			_player->SetTrajectory(touch->getLocation());

			visibleTarget->setPosition(touch->getLocation());
			visibleTarget->setOpacity(255);
		}
	}
}

void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if (GameManager::sharedGameManager()->isGameLive == true)
	{
		if (GameManager::sharedGameManager()->_died != true)
		{
			_player->SetTrajectory(touch->getLocation());

			visibleTarget->setPosition(touch->getLocation());
			visibleTarget->setOpacity(255);
		}
	}
}

void HelloWorld::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event)
{

}
void HelloWorld::StartGame()
{
	audio->rewindBackgroundMusic();
	audio->playBackgroundMusic("DiscoCentury.wav", true);
	for (int i = 0; i < 5; i++)
	{
		asteroids[i]->Reset();
	}
	_player->reset();
	Title->setVisible(false);
	startButton->setVisible(false);
	exitButton->setVisible(false);
	creditsButton->setVisible(false);
	_player->setVisible(true);
	_timer->reset();
	for (int i = 0; i < 5; i++)
	{
		asteroids[i]->setVisible(true);
	}
	GameManager::sharedGameManager()->isGameLive = true;
	GameManager::sharedGameManager()->_died = false;
}
void HelloWorld::SetUpbuttons()
{
	audio->pauseBackgroundMusic();

	visibleTarget->setOpacity(0);
	
	Title->setVisible(true);

	_player->setVisible(false);

	for (int i = 0; i < 5; i++)
	{
		asteroids[i]->setVisible(false);
	}

	startButton->setVisible(true);
	startButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			StartGame();
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

	exitButton->setVisible(true);
	exitButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			Director::getInstance()->end();
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

	creditsButton->setVisible(true);
	creditsButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			Director::getInstance()->pushScene(Credits::createScene());
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
}