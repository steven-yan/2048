/**
 *
 *@author steven.yan
 *@date June 17 2014
 *
 **/

#include "CardSprite.h"

USING_NS_CC;

// on "init" you need to initialize your instance
CardSprite* CardSprite::create(float length, int score)
{
    CardSprite *card = new CardSprite();
    if ( card && card->init(length, score) )
    {
        card->autorelease();
        return card;
    }
    
    CC_SAFE_DELETE(card);
    
    return NULL;
}

bool CardSprite::init(float width, int score)
{
	if (Sprite::init())
	{
        //初始化 cardBgColor
        cardBgColor = LayerColor::create(Color4B(200,190,180,255), width, width);
        addChild(cardBgColor);
        
        //初始化 cacardLabel
        const char *str = __String::createWithFormat("%d", score)->getCString();
        if (score < 0)
        {
            str = "";
        }
        
        cardLabel = Label::createWithSystemFont(str, "Consolas",100);
        cardLabel->setPosition(Point(width / 2.0, width / 2.0));
        addChild(cardLabel);
        
        setCardScore(score);
        
		return true;
	}
    
	return false;
}

CardSprite:: ~CardSprite()
{
}

int CardSprite:: getCardScore()
{
    return cardScore;
}

void CardSprite::doubleCardScore()
{
    setCardScore(cardScore * 2);
}

void CardSprite:: setCardScore(int score)
{
    //设置label 字体大小、内容
    int fontSize = 0;
    const char *str = __String::createWithFormat("%d", score)->getCString();
    
    if (score >= 2) {
        fontSize = 100;
	}
    
    if (score >= 16) {
        fontSize = 90;
	}
    
    if (score >= 128) {
        fontSize = 60;
    }
    
    if (score >= 1024)	{
        fontSize = 40;
    }
    
    cardLabel->setSystemFontSize(fontSize);
    cardLabel->setString(str);
    
    //设置背景颜色
    switch (score) {
        case -1:
            cardBgColor->setColor(Color3B(200,190,180));
            break;
            
        case 2:
            cardBgColor->setColor(Color3B(200,190,180));
            break;
            
        case 4:
            cardBgColor->setColor(Color3B(240,230,220));
            break;
            
        case 6:
            cardBgColor->setColor(Color3B(240,220,200));
            break;
            
        case 8:
            cardBgColor->setColor(Color3B(240,180,120));
            break;
            
        case 16:
            cardBgColor->setColor(Color3B(240,140,90));
            break;
            
        case 32:
            cardBgColor->setColor(Color3B(240,120,90));
            break;
            
        case 64:
            cardBgColor->setColor(Color3B(240,90,60));
            break;
            
        case 128:
            cardBgColor->setColor(Color3B(240,90,60));
            break;
            
        case 256:
            cardBgColor->setColor(Color3B(240,200,70));
            break;
            
        case 512:
            cardBgColor->setColor(Color3B(240,200,70));
            break;
            
        case 1024:
            cardBgColor->setColor(Color3B(0,130,0));
            break;
            
        case 2048:
            cardBgColor->setColor(Color3B(0,130,0));
            break;
            
        case 4096:
            cardBgColor->setColor(Color3B(0,130,0));
            break;
            
        case 8192:
            cardBgColor->setColor(Color3B(0,130,0));
            break;
            
        default:
            break;
    }
    
    cardScore = score;
}


