//
//  Face.h
//  FaceHockey
//
//  Created by Rishav Guha on 1/28/14.
//
//

#ifndef __FaceHockey__Face__
#define __FaceHockey__Face__

#include "b2Sprite.h"

//b2Sprite.h includes GameLayer.h

USING_NS_CC;

class b2Sprite;
class GameLayer;

class Face : public b2Sprite {
    
public:
    
    CC_SYNTHESIZE(bool, _inPlay, InPlay);
    
    ~Face();
    Face(GameLayer * game, int type, CCPoint position);
    static Face* create(GameLayer * game, int type, CCPoint position);
    virtual void reset();
    virtual void update (float dt);
private:
    void initFace();
    CCPoint _startPosition;
    
};


#endif /* defined(__FaceHockey__Face__) */
