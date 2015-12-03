#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

// Includes required for Pseudo Random Numbers
#include <cstdlib>
#include <ctime>


USING_NS_CC;

Asteroid* _asteroid1;
Asteroid* _asteroid2;
Asteroid* _asteroid3;
Asteroid* asteroids[3];

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
	//this->scheduleUpdate();

	_asteroid1 = new Asteroid();
	addChild(_asteroid1);
	_asteroid2 = new Asteroid();
	addChild(_asteroid2);
	_asteroid3 = new Asteroid();
	addChild(_asteroid3);

	asteroids[0] = _asteroid1;
	asteroids[1] = _asteroid2;
	asteroids[2] = _asteroid3;

	// Add the label to give us some feedback on where we have touched
	labelTouchInfo = Label::createWithSystemFont("Kek", "Arial", 30);

	// Set the label to be in the middle of the screen
	labelTouchInfo->setPosition(cocos2d::Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2));

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

	// Finally, lets add the label to the layer (HelloWorld is a layer, NOT a scene)
	this->addChild(labelTouchInfo);

	this->scheduleUpdate();
	
    return true;
}

void HelloWorld::update(float delta)
{
	for (int i = 0; i < sizeof(asteroids); i++) {
		for (int j = 0; j < sizeof(asteroids); j++) {
			if (j != i) {
				asteroids[i]->HasCollidedWithAsteroid(asteroids[j]->GetBoundingBox());
			}
		}
	}


}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	// Create three random numbers that will be the colour of our text
	GLubyte red = rand() % 255;
	GLubyte green = rand() % 255;
	GLubyte blue = rand() % 255;
	// Create the colour based on our random numbers
	cocos2d::Color3B myColour = cocos2d::Color3B(red, green, blue);
	labelTouchInfo->setPosition(touch->getLocation());
	labelTouchInfo->setString("You pressed HERE!");
	labelTouchInfo->setColor(myColour);
	return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	
}

void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{

}

void HelloWorld::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event)
{

}