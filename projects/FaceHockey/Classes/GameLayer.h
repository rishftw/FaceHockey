#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"
#include "GLES-Render.h"

class PhysicsSprite : public cocos2d::CCSprite
{
public:
    PhysicsSprite();
    void setPhysicsBody(b2Body * body);
    virtual bool isDirty(void);
    virtual cocos2d::CCAffineTransform nodeToParentTransform(void);
private:
    b2Body* m_pBody;    // strong ref
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
    b2World* world;
    
    GLESDebugDraw *m_debugDraw;
};

#endif // __GAMELAYER_H__
