//
//  b2Sprite.cpp
//  FaceHockey
//
//  Created by Rishav Guha on 1/25/14.
//
//

#include "b2Sprite.h"
#include "GameLayer.h"


b2Sprite::b2Sprite (GameLayer* game, int type){
    _game = game;
    _type = type;
}

void b2Sprite::setSpritePosition(CCPoint position){
    setPosition(position);
    
    //update box2d body, if any
    if(_body){
        _body->SetTransform(b2Vec2(position.x/PTM_RATIO,
                                   position.y/PTM_RATIO),
                            _body->GetAngle());
        
    }
}

void b2Sprite::update(float dt){
    if(_body && isVisible()) {
        setPositionX(_body->GetPosition().x * PTM_RATIO);
        setPositionY(_body->GetPosition().y * PTM_RATIO);
        setRotation(CC_RADIANS_TO_DEGREES(-1 * _body->GetAngle()));
    }
}

void b2Sprite::hide(){
    if(_body){
        _body->SetLinearVelocity(b2Vec2_zero);
        _body->SetAngularVelocity(0);
        _body->SetTransform(b2Vec2_zero, 0.0f);
        _body->SetAwake(false);
    }
}

void b2Sprite::reset(){
 //NoData
}

float b2Sprite::mag(void){
    //get sqared magnitutde of sprite's vetor
    if (_body){
        return pow(_body->GetLinearVelocity().x, 2)+
        pow(_body->GetLinearVelocity().y, 2);
    }
    return 0.0f;
}

b2Body* b2Sprite::getBody(){
    return _body;
}