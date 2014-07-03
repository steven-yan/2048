/**
 *
 *@author steven.yan
 *@date June 17 2014
 *
 **/

#include "GameLayer.h"

USING_NS_CC;

#define S_TO_US (1000000)


// on "init" you need to initialize your instance
GameLayer* GameLayer::createLayer(int width, int row_Num)
{
    GameLayer *layer = new GameLayer();
    if ( layer && layer->init(width, row_Num) )
    {
        layer->autorelease();
        
        return layer;
    }
    
    CC_SAFE_DELETE(layer);

    return NULL;
}

bool GameLayer::init(int width, int row_Num)
{
    if ( !LayerColor::initWithColor(Color4B(180, 170, 160, 255)))
    {
        return false;
    }
    
    //设置长宽
    changeWidthAndHeight(width, width);
    
    //行数
    rowNum = row_Num;
    
    //创建精灵数组
    float spriteGap = 10;
    spriteWidth = (width - (rowNum + 1) * spriteGap) / rowNum;
    
    cardSpriteArray = (CardSprite ***)malloc(sizeof(CardSprite **) * rowNum);
    cardPosArray = (Point ***)malloc(sizeof(Point **) * rowNum);
    
    //初始化背景及位置数组
    for (int i= 0; i < rowNum; i++)
    {
        cardSpriteArray[i] = (CardSprite **)malloc(sizeof(CardSprite *) * rowNum);
        cardPosArray[i] = (Point **)malloc(sizeof(Point *) * rowNum);
        
        for (int j = 0; j < rowNum; j++)
        {
            //精灵数组
            cardSpriteArray[i][j] = NULL;
            
            //精灵位置
            Point point = Point((spriteWidth + spriteGap) * j + spriteGap, (spriteWidth + spriteGap) * i + spriteGap);
            
            //位置数组
            Point *p = (Point *)malloc(sizeof(Point));
            memcpy(p, &point, sizeof(Point));
            cardPosArray[i][j] = p;
            
            //背景位置
            LayerColor *spriteBg = LayerColor::create(Color4B(255, 255, 255, 255), spriteWidth, spriteWidth);
            spriteBg->setPosition(point);
            addChild(spriteBg);
        }
    }
    
    //创建原始卡片
    for (int i = 0; i < 10; i ++) {
        createCardSprite();
//        int s = 4;
//        if (i == 1 || i == 2 ) {
//            s = 2;
//        }
//        CardSprite *card = CardSprite::create(spriteWidth, s);
//        card->setPosition(*cardPosArray[1][i]);
//        addChild(card);
//        cardSpriteArray[1][i] = card;
    }
    
    //触摸事件
    auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

GameLayer:: ~GameLayer()
{
    //释放cardArray
    for (int i = 0; i < rowNum; i++)
    {
        free(cardPosArray[i]);
    }
    free(cardPosArray);
    
    //删除监听
    _eventDispatcher->removeEventListenersForTarget(this);
}

bool GameLayer::onTouchBegan(Touch *touch, Event *event)
{
    //获取触摸起始点位置
    start = touch->getLocation();
    
    //是否在layer内部
    if (!(start.x > this->getPositionX() && start.x < this->getPositionX() + this->getContentSize().width && start.y > this->getPositionY() && start.y < this->getPositionY() + this->getContentSize().height))
    {
        return false;
    }
    
    return true;
}

void GameLayer::onTouchEnded(Touch *touch, Event *event)
{
    //获取触摸终点位置
    end = touch->getLocation();
    //获取滑动距离
    float offsetX = end.x - start.x;
    float offsetY = end.y - start.y;
    
    //滑动距离小于20不处理
    if (abs(offsetX) <= 20 && abs(offsetY) <= 20)
    {
        return;
    }
    
    //判断方向------
    MOVE_T direction;
    if (abs(offsetX) > abs(offsetY))    //X轴滑动
    {
        if (offsetX > 0)                //X轴正向
        {
            direction = MOVE_RIGHT;
        }
        else                            //X轴反向
        {
            direction = MOVE_LEFT;
        }
    }
    else                                //Y轴滑动
    {
        if (offsetY > 0)                //Y轴正向
        {
            direction = MOVE_UP;
        }
        else                            //Y轴反向
        {
            direction = MOVE_DOWN;
        }
    }
    
    //移动精灵
    moveDirect(direction);
    //创建精灵

    //检测结束
}

//移动精灵
void GameLayer::moveDirect(MOVE_T direction)
{
    if (direction == MOVE_RIGHT) {
        for (int i = 0; i < rowNum; i++) {
            for (int j = rowNum - 1; j >= 0; j --) {
                for (int k = j - 1; k >= 0; k --) {
                    if (cardSpriteArray[i][k]) {
                        if (!cardSpriteArray[i][j]) {
                            cardSpriteArray[i][k]->runAction(MoveTo::create(0.1, *cardPosArray[i][j]));
                            cardSpriteArray[i][j] = cardSpriteArray[i][k];
                            cardSpriteArray[i][k] = NULL;
                        } else if (cardSpriteArray[i][k]->getCardScore() == cardSpriteArray[i][j]->getCardScore()) {
                            cardSpriteArray[i][k]->runAction(MoveTo::create(0.1, *cardPosArray[i][j]));
                            removeChild(cardSpriteArray[i][k]);
                            cardSpriteArray[i][k] = NULL;
                            cardSpriteArray[i][j]->setCardScore(cardSpriteArray[i][j]->getCardScore() * 2);
                            j--;
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    }
}

bool GameLayer::createCardSprite()
{
    int i = fakeRandomNum() % rowNum;
    int j = fakeRandomNum() % rowNum;

    if (cardSpriteArray[i][j] == NULL)
    {
        int score = (fakeRandomNum() % 7) < 6 ? 2 : 4;
        CardSprite *card = CardSprite::create(spriteWidth, score);
        card->setPosition(*cardPosArray[i][j]);
        addChild(card);
        cardSpriteArray[i][j] = card;
        
        return true;
    }
    else
    {
        //防止递归溢出
        for (int i = 0; i < rowNum; i ++) {
            for (int j = 0; j < rowNum; j++) {
                if (cardSpriteArray[i][j] == NULL) {
                    return createCardSprite();
                }
            }
        }
    
        return false;
    }
}

// 获取random
int fakeRandomNum() {
    static unsigned int i = 0;
    struct timeval tv;
    gettimeofday(&tv, NULL);

    srand(i * (i + 7) + tv.tv_usec * i);
    i++;
    
    return rand();
}


