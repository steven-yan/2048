/**
 *
 *@author steven.yan
 *@date June 17 2014
 *
 **/

#include "MainScene.h"
#include "GameLayer.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
	auto layerColorBG = LayerColor::create(Color4B(100, 0, 0, 255));
	this->addChild(layerColorBG);
    
	auto cardNumberTitle = LabelTTF::create("SCORE","Consolas",60);
	cardNumberTitle->setPosition(Point(visibleSize.width - 250 , visibleSize.height - 160));
	addChild(cardNumberTitle);
    
	auto cardNumberTTF = LabelTTF::create("0", "Consolas", 40);
	cardNumberTTF->setPosition(Point(visibleSize.width - 100, visibleSize.height - 160));
	addChild(cardNumberTTF);
    
    auto layer = GameLayer::createLayer(600, 4);
    layer->setPosition(Point(20, 100));
    addChild(layer);
    
    return true;
}
