//
//  First_Scene.cpp
//  animate_homework
//
//  Created by mac on 15-7-31.
//
//
#include "liubei.h"
#include "guanyu.h"
#include "zhangfei.h"
#include "Second_Scene.h"
#include "zhugeliang.h"
#include "Player.h"
#include "Animation_itools.h"
#include "First_Scene.h"
#include "Talking_Rush.h"
#include "First_hurdle.h"
#include "zhaoyun_r.h"
#include "UIr_Layer.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio::timeline;
using namespace CocosDenshion;
cocos2d::Scene* First_Scene::createScene(){
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = First_Scene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
bool First_Scene::init(){
    if (!Layer::init()) {
        return false;
    }
    isadding=false;
    addok=false;
    change=false;
    talking=false;
    changescene=false;
    renwu_jindu=0;
 
    SimpleAudioEngine::getInstance()->playBackgroundMusic("p42凤尾丝竹·变调.mp3",true);
    LoadingAnimation();
    auto sp=Sprite::create("first_scene.jpg");
    sp->setPosition(480,320);
    this->addChild(sp,0,0);
 
    auto sp1=Sprite::create();
    sp1->setPosition(600,520);
    AnimationCache* ac=AnimationCache::getInstance();
    Animation *a=ac->getAnimation("npc1_s");
    Animate* animate=Animate::create(a);
    sp1->runAction(animate);
    this->addChild(sp1,1,3);
    
    
    auto sp2=Sprite::create();
    sp2->setPosition(400,520);
    Animation *b=ac->getAnimation("npc2_s");
    Animate* animate2=Animate::create(b);
    sp2->runAction(animate2);
    this->addChild(sp2,1,4);
 
    CCLOG("a");
      auto NootGuanyu=CSLoader::createNode("Node.csb");
      auto Noodguanyuaction=CSLoader::createTimeline("Node.csb");
      this->addChild(NootGuanyu,1,6);
  
      NootGuanyu->runAction(Noodguanyuaction);
      Noodguanyuaction->gotoFrameAndPlay(0,20,true);
    
    Sprite*spgy=(Sprite*)NootGuanyu->getChildByTag(18);
    spgy->setPosition(300,300);
//    this->addChild(spgy,1,6);

    CCLOG("b");

    
//    TextField* t1=Text::create();
//    Widget
    
    
    zhaoyun_r*zy=zhaoyun_r::create();
    zy->setPosition(940,100);
    zy->set_speed(8);
    this->addChild(zy,2,1);
    
    
    
    auto uilayer=UIr_Layer::create();
    uilayer->type=0;
    uilayer->set_workstring("任务:和刘备对话。");
    this->addChild(uilayer,2,2);
    
    
    auto listener=EventListenerTouchOneByOne::create();
    listener->onTouchBegan=[=](Touch*touch,Event*event){
          
        if (this->getChildByTag(3)->getBoundingBox().containsPoint(touch->getLocation())&&!talking){
            this->getChildByTag(3)->runAction(Sequence::create(ScaleTo::create(0.1, 1.2),ScaleTo::create(0.1, 1.0) ,NULL));
            talking=true;
            talk_1();
                return true;
        }
        else if (this->getChildByTag(4)&&this->getChildByTag(4)->getBoundingBox().containsPoint(touch->getLocation())&&!talking){
             this->getChildByTag(4)->runAction(Sequence::create(ScaleTo::create(0.1, 1.2),ScaleTo::create(0.1, 1.0) ,NULL));
            talking=true;
            talk_2();
            return true;
        }
        else if (this->getChildByTag(6)&&this->getChildByTag(6)->getChildByTag(18)->getBoundingBox().containsPoint(touch->getLocation())&&!talking){
            this->getChildByTag(6)->runAction(Sequence::create(ScaleTo::create(0.1, 1.2),ScaleTo::create(0.1, 1.0) ,NULL));
            talking=true;
            if (renwu_jindu==1) {
                talk_3();
            }
            else {
                talk_1();
            }
            return true;
        }
        return false;
            };
         
 Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
    
    scheduleUpdate();
    
    return true;
}



void First_Scene::update(float dt){
    if (addok&&!isadding) {
        Player*p=Player::getInstance();
        zhugeliang*zgl=zhugeliang::create();
        p->addhero(zgl);
        
        guanyu*gy=guanyu::create();
        p->addhero(gy);
        
        zhangfei*zf=zhangfei::create();
        p->addhero(zf);
        
        liubei*lb=liubei::create();
        p->addhero(lb);

        
        
        isadding=true;
        Vector<Node*> vn=this->getChildren();
        for(auto i:vn){
            if (i->getTag()==4||i->getTag()==6) {
                i->runAction(Sequence::create(FadeOut::create(1.0f),
                                              RemoveSelf::create(),
                                              NULL));
            }
            else{
            i->runAction(Sequence::create(FadeOut::create(1.0f),
                                           DelayTime::create(1.0f),
                                            FadeIn::create(1.0f),NULL));
            }
    }
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
        zhaoyun_r*t=static_cast<zhaoyun_r*>(this->getChildByTag(1));
    if (t->getPositionX()<30&&t->getPositionY()<30&&!change) {
        change=true;
          Director::getInstance()->replaceScene(TransitionFade::create(1.5,Second_Scene::createScene()));
    }
    }
    
}

void First_Scene::talk_1(){
    std::vector<std::string> v_t;
         v_t=itools->load_mssage("/Users/mac/Desktop/homeworkpic/talk/talk1.txt", v_t);
    
         auto talk_layer=Talking_Rush::create(v_t);
    this->addChild(talk_layer,1,5);
  
}
void First_Scene::talk_3(){
    std::vector<std::string> v_t;
    v_t=itools->load_mssage("/Users/mac/Desktop/homeworkpic/talk/talk2.txt", v_t);
    auto talk_layer=Talking_Rush::create(v_t);
    this->addChild(talk_layer,1,5);
    renwu_jindu=2;
     schedule(schedule_selector(First_Scene::addhero1),1/60);
   
}

void First_Scene::talk_2(){
    std::vector<std::string> v_t;
      v_t=itools->load_mssage("/Users/mac/Desktop/homeworkpic/talk/talk3.txt", v_t);

    Talking_Rush*talk_layer=Talking_Rush::create(v_t, "301.png", "403.png",2);
    this->addChild(talk_layer,1,5);
    changescene=true;
    
    auto sp=Sprite::create();
    sp->setPosition(20,20);
    AnimationCache* ac=AnimationCache::getInstance();
    Animation *a=ac->getAnimation("changescene");
    Animate* animate=Animate::create(a);
    sp->runAction(animate);
    this->addChild(sp,2,10);
    
    UIr_Layer*ui=(UIr_Layer*)this->getChildByTag(2);
    ui->set_workstring("任务:从左下角去长板坡\n帮刘备救老婆孩子");
    renwu_jindu=1;
    
}



void First_Scene::LoadingAnimation(){
    AnimationCache* ac=AnimationCache::getInstance();
    Animation*stand1=itools->makeAnimationfromPlist("NPC_1_stad.plist", "37082-%d.png",4,1,0.2,true,-1);
    ac->addAnimation(stand1,"npc1_s");
    Animation*stand2=itools->makeAnimationfromPlist("NPC_2_stand.plist", "36990-%d.png",4,1,0.2,true,-1);
    ac->addAnimation(stand2,"npc2_s");
}
void First_Scene::addhero1(float dt){
    auto tk=(Talking_Rush*)this->getChildByTag(5);
    if (!tk&&renwu_jindu==2) {
        addok=true;
        unschedule(schedule_selector(First_Scene::addhero1));
    }
}
