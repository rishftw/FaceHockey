#include "GameLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

//#define PTM_RATIO 32

GameLayer::GameLayer()
{
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *bg = CCSprite::create("bg.jpg");
    bg->setPosition(ccp(_screenSize.width*0.5f,
                        _screenSize.height*0.5f));
    this->addChild(bg);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("sprite_sheet.plist");
    _gameBatchNode = CCSpriteBatchNode::create("sprite_sheet.png");
    
    this->addChild(_gameBatchNode, kMiddleground);
    
    // init physics
    this->initPhysics();
    
    setTouchEnabled(true);
    
    scheduleUpdate();
}

GameLayer::~GameLayer()
{
    delete world;
    world = NULL;
    
    delete m_debugDraw;
    //delete _collisionListener;
}

void GameLayer::initPhysics()
{
    //GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile("shapes.plist");
    
    b2Vec2 gravity;
    gravity.Set(0.0f, 0.0f);
    world = new b2World(gravity);
    
    // Do we want to let bodies sleep?
    world->SetAllowSleeping(true);
    
    world->SetContinuousPhysics(true);
    
    //_collisionListener = new CollisionListener;
    //world->SetContactListener(_collisionListener);
    
    
    m_debugDraw = new GLESDebugDraw( PTM_RATIO );
    world->SetDebugDraw(m_debugDraw);
    
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    //        flags += b2Draw::e_jointBit;
    //        flags += b2Draw::e_aabbBit;
    //        flags += b2Draw::e_pairBit;
    //        flags += b2Draw::e_centerOfMassBit;
    m_debugDraw->SetFlags(flags);
    
    
    //start creation of the bounding box of the arena to prevent the puck from flying outside. The design allows for the puck to go inside around 200 pixels inside the goal.
    b2BodyDef boundingBoxDef;
    boundingBoxDef.type = b2_staticBody;
    b2Body *boundingBody = world->CreateBody(&boundingBoxDef);
    
    //create fixture and call createBoundingBoxShape to create and assign the chainShap
    
    b2FixtureDef boundingBoxFixDef;
    
    boundingBoxFixDef.shape = createBoundingBoxShape();
    
    boundingBoxFixDef.friction = 0.1;
    boundingBoxFixDef.density = 5;
    boundingBoxFixDef.restitution = 0.8;
    
    boundingBody->CreateFixture(&boundingBoxFixDef);
    
    face = Face::create(this, 1, ccp(0.5f*_screenSize.width, 0.5f*_screenSize.height));
    
    _gameBatchNode->addChild(face);
    
    face->setVisible(true);
    
    bat = Bat::create(this, 2, ccp(0.2f*_screenSize.width,
                                   0.5f*_screenSize.height));
    _gameBatchNode->addChild(bat);
    
    bat->setVisible(true);
}

void GameLayer::draw()
{
    //
    // IMPORTANT:
    // This is only for debug purposes
    // It is recommend to disable it
    //
    
    CCLayer::draw();
    
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    
    kmGLPushMatrix();
    
    world->DrawDebugData();
    
    kmGLPopMatrix();
    
}

void GameLayer::update(float dt)
{
    //It is recommended that a fixed time step is used with Box2D for stability
    //of the simulation, however, we are using a variable time step here.
    //You need to make an informed choice, the following URL is useful
    //http://gafferongames.com/game-physics/fix-your-timestep/
    
    int velocityIterations = 8;
    int positionIterations = 1;
    
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    world->Step(dt, velocityIterations, positionIterations);
    
    face->update(dt);
    
    bat->update(dt);
    
    static bool y = true;
    if(y==true){
        b2Vec2 force = b2Vec2(0.0f,10.0f);
        b2Vec2 point = face->getBody()->GetWorldCenter();
        face->getBody()->ApplyLinearImpulse(force
                                            , point);
        y=false;
    }else{
        y=true;	
    }
}

CCScene* GameLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new GameLayer();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}

b2ChainShape* GameLayer::createBoundingBoxShape(){
    b2Vec2 vs[12];
    
    vs[0].Set(convertPixelToRatio(0.0f, 0), convertPixelToRatio(0.0f, 1));
    vs[1].Set(convertPixelToRatio(0.0f, 0), convertPixelToRatio(217.0f, 1));
    vs[2].Set(convertPixelToRatio(-200.0f, 0), convertPixelToRatio(217.0f, 1));
    vs[3].Set(convertPixelToRatio(-200.0f, 0), convertPixelToRatio(551.0f, 1));
    vs[4].Set(convertPixelToRatio(0.0f, 0), convertPixelToRatio(551.0f, 1));
    vs[5].Set(convertPixelToRatio(0.0f, 0), convertPixelToRatio(768.0f, 1));
    vs[6].Set(convertPixelToRatio(1024.0f, 0), convertPixelToRatio(768.0f, 1));
    vs[7].Set(convertPixelToRatio(1024.0f, 0), convertPixelToRatio(551.0f, 1));
    vs[8].Set(convertPixelToRatio(1224.0f, 0), convertPixelToRatio(551.0f, 1));
    vs[9].Set(convertPixelToRatio(1224.0f, 0), convertPixelToRatio(217.0f, 1));
    vs[10].Set(convertPixelToRatio(1024.0f, 0), convertPixelToRatio(217.0f, 1));
    vs[11].Set(convertPixelToRatio(1024.0f, 0), convertPixelToRatio(0.0f, 1));
    
    b2ChainShape* chain = new b2ChainShape;
    
    chain->CreateLoop(vs, 12);
    
    return chain;
}

//heightOrWidth = 0 for width, =1 for height
float GameLayer::convertPixelToRatio(float pixelVal, int heightOrWidth){
    float tempVal = 0.0f;
    
    if(heightOrWidth != 0){
        tempVal = pixelVal/768;
        
        return (tempVal * _screenSize.height)/PTM_RATIO;
    }else{
        tempVal = pixelVal/1024;
        
        return (tempVal*_screenSize.width)/PTM_RATIO;
    }
    
}

b2World* GameLayer::getWorld(){
    return world;
}