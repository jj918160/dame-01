//
//  huangzhong.cpp
//  animate_homework
//
//  Created by mac on 15-8-3.
//
//

#include "huangzhong.h"
#include "zhaoyun.h"
#include "Animation_itools.h"
#include "UI_Layer.h"
USING_NS_CC;
bool huangzhong::init(){
    if (!zhaoyun::init()) {
        return false;
    }
    name="huangzhong";
    winsize=Director::getInstance()->getWinSize();
    animate=false;
    Max_Hp=100;
    nowhp=100;
    make_comb=false;
    
    
    //未写的
    atk=2.5;//攻击段数为3.
    Max_mp=20;
    nowmp=20;
    lv=1;  //等级
    Max_exe=50;//最大经验
    nowexe=0;//当前经验
    speed=3.5;//速度
    //未写的
    ui_name="黄忠";
    ui_picture="403.png";
    ui_description="黄忠，字汉升，南阳（今河南南阳）\n人。东汉末年名将。本为刘\n表部下中郎将，后归刘备，\n并助刘备攻益州刘璋。公元219年，\n黄忠在定军山一战中\n阵斩曹操部下名将夏侯渊，\n升任征西将军，刘备\n称汉中王后改封后将军，赐\n关内侯。次年，黄忠病逝，谥曰\n刚侯。";
    
    
    this->initWithFile("hz.png",Rect(0,0,192/4,256/4));
    
    Sprite*maxhp=Sprite::create("max_hp.0.png");
    maxhp->setRotation(90);
    maxhp->setAnchorPoint(ccp(0.5,0));
    maxhp->setPosition(0,this->getContentSize().height);
    this->addChild(maxhp,0,1);
    
    
    Sprite*hp=Sprite::create("hp.png");
    hp->setPosition(0,this->getContentSize().height);
    hp->setRotation(90);
    hp->setAnchorPoint(ccp(0.5,0));
    this->addChild(hp,0,2);
    
    
    
    loading_animation();
    
    
    scheduleUpdate();
   
    
    return true;
}

//void huangzhong::onEnter(){
//    zhaoyun::onEnter();
//    scheduleUpdate();
//}
//
//void huangzhong::onExit(){
//    zhaoyun::onExit();
//    unscheduleUpdate();
//}
void huangzhong::loading_animation(){
    AnimationCache* ac=AnimationCache::getInstance();
    Animation*rundown=itool->makeAnimationfrommixpicture("hz.png",4,4,1,1,4,1,0.1f,true,-1);
    ac->addAnimation(rundown,"hzgodown");
    Animation*goleft=itool->makeAnimationfrommixpicture("hz.png",4,4,1,2,4,2,0.1f,true,-1);
    ac->addAnimation(goleft,"hzgoleft");
    Animation*goright=itool->makeAnimationfrommixpicture("hz.png",4,4,1,3,4,3,0.1f,true,-1);
    ac->addAnimation(goright,"hzgoright");
    Animation*goup=itool->makeAnimationfrommixpicture("hz.png",4,4,1,4,4,4,0.1f,true,-1);
    ac->addAnimation(goup,"hzgoup");
    
    Animation*attackdown=itool->makeAnimationfrommixpicture("hz_melee.png",4,4,1,1,4,1,0.2f,true,1);
    ac->addAnimation(attackdown,"hzAdown");
    Animation*attackleft=itool->makeAnimationfrommixpicture("hz_melee.png",4,4,1,2,4,2,0.2f,true,1);
    ac->addAnimation(attackleft,"hzAleft");
    Animation*attackright=itool->makeAnimationfrommixpicture("hz_melee.png",4,4,1,3,4,3,0.2f,true,1);
    ac->addAnimation(attackright,"hzAright");
    Animation*attackup=itool->makeAnimationfrommixpicture("hz_melee.png",4,4,1,4,4,4,0.2f,true,1);
    ac->addAnimation(attackup,"hzAup");

}
void huangzhong::update(float dt){
    
    Sprite*hpimage=(Sprite*)this->getChildByTag(2);
    
    float sca=nowhp/float(Max_Hp);
   
    hpimage->setScaleY(sca);
    float t=hpimage->getScaleY();
//    CCLOG("%f",sca);
//    CCLOG("t:%f",t);
//    
//    CCLOG("%d/%d",nowhp,Max_Hp);
    
    int k=UI_Layer::type;
    
    
    if (k==0||yester_direction!=k) {
        animate=false;
        this->stopAllActions();
    }
    if (animate==false) {
        yester_direction=k;
        if (k==1) {
            direction=k;
            walk("hzgodown");
            animate=true;
        }
        else if (k==2) {
            direction=k;
            walk("hzgoleft");
            animate=true;
        }
        else if (k==3) {
            direction=k;
            walk("hzgoright");
            animate=true;
        }
        else if (k==4) {
            animate=true;
            direction=k;
            walk("hzgoup");
        }
        else if(k==5){
            scheduleOnce(schedule_selector(zhaoyun::attack_update),0);
            animate=true;
        }
    }
    move(k);
  

}
void huangzhong::attack_update(float dt){
    switch (direction) {
        case 1:
            attack("hzAdown");
            break;
        case 2:
            attack("hzAleft");
            break;
        case 3:
            attack("hzAright");
            break;
        case 4:
            attack("hzAup");
            break;
            
        default:
            break;
    }

}
void huangzhong::level_up(){
    lv++;
    Max_Hp=100+15*(lv-1);
    nowhp=Max_Hp;
    atk+=0.5;
    Max_mp=20+5*(lv-1);
    nowmp=Max_mp;
    Max_exe=pow(lv,2)*50;//最大经验
    nowexe=0;//当前经验
}
