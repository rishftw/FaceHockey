//
//  b2Sprite.h
//  FaceHockey
//
//  Created by Rishav Guha on 1/25/14.
//
//

#ifndef __FaceHockey__b2Sprite__
#define __FaceHockey__b2Sprite__

#define BAll_RADIUS 8.0f
#define PTM_RATIO 32

#include "cocos2d.h"
#include "Box2D.h"

USING_NS_CC;

class GameLayer;

class b2Sprite : public CCSprite{
protected:
    b2Body *_body;
    
public:
    
    b2Sprite(GameLayer* game, int type);
    
    b2Body* getBody();
    CC_SYNTHESIZE(GameLayer*, _game, Game);
    CC_SYNTHESIZE(int, _type, Type);
    
    virtual void setSpritePosition(CCPoint position);
    virtual void update(float dt);
    virtual void hide(void);
    virtual void reset (void);
    virtual float mag (void);
    

};

#endif /* defined(__FaceHockey__b2Sprite__) */
