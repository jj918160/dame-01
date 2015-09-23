//
//  Second_Scene.cpp
//  animate_homework
//
//  Created by mac on 15-8-5.
//
//
#include "First_hurdle.h"
#include "Second_Scene.h"
#include "Nofight_Scene_Base.h"
#include "UIr_Layer.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "zhaoyun_r.h"
#include "Talking_Rush.h"
#include "Animation_itools.h"
#include "Player.h"
#include "xiangyu.h"
#include "xiongkuohai.h"
#include "liyuanba.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio::timeline;
using namespace CocosDenshion;

Scene* Second_Scene::createScene(){
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Second_Scene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
bool Second_Scene::init(){
    if (!Layer::init()) {
        return false;
    }
    addok=false;
    talking=false;
    isadding=false;
    changing=false;
    changescene=false;
    cantouch=true;
    
    base=Nofight_Scene_Base::create("map2.tmx");
    this->addChild(base,0,1);
    
    base->zy->big_map=true;
    
    UIr_Layer*uir=UIr_Layer::create();
    this->addChild(uir,1,2);
    
    UIr_Layer::type=0;
    uir->set_workstring("和这个陌生人对话。");
    
    SimpleAudioEngine::getInstance()->playBackgroundMusic("p68杏叶书香.mp3",true);
    
    auto NootGuanyu=CSLoader::createNode("Npc1.csb");
    auto Noodguanyuaction=CSLoader::createTimeline("Npc1.csb");
    base->addChild(NootGuanyu,1,3);
    NootGuanyu->runAction(Noodguanyuaction);
    Noodguanyuaction->gotoFrameAndPlay(0,80,true);
    
    
    
    Sprite*spgy=(Sprite*)NootGuanyu->getChildByTag(23);
    
    spgy->setPosition(100,100);
    
    
   
    
    
    //base->addChild(spgy,1,3);
    
    auto listener=EventListenerTouchOneByOne::create();
    listener->onTouchBegan=[=](Touch*touch,Event*event){
        Vec2 point=base->convertToNodeSpace(touch->getLocation());
     
        if (event->getCurrentTarget()->boundingBox().containsPoint(point)&&cantouch){
            event->getCurrentTarget()->runAction(Sequence::create(ScaleTo::create(0.1, 1.2),ScaleTo::create(0.1, 1.0) ,NULL));
            cantouch=false;
            talking=true;
            talk1();
            return true;
        }
        return false;
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,spgy);
    
    scheduleUpdate();
    return true;
}

void Second_Scene::talk1(){
        std::vector<std::string> v_t;
        v_t=itools->load_mssage("/Users/mac/Desktop/homeworkpic/talk/talk4.txt", v_t);
        auto talk_layer=Talking_Rush::create(v_t);
        this->addChild(talk_layer,1,5);
        schedule(schedule_selector(Second_Scene::addhero1),1/60);
        changescene=true;
    
    auto sp=Sprite::create();
    sp->setPosition(-650,-100);
    AnimationCache* ac=AnimationCache::getInstance();
    Animation *a=ac->getAnimation("changescene");
    Animate* animate=Animate::create(a);
    sp->runAction(animate);
    base->addChild(sp,2,10);
    
    UIr_Layer*ui=(UIr_Layer*)this->getChildByTag(2);
    ui->set_workstring("任务:去长板坡和李元霸杀敌");
}

void Second_Scene::addhero1(float dt){

    auto tk=(Talking_Rush*)this->getChildByTag(5);
    if (!tk) {
        addok=true;
  
        unschedule(schedule_selector(Second_Scene::addhero1));
    }
}

void Second_Scene::update(float dt){
    if (addok&&!isadding) {
     
        Player*p=Player::getInstance();
        xiangyu*xy=xiangyu::create();
        p->addhero(xy);
       
        
        
            xiongkuohai*xkh=xiongkuohai::create();
        p->addhero(xkh);
        
            liyuanba*lyb=liyuanba::create();
        p->addhero(lyb);
        isadding=true;
      
     
        auto i=base->getChildByTag(3);
       
        
                i->runAction(Sequence::create(FadeOut::create(1.0f),
                                              RemoveSelf::create(),
                                              NULL));
            
            
        }
 
   
    
    if (talking) {
        Talking_Rush*talk_layer=(Talking_Rush*)this->getChildByTag(5);
        if (talk_layer->over) {
            talking=false;
            this->removeChildByTag(5);
        }
        
    }
    else if(!talking){
        if (!changescene) {
            return;
        }
        zhaoyun_r*t=static_cast<Nofight_Scene_Base*>(this->getChildByTag(1))->zy;
        if (base->getChildByTag(10)->boundingBox().containsPoint(t->getPosition())&&!changing) {
            changing=true;
            Director::getInstance()->replaceScene(TransitionFade::create(1.5,First_hurdle::createScene()));
        }
    }
    
}


