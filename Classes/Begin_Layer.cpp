//
//  Begin_Layer.cpp
//  animate_homework
//
//  Created by mac on 15-7-19.
//
//
#include "Second_Scene.h"
#include "About_Scene.h"
#include "State_Layer.h"
#include "Setting_Layer.h"
#include "Begin_Layer.h"
#include "Loadind_layer.h"
#include "First_Scene.h"
#include "First_hurdle.h"
#include "Animation_itools.h"
#include "SimpleAudioEngine.h"
//#include "cocostudio/CocoStudio.h"

//#include "ui/CocosGUI.h"
using namespace CocosDenshion;
USING_NS_CC;
using namespace ui;
//using namespace cocostudio;
//using namespace cocos2d::ui;

Scene* Begin_Layer::createScene()

{
    
    auto scene = Scene::create();
    
    auto layer = Begin_Layer::create();
    
    scene->addChild(layer);

    return scene;
    
}


bool Begin_Layer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(UserDefault::getInstance()->getFloatForKey("music"));
    SimpleAudioEngine::getInstance()->setEffectsVolume(UserDefault::getInstance()->getFloatForKey("effict"));
    
//    auto rootNode = CSLoader::createNode("Scene.csb");
//    addChild(rootNode);
//    auto bottonWidght=dynamic_cast<ui::Button*>(rootNode->getChildByTag(1));
//    bottonWidght->addTouchEventListener(this,toucheventselector(Begin_Layer::touchButton));
    loading_animation();
    SimpleAudioEngine::getInstance()->playBackgroundMusic("p17天朝礼乐.mp3",true);
    Size win_size=Director::getInstance()->getWinSize();
    auto backgrund=Sprite::create("yun.png");
    backgrund->setPosition(win_size.width/2,win_size.height/2);
    this->addChild(backgrund,0,20);
    auto backgrund2=Sprite::create("yun.png");
    backgrund2->setPosition(win_size.width*3/2,win_size.height/2);
    backgrund2->setFlippedX(true);
    this->addChild(backgrund2,0,21);
    
    creat_name_IBM();

    create_bird(Vec2(200,400),Vec2(700,600),5.0);
    create_bird(Vec2(100,200),Vec2(500,500),10.0);
    for (int i=0; i<7; i++) {
        create_bird(6.0+i);
    }
    
    creat_botton(3);
    creat_botton(1);
    creat_botton(5);
    creat_botton(7);
    creat_botton(10);
    auto mu=Menu::createWithArray(vecfoeitem);
    for (int i=0; i<vecfoeitem.size(); i++) {
        MenuItemSprite*p=(MenuItemSprite*)vecfoeitem.at(i);
        p->setPosition(i*100+100,200);
        
    }
    vecfoeitem.at(0)->setCallback(CC_CALLBACK_1(Begin_Layer::callback1,this));
    vecfoeitem.at(1)->setCallback(CC_CALLBACK_1(Begin_Layer::callback2,this));
    vecfoeitem.at(2)->setCallback(CC_CALLBACK_1(Begin_Layer::callback3,this));
    vecfoeitem.at(3)->setCallback(CC_CALLBACK_1(Begin_Layer::callback4,this));
    vecfoeitem.at(4)->setCallback(CC_CALLBACK_1(Begin_Layer::callback5,this));
    mu->setPosition(0, 0);
    mu->setOpacity(0);
    mu->runAction(Sequence::create(DelayTime::create(2.0),FadeIn::create(2.0),NULL));
  
    this->addChild(mu,1);
    
    
    
    
    for (int i=0; i<5; i++) {
        auto sp=Sprite::create();
        sp->setPosition(1000+100*i,200);
        AnimationCache* ac=AnimationCache::getInstance();
        Animation *a=ac->getAnimation("flymood");
        Animate* animate=Animate::create(a);
        sp->runAction(Spawn::create(animate,MoveTo::create(2, Vec2(200+100*i,200)),NULL));
        this->addChild(sp);
    }

    schedule(schedule_selector(Begin_Layer::back_update), 0.05);
    schedule(schedule_selector(Begin_Layer::create_flower), 0.5);
    return true;
    
}

//void Begin_Layer::touchButton(cocos2d::Ref*ref ,cocos2d::ui::TouchEventType type){
//    if (type==cocos2d::ui::TouchEventType::TOUCH_EVENT_ENDED) {
//        Director::getInstance()->replaceScene(TransitionFade::create(1.5,Loading_layer::createScene()));
//    }
//}

void Begin_Layer::loading_animation(){
    AnimationCache* ac=AnimationCache::getInstance();
    Animation*change=itools->makeAnimationfromPlist("change_s.plist", "changescene_%d.png",5,0,0.2,true,-1);
    ac->addAnimation(change,"changescene");
    
    itools->cutPicturewithframe("CG-1559.png", 2, 9, "a_%d");
    
    
    Animation*flymood=itools->makeAnimationfrommixpicture("CG-1565.png",5,2,1,1,5,2,0.02f,true,10);
    ac->addAnimation(flymood,"flymood");
    Animation*flybird=itools->makeAnimationfrommixpicture("CG-1560.png",2,3,1,1,2,3,0.2f,false,-1);
    ac->addAnimation(flybird,"flybird");
    Animation*flyflower=itools->makeAnimationfrommixpicture("CG-1564.png",5,5,1,1,3,5,0.2f,false,-1);
    ac->addAnimation(flyflower,"flyflower");
    
}

void Begin_Layer::creat_botton(int t){
   
        char name[64]={0};
    char name2[64]={0};
        sprintf(name,"a_%d",t);
      sprintf(name2,"a_%d",t+1);
        SpriteFrame* sp=SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
        auto sprite=Sprite::createWithSpriteFrame(sp);
    SpriteFrame* sp2=SpriteFrameCache::getInstance()->getSpriteFrameByName(name2);
    auto sprite2=Sprite::createWithSpriteFrame(sp2);
    
    MenuItemSprite*mp=MenuItemSprite::create(sprite, sprite2);
    
    vecfoeitem.pushBack(mp);

}
void Begin_Layer::create_bird(Vec2 point,Vec2 point2,float t){
    auto bird1=Sprite::create();
    bird1->setPosition(point);
    AnimationCache* ac=AnimationCache::getInstance();
    Animation *a=ac->getAnimation("flybird");
    Animate* animate=Animate::create(a);
    bird1->runAction(animate);
    bird1->runAction(RepeatForever::create(Sequence::create(MoveTo::create(t,point2),FlipX::create(true),
                                                            MoveTo::create(t,point),FlipX::create(false),
                                                            NULL)));
    
    this->addChild(bird1);
}

void Begin_Layer::create_bird(float t){
    auto bird1=Sprite::create();
    bird1->setPosition(Vec2(arc4random()%960,arc4random()%640));
    AnimationCache* ac=AnimationCache::getInstance();
    Animation *a=ac->getAnimation("flybird");
    Animate* animate=Animate::create(a);
    bird1->runAction(animate);
    bird1->runAction(RepeatForever::create(Sequence::create(MoveTo::create(t,Vec2(arc4random()%960,arc4random()%640)),
                                                            FlipX::create(true),
                                                            MoveTo::create(t,Vec2(arc4random()%960,arc4random()%640)),FlipX::create(false),
                                                             MoveTo::create(t,Vec2(arc4random()%960,arc4random()%640)),FlipX::create(true),
                                                             MoveTo::create(t,Vec2(arc4random()%960,arc4random()%640)),FlipX::create(false),
                                                            NULL)));
    
    this->addChild(bird1);

    
}



void Begin_Layer::create_flower(float dt){
    auto flower=Sprite::create();
    flower->setPosition(Vec2(arc4random()%100,300+arc4random()%700));
    AnimationCache* ac=AnimationCache::getInstance();
    Animation *a=ac->getAnimation("flyflower");
    Animate* animate=Animate::create(a);
    flower->runAction(animate);
    flower->runAction(RepeatForever::create(Sequence::create(MoveTo::create(20,Vec2(arc4random()%100+960,arc4random()%640)),RemoveSelf::create(),
                                                        
                                                            NULL)));
    this->addChild(flower);

}

void Begin_Layer::back_update(float dt){
    float s=Director::getInstance()->getWinSize().width;
    Sprite*backgrond1=static_cast<Sprite*>(this->getChildByTag(20));
    Sprite*backgrond2=static_cast<Sprite*>(this->getChildByTag(21));
    backgrond1->setPositionX(backgrond1->getPositionX()-1);
    backgrond2->setPositionX(backgrond2->getPositionX()-1);
    if (backgrond1->getPositionX()<=-s/2) {
        backgrond1->setPositionX(1.5*s);
        backgrond2->setPositionX(s/2);
    }
    if (backgrond2->getPositionX()<=-s/2) {
        backgrond2->setPositionX(1.5*s);
        backgrond1->setPositionX(s/2);
    }
}


void Begin_Layer::creat_name_IBM(){
    auto bt1=Sprite::create("biaoti1.png");
    bt1->setPosition(740,540);
    bt1->setOpacity(0);
    bt1->setScale(0.8);
    bt1->runAction(Sequence::create(DelayTime::create(2.0),FadeIn::create(1.0),TintBy::create(5.0, -200, -200, -200),TintBy::create(2.0,200, 200, 200), NULL));
    this->addChild(bt1);
    
    auto bt2=Sprite::create("biaoti2.png");
    bt2->setPosition(740,400);
    bt2->setOpacity(0);
    bt2->setScale(0.6);
    bt2->runAction(Sequence::create(DelayTime::create(3.0),FadeIn::create(1.0),TintBy::create(4.0, -200, -200, -200),TintBy::create(2.0,200, 200, 200), NULL));

    this->addChild(bt2);

//    auto bt3=Sprite::create("biaoti3.png");
//    bt3->setPosition(740,200);
//    bt3->setOpacity(0);
//    bt3->runAction(Sequence::create(DelayTime::create(4.0),FadeIn::create(1.0),TintBy::create(3.0, -200, -200, -200),TintBy::create(2.0,200, 200, 200), NULL));
//
//    this->addChild(bt3);


}

void Begin_Layer::callback1(Ref* psender){
    SimpleAudioEngine::getInstance()->playEffect("dianji.wav");
    Director::getInstance()->replaceScene(TransitionFade::create(1.5,Loading_layer::createScene()));

}
void Begin_Layer::callback2(Ref* psender){
    SimpleAudioEngine::getInstance()->playEffect("dianji.wav");
      Director::getInstance()->replaceScene(First_hurdle::createScene());
}
void Begin_Layer::callback3(Ref* psender){
    SimpleAudioEngine::getInstance()->playEffect("dianji.wav");
      Director::getInstance()->pushScene(About_Layer::createScene());
   
}
void Begin_Layer::callback4(Ref* psender){
    Director::getInstance()->pushScene(Setting_Layer::createScene());
    SimpleAudioEngine::getInstance()->playEffect("dianji.wav");
}
void Begin_Layer::callback5(Ref* psender){
    SimpleAudioEngine::getInstance()->playEffect("dianji.wav");
       // Director::getInstance()->pushScene(About_Layer::createScene());
     Director::getInstance()->replaceScene(Second_Scene::createScene());
}
