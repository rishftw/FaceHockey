//
//  Bat.cpp
//  FaceHockey
//
//  Created by Rishav Guha on 1/28/14.
//
//

#include "Bat.h"
#include "GameLayer.h"

#define BOX_WIDTH 27/2.0f
#define BOX_HEIGHT 192/2.0f

class GameLayer;

Bat::~Bat(){
}

Bat::Bat(GameLayer *game, int type, CCPoint position):b2Sprite(game, type){
    _type = type;
    _game = game;
    _startPosition = position;
    _inPlay = true;
}

Bat* Bat::create(GameLayer * game, int type, CCPoint position) {
    Bat * sprite = new Bat(game, type, position);
	if (sprite) {
        sprite->initBat();
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return NULL;
}

void Bat::initBat() {
    
    //create box2d body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    
    _body = _game->getWorld()->CreateBody(&bodyDef);
    _body->SetSleepingAllowed(true);
    _body->SetLinearDamping(0.6);
    _body->SetAngularDamping(0.4);
    
    //set sprite texture
    this->initWithSpriteFrameName("bat_resized_straight.png");
    
    _body->SetUserData(this);
    
    /*
     //create shape
     string temp = "dhruv_Bat";
     GB2ShapeCache *sc = GB2ShapeCache::sharedGB2ShapeCache();
     sc->addFixturesToBody(_body, temp.c_str());
     this->setAnchorPoint(sc->anchorPointForShape(temp.c_str()));
     */
    
    
    //create rectangle shape
    b2PolygonShape box;
    box.SetAsBox(BOX_WIDTH/PTM_RATIO, BOX_HEIGHT/PTM_RATIO);
    
    //define fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.density = 5;
    fixtureDef.restitution = 0.7;
    
    _body->CreateFixture(&fixtureDef);
    
    _body->SetUserData(this);
    
    setSpritePosition(_startPosition);
}

void Bat::reset() {
    if (_body) {
        _body->SetLinearVelocity(b2Vec2_zero);
        _body->SetAngularVelocity(0);
        _body->SetAwake(true);
    }
    setSpritePosition(_startPosition);
    _inPlay = true;
    setVisible(true);
}

void Bat::update (float dt) {
    
    if (_body && isVisible()) {
        setPositionX(_body->GetPosition().x * PTM_RATIO);
        setPositionY(_body->GetPosition().y * PTM_RATIO);
    }
}