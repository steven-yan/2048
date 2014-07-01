/**
 *
 *@author steven.yan
 *@date June 17 2014
 *
 **/

#ifndef __Main_SCENE_H__
#define __Main_SCENE_H__

#include "cocos2d.h"

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
    
    //触摸事件
//    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
//	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
private:
};

#endif
