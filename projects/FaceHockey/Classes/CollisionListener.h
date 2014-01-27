//
//  CollisionListener.h
//  FaceHockey
//
//  Created by Rishav Guha on 1/28/14.
//
//

#ifndef __FaceHockey__CollisionListener__
#define __FaceHockey__CollisionListener__

#include "Box2d.h"
#include "GameLayer.h"

class CollisionListener : public b2ContactListener
{
    public :
    virtual void BeginContact(b2Contact* contact);
    //virtual void EndContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    //virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    
};

#endif /* defined(__FaceHockey__CollisionListener__) */
