//
//  First_hurdle.cpp
//  animate_homework
//
//  Created by mac on 15-7-23.
//
//
#include "State_Layer.h"
#include "First_hurdle.h"
#include "UI_Layer.h"
#include "HelloWorldScene.h"
#include "Begin_Layer.h"
#include "SimpleAudioEngine.h"
#include "Player.h"
using namespace CocosDenshion;
USING_NS_CC;
cocos2d::Scene* First_hurdle::createScene(){
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = First_hurdle::create();
   
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
void First_hurdle::onEnterTransitionDidFinish(){
    Layer::onEnterTransitionDidFinish();
   
}
bool First_hurdle::init(){
    if (!Layer::init()) {
        return false;
    }
   
     SimpleAudioEngine::getInstance()->playBackgroundMusic("p66剑歌行·变调.mp3",true);
    
    auto game=HelloWorld::create();
    this->addChild(game,0,1);
    
    auto ui=UI_Layer::create();
    addChild(ui,1,2);
    
    scheduleUpdate();
    return true;
}
void First_hurdle::update(float dt){
    HelloWorld*game=static_cast<HelloWorld*>(this->getChildByTag(1));
    if (game->gameover==true) {
        gameover();
    }
}

void First_hurdle::gameover(){
    Player*p=Player::getInstance();
    p->vecofhero.clear();
    
    SimpleAudioEngine::getInstance()->playBackgroundMusic("p105战斗失败.mp3");
    Size size=Director::getInstance()->getWinSize();
    //LayerColor *layer=LayerColor::create(ccc4(0,0,0,190),size.width,size.height);
    Sprite *sp=Sprite::create("CombatOver.png");
    Point t=this->convertToNodeSpace(Vec2(size.width*0.5,size.height*0.5));
    sp->setPosition(t);
    sp->setScale(size.width/sp->getContentSize().width, size.height/sp->getContentSize().height);
   // layer->
    addChild(sp,100);
    
    //addChild(layer,100);
    
    Label*ttback=Label::create("返回", "Helvetica_Blod", 23);
    MenuItemLabel *menuLabel=MenuItemLabel::create(ttback, this, menu_selector(First_hurdle::back_game));
    menuLabel->setPosition(0,-200);
    
    Menu*menu=Menu::create(menuLabel,NULL);
    menu->setPosition(t);
    addChild(menu,100);
    
    Director::getInstance()->pause();
}

void First_hurdle::back_game(CCObject *sender){
    this->unscheduleAllSelectors();
    Director::getInstance()->resume();
    Director::getInstance()->replaceScene(TransitionFadeBL::create(1.5,Begin_Layer::createScene()));
    
    
    
}
