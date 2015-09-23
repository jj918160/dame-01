//
//  liyuanba.cpp
//  animate_homework
//
//  Created by mac on 15-8-5.
//
//

#include "liyuanba.h"
#include "zhaoyun.h"
#include "Animation_itools.h"
#include "UI_Layer.h"
USING_NS_CC;
bool liyuanba::init(){
    if (!zhaoyun::init()) {
        return false;
    }
    name="liyuanba";
    winsize=Director::getInstance()->getWinSize();
    animate=false;
    Max_Hp=180;
    nowhp=Max_Hp;
    make_comb=false;
    
    
    //未写的
    atk=6;//攻击段数为3.
    Max_mp=20;
    nowmp=20;
    lv=1;  //等级
    Max_exe=50;//最大经验
    nowexe=0;//当前经验
    speed=4.2;//速度
    //未写的
    ui_name="李元霸";
    ui_picture="李元霸.png";
    ui_description="李元霸，隋唐第一条好汉。。待写没网";
    
    
    this->initWithFile("liyb.png",Rect(0,0,192/4,256/4));
    
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

void liyuanba::loading_animation(){
    AnimationCache* ac=AnimationCache::getInstance();
    Animation*rundown=itool->makeAnimationfrommixpicture("liyb.png",4,4,1,1,4,1,0.1f,true,-1);
    ac->addAnimation(rundown,"liyuanbagodown");
    Animation*goleft=itool->makeAnimationfrommixpicture("liyb.png",4,4,1,2,4,2,0.1f,true,-1);
    ac->addAnimation(goleft,"liyuanbagoleft");
    Animation*goright=itool->makeAnimationfrommixpicture("liyb.png",4,4,1,3,4,3,0.1f,true,-1);
    ac->addAnimation(goright,"liyuanbagoright");
    Animation*goup=itool->makeAnimationfrommixpicture("liyb.png",4,4,1,4,4,4,0.1f,true,-1);
    ac->addAnimation(goup,"liyuanbagoup");
    
    Animation*attackdown=itool->makeAnimationfrommixpicture("liyb_melee.png",4,4,1,1,4,1,0.2f,true,1);
    ac->addAnimation(attackdown,"liyuanbaAdown");
    Animation*attackleft=itool->makeAnimationfrommixpicture("liyb_melee.png",4,4,1,2,4,2,0.2f,true,1);
    ac->addAnimation(attackleft,"liyuanbaAleft");
    Animation*attackright=itool->makeAnimationfrommixpicture("liyb_melee.png",4,4,1,3,4,3,0.2f,true,1);
    ac->addAnimation(attackright,"liyuanbaAright");
    Animation*attackup=itool->makeAnimationfrommixpicture("liyb_melee.png",4,4,1,4,4,4,0.2f,true,1);
    ac->addAnimation(attackup,"liyuanbaAup");
    
}
void liyuanba::update(float dt){
    
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
            walk("liyuanbagodown");
            animate=true;
        }
        else if (k==2) {
            direction=k;
            walk("liyuanbagoleft");
            animate=true;
        }
        else if (k==3) {
            direction=k;
            walk("liyuanbagoright");
            animate=true;
        }
        else if (k==4) {
            animate=true;
            direction=k;
            walk("liyuanbagoup");
        }
        else if(k==5){
            scheduleOnce(schedule_selector(zhaoyun::attack_update),0);
            animate=true;
        }
    }
    move(k);
    
    
}
void liyuanba::attack_update(float dt){
    switch (direction) {
        case 1:
            attack("liyuanbaAdown");
            break;
        case 2:
            attack("liyuanbaAleft");
            break;
        case 3:
            attack("liyuanbaAright");
            break;
        case 4:
            attack("liyuanbaAup");
            break;
            
        default:
            break;
    }
    
}
void liyuanba::level_up(){
    lv++;
    Max_Hp+=100;
    nowhp=Max_Hp;
    atk+=1;
    Max_mp=20+5*(lv-1);
    nowmp=Max_mp;
    Max_exe=pow(lv,2)*50;//最大经验
    nowexe=0;//当前经验
}
