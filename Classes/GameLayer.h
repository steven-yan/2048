/**
 *
 *@author steven.yan
 *@date June 17 2014
 *
 **/

#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "CardSprite.h"

USING_NS_CC;


typedef enum
{
    MOVE_NONE,
    MOVE_UP,
    MOVE_RIGHT,
    MOVE_DOWN,
    MOVE_LEFT
} MOVE_T;

class GameLayer : public LayerColor
{
public:
    static GameLayer* createLayer(int width, int row_Num);
    bool init(int length, int row_Num);
    int rowNum;
    
    //可动态调整数组大小 默认为4
    CardSprite ***cardSpriteArray;
    Point ***cardPosArray;
    
private:
    //propety
    Point start, end;
    int spriteWidth;
    int totalPoints;
    
    //destruction
    ~GameLayer();
    
    //移动元素
    void moveDirect(MOVE_T direction);
    
    // touch method
    bool onTouchBegan(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
    
    //创建精灵
    bool createCardSprite();
};

int fakeRandomNum();



#endif
