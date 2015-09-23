//
//  Loadind_layer.cpp
//  animate_homework
//
//  Created by mac on 15-7-31.
//
//
#include "zhaoyun_r.h"
#include "UIr_Layer.h"
#include "Loadind_layer.h"
#include "First_Scene.h"
#include "Talking_Rush.h"
#include "SimpleAudioEngine.h"
#include "Animation_itools.h"
USING_NS_CC;
using namespace CocosDenshion;
cocos2d::Scene* Loading_layer::createScene(){
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Loading_layer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
bool Loading_layer::init(){
    if (!Layer::init()) {
        return false;
    }
    add=false;
    SimpleAudioEngine::getInstance()->playBackgroundMusic("p85青冥剑誓·变调.mp3",true);
    
    auto sp=Sprite::create("Loading_layer_back.png");
    sp->setPosition(480,320);
    this->addChild(sp,0,0);
    
    zhaoyun_r*zy=zhaoyun_r::create();
    zy->setPosition(800,100);
    zy->set_speed(8);
    this->addChild(zy,2,1);
    scheduleOnce(schedule_selector(Loading_layer::change_tp1), 3.0);
    
          

   auto  ui_layer=UIr_Layer::create();
  
    ui_layer->type=5;
  
   
    
    return true;
}

void Loading_layer::update(float dt){

    Talking_Rush*t=static_cast<Talking_Rush*>(this->getChildByTag(3));
    if (t->over==true) {
        this->removeChild(t);
        t=nullptr;
        auto  ui_layer=UIr_Layer::create();
        ui_layer->type=0;
        this->addChild(ui_layer,2,2);
        
        auto sp=Sprite::create();
        sp->setPosition(20,20);
        AnimationCache* ac=AnimationCache::getInstance();
        Animation *a=ac->getAnimation("changescene");
        Animate* animate=Animate::create(a);
        sp->runAction(animate);
        this->addChild(sp,2,3);
        
        schedule(schedule_selector(Loading_layer::change_4), 0.01);
        unscheduleUpdate();
    }
    
}
void Loading_layer::change_tp1(float dt){
  
    UIr_Layer::type=3;
     scheduleOnce(schedule_selector(Loading_layer::change_tp2), 0.3);
}
void Loading_layer::change_tp2(float dt){
  
     UIr_Layer::type=2;
     scheduleOnce(schedule_selector(Loading_layer::change_tp3), 0.4);
}
void Loading_layer::change_tp3(float dt){
    
    UIr_Layer::type=0;
     std::vector<std::string> v_t;
    v_t=itools->load_mssage("/Users/mac/Desktop/beifenwork/dame1/Resources/homeworkpic/talk/dubai.txt", v_t);
    
        auto talk_layer=Talking_Rush::create(v_t, "301.png", "325.png",1);
    
//     v_t=itools->load_mssage("/Users/mac/Desktop/homeworkpic/talk/talk1.txt", v_t);
//    
//     auto talk_layer=Talking_Rush::create(v_t);
//    
    
    
       this->addChild(talk_layer,1,3);
    
   
    
     scheduleUpdate();

}
void Loading_layer::change_4(float dt){
        zhaoyun_r*t=(zhaoyun_r*)this->getChildByTag(1);
        if (t->getPositionX()<20&&t->getPositionY()<20&&!change) {
            change=true;
            Director::getInstance()->replaceScene(TransitionFade::create(1.5,First_Scene::createScene()));
        }
        if (t->getPositionY()>250) {
            t->setPositionY(250);
        }

}