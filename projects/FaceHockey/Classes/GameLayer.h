#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"
#include "GLES-Render.h"
#include "cocoa/CCNS.h"
#include "b2Sprite.h"
#include "GB2ShapeCache-x.h"
#include "CollisionListener.h"

USING_NS_CC;

enum {
    kBackground,
    kMiddleground,
    kForeground
};

class GameLayer : public cocos2d::CCLayer {
public:
    ~GameLayer();
    GameLayer();
    
    // returns a Scene that contains the GameLayer as the only child
    static cocos2d::CCScene* scene();
    
    void initPhysics();
    virtual void draw();
    void update(float dt);
    
    
private:
    CCSpriteBatchNode * _gameBatchNode;
    b2ContactListener *_collisionListener;
    
    CC_SYNTHESIZE(b2World*, world, World);
    
    CCSize _screenSize;
    
    GLESDebugDraw *m_debugDraw;
    
    b2ChainShape* createBoundingBoxShape();
    
    float convertPixelToRatio(float pixelVal, int heightOrWidth);
};

#endif // __GAMELAYER_H__