//
//  Face.cpp
//  FaceHockey
//
//  Created by Rishav Guha on 1/28/14.
//
//

#include "Face.h"
#include "GameLayer.h"

#define BALL_RADIUS 96

Face::~Face(){
}

Face::Face(GameLayer *game, int type, CCPoint position):b2Sprite(game, type){
    _type = type;
    _game = game;
    _startPosition = position;
    _inPlay = true;
}

Face* Face::create(GameLayer * game, int type, CCPoint position) {
    Face * sprite = new Face(game, type, position);
	if (sprite) {
        sprite->initFace();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

void Face::initFace() {
    
    //create box2d body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    
    _body = _game->world->CreateBody(&bodyDef);
    _body->SetSleepingAllowed(true);
    _body->SetLinearDamping(0.6);
    _body->SetAngularDamping(0.4);
    
    //set sprite texture
    this->initWithSpriteFrameName("dhruv_face.png");
    
    _body->SetUserData(this);
    
    
     //create shape
    string temp = "dhruv_face";
    GB2ShapeCache *sc = GB2ShapeCache::sharedGB2ShapeCache();
    sc->addFixturesToBody(_body, temp.c_str());
    this->setAnchorPoint(sc->anchorPointForShape(temp.c_str()));
    
    
    /*
    //create circle shape
    b2CircleShape  circle;
    circle.m_radius = BALL_RADIUS/PTM_RATIO;
    
    //define fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 5;
    fixtureDef.restitution = 0.7;
    
    _body->CreateFixture(&fixtureDef);
    */
    _body->SetUserData(this);

    setSpritePosition(_startPosition);
}

void Face::reset() {
    if (_body) {
        _body->SetLinearVelocity(b2Vec2_zero);
        _body->SetAngularVelocity(0);
        _body->SetAwake(true);
    }
    setSpritePosition(_startPosition);
    _inPlay = true;
    setVisible(true);
}

void Face::update (float dt) {
    
    if (_body && isVisible()) {
        setPositionX(_body->GetPosition().x * PTM_RATIO);
        setPositionY(_body->GetPosition().y * PTM_RATIO);
    }
}