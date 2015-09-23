//
//  guanyu.cpp
//  animate_homework
//
//  Created by mac on 15-8-4.
//
//

#include "guanyu.h"
#include "zhaoyun.h"
#include "Animation_itools.h"
#include "UI_Layer.h"
USING_NS_CC;
bool guanyu::init(){
    if (!zhaoyun::init()) {
        return false;
    }
    name="guanyu";
    winsize=Director::getInstance()->getWinSize();
    animate=false;
    Max_Hp=120;
    nowhp=Max_Hp;
    make_comb=false;
    
    
    //未写的
    atk=2.8;//攻击段数为3.
    Max_mp=20;
    nowmp=20;
    lv=1;  //等级
    Max_exe=50;//最大经验
    nowexe=0;//当前经验
    speed=4.5;//速度
    //未写的
    ui_name="关羽";
    ui_picture="关羽.png";
    ui_description="关羽，字云长，河东解良人，东汉末年\n名将，早期跟随刘备辗转各地，曾被曹\n操生擒，于白马坡斩杀袁绍大将颜良，与张\n飞一同被称为万人敌。\n赤壁之战后，刘备助东吴周瑜攻打南郡曹仁，别遣\n关羽绝北道，阻挡曹操\n援军，曹仁退走后，关羽被封为\n襄阳太守。刘备入益州，\n关羽留守荆州。建安二十四年，关羽\n围襄樊，曹操派于禁前来增援，\n关羽擒获于禁，斩杀庞德，威震华夏，\n曹操曾想迁都以避其锐。后曹\n操派徐晃前来增援，东吴吕蒙又偷袭荆州，关羽腹背\n受敌，兵败被杀。关羽去世后，逐渐被\n神化，被民间尊为“关公”，又称美髯公。";
    
    
    this->initWithFile("guy.png",Rect(0,0,192/4,256/4));
    
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

void guanyu::loading_animation(){
    AnimationCache* ac=AnimationCache::getInstance();
    Animation*rundown=itool->makeAnimationfrommixpicture("guy.png",4,4,1,1,4,1,0.1f,true,-1);
    ac->addAnimation(rundown,"guanyugodown");
    Animation*goleft=itool->makeAnimationfrommixpicture("guy.png",4,4,1,2,4,2,0.1f,true,-1);
    ac->addAnimation(goleft,"guanyugoleft");
    Animation*goright=itool->makeAnimationfrommixpicture("guy.png",4,4,1,3,4,3,0.1f,true,-1);
    ac->addAnimation(goright,"guanyugoright");
    Animation*goup=itool->makeAnimationfrommixpicture("guy.png",4,4,1,4,4,4,0.1f,true,-1);
    ac->addAnimation(goup,"guanyugoup");
    
    Animation*attackdown=itool->makeAnimationfrommixpicture("guy_melee.png",4,4,1,1,4,1,0.2f,true,1);
    ac->addAnimation(attackdown,"guanyuAdown");
    Animation*attackleft=itool->makeAnimationfrommixpicture("guy_melee.png",4,4,1,2,4,2,0.2f,true,1);
    ac->addAnimation(attackleft,"guanyuAleft");
    Animation*attackright=itool->makeAnimationfrommixpicture("guy_melee.png",4,4,1,3,4,3,0.2f,true,1);
    ac->addAnimation(attackright,"guanyuAright");
    Animation*attackup=itool->makeAnimationfrommixpicture("guy_melee.png",4,4,1,4,4,4,0.2f,true,1);
    ac->addAnimation(attackup,"guanyuAup");
    
}
void guanyu::update(float dt){
    
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
            walk("guanyugodown");
            animate=true;
        }
        else if (k==2) {
            direction=k;
            walk("guanyugoleft");
            animate=true;
        }
        else if (k==3) {
            direction=k;
            walk("guanyugoright");
            animate=true;
        }
        else if (k==4) {
            animate=true;
            direction=k;
            walk("guanyugoup");
        }
        else if(k==5){
            scheduleOnce(schedule_selector(zhaoyun::attack_update),0);
            animate=true;
        }
    }
    move(k);
    
    
}
void guanyu::attack_update(float dt){
    switch (direction) {
        case 1:
            attack("guanyuAdown");
            break;
        case 2:
            attack("guanyuAleft");
            break;
        case 3:
            attack("guanyuAright");
            break;
        case 4:
            attack("guanyuAup");
            break;
            
        default:
            break;
    }
    
}
void guanyu::level_up(){
    lv++;
    Max_Hp=120+18*(lv-1);
    nowhp=Max_Hp;
    atk+=0.6;
    Max_mp=20+5*(lv-1);
    nowmp=Max_mp;
    Max_exe=pow(lv,2)*50;//最大经验
    nowexe=0;//当前经验
}
