//
//  xiangyu.cpp
//  animate_homework
//
//  Created by mac on 15-8-5.
//
//

#include "xiangyu.h"
#include "zhaoyun.h"
#include "Animation_itools.h"
#include "UI_Layer.h"
USING_NS_CC;
bool xiangyu::init(){
    if (!zhaoyun::init()) {
        return false;
    }
    name="xiangyu";
    winsize=Director::getInstance()->getWinSize();
    animate=false;
    Max_Hp=130;
    nowhp=Max_Hp;
    make_comb=false;
    
    
    //未写的
    atk=4.5;//攻击段数为3.
    Max_mp=20;
    nowmp=20;
    lv=1;  //等级
    Max_exe=50;//最大经验
    nowexe=0;//当前经验
    speed=5.5;//速度
    //未写的
    ui_name="项羽";
    ui_picture="项羽.png";
    ui_description="项羽，西楚霸王。。待写没网";
    
    
    this->initWithFile("xiangy.png",Rect(0,0,192/4,256/4));
    
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

void xiangyu::loading_animation(){
    AnimationCache* ac=AnimationCache::getInstance();
    Animation*rundown=itool->makeAnimationfrommixpicture("xiangy.png",4,4,1,1,4,1,0.1f,true,-1);
    ac->addAnimation(rundown,"xiangyugodown");
    Animation*goleft=itool->makeAnimationfrommixpicture("xiangy.png",4,4,1,2,4,2,0.1f,true,-1);
    ac->addAnimation(goleft,"xiangyugoleft");
    Animation*goright=itool->makeAnimationfrommixpicture("xiangy.png",4,4,1,3,4,3,0.1f,true,-1);
    ac->addAnimation(goright,"xiangyugoright");
    Animation*goup=itool->makeAnimationfrommixpicture("xiangy.png",4,4,1,4,4,4,0.1f,true,-1);
    ac->addAnimation(goup,"xiangyugoup");
    
    Animation*attackdown=itool->makeAnimationfrommixpicture("xiangy_melee.png",4,4,1,1,4,1,0.2f,true,1);
    ac->addAnimation(attackdown,"xiangyuAdown");
    Animation*attackleft=itool->makeAnimationfrommixpicture("xiangy_melee.png",4,4,1,2,4,2,0.2f,true,1);
    ac->addAnimation(attackleft,"xiangyuAleft");
    Animation*attackright=itool->makeAnimationfrommixpicture("xiangy_melee.png",4,4,1,3,4,3,0.2f,true,1);
    ac->addAnimation(attackright,"xiangyuAright");
    Animation*attackup=itool->makeAnimationfrommixpicture("xiangy_melee.png",4,4,1,4,4,4,0.2f,true,1);
    ac->addAnimation(attackup,"xiangyuAup");
    
}
void xiangyu::update(float dt){
    
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
            walk("xiangyugodown");
            animate=true;
        }
        else if (k==2) {
            direction=k;
            walk("xiangyugoleft");
            animate=true;
        }
        else if (k==3) {
            direction=k;
            walk("xiangyugoright");
            animate=true;
        }
        else if (k==4) {
            animate=true;
            direction=k;
            walk("xiangyugoup");
        }
        else if(k==5){
            scheduleOnce(schedule_selector(zhaoyun::attack_update),0);
            animate=true;
        }
    }
    move(k);
    
    
}
void xiangyu::attack_update(float dt){
    switch (direction) {
        case 1:
            attack("xiangyuAdown");
            break;
        case 2:
            attack("xiangyuAleft");
            break;
        case 3:
            attack("xiangyuAright");
            break;
        case 4:
            attack("xiangyuAup");
            break;
            
        default:
            break;
    }
    
}
void xiangyu::level_up(){
    lv++;
    Max_Hp+=120;
    nowhp=Max_Hp;
    atk+=0.8;
    Max_mp=50+5*(lv-1);
    speed+=0.1;
    nowmp=Max_mp;
    Max_exe=pow(lv,2)*50;//最大经验
    nowexe=0;//当前经验
}
