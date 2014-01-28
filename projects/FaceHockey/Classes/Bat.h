//
//  Bat.h
//  BatHockey
//
//  Created by Rishav Guha on 1/28/14.
//
//

#ifndef __FaceHockey__Bat__
#define __FaceHockey__Bat__

#include "b2Sprite.h"

//b2Sprite.h includes GameLayer.h

USING_NS_CC;

class GameLayer;

class Bat : public b2Sprite {
    
public:
    
    CC_SYNTHESIZE(bool, _inPlay, InPlay);
    
    ~Bat();
    Bat(GameLayer * game, int type, CCPoint position);
    static Bat* create(GameLayer * game, int type, CCPoint position);
    virtual void reset();
    virtual void update (float dt);
private:
    void initBat();
    CCPoint _startPosition;
    
};


#endif /* defined(__FaceHockey__Bat__) */
