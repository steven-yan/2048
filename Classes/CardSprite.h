/**
 *
 *@author steven.yan
 *@date June 17 2014
 *
 **/

#ifndef __Card_Sprite_H__
#define __Card_Sprite_H__

#include "cocos2d.h"

USING_NS_CC;

class CardSprite : public Sprite
{
public:
    static CardSprite* create(float length, int score);
	virtual bool init(float width, int score);
    ~CardSprite();
    
    //cardNum
    int getCardScore();
    void setCardScore(int score);
    
private:
    
    int cardScore;
    Label *cardLabel;
    LayerColor *cardBgColor;
};



#endif
