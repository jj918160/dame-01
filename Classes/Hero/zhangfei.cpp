//
//  zhangfei.cpp
//  animate_homework
//
//  Created by mac on 15-8-4.
//
//

#include "zhangfei.h"
#include "zhaoyun.h"
#include "Animation_itools.h"
#include "UI_Layer.h"
USING_NS_CC;
bool zhangfei::init(){
    if (!zhaoyun::init()) {
        return false;
    }
    name="zhangfei";
    winsize=Director::getInstance()->getWinSize();
    animate=false;
    Max_Hp=110;
    nowhp=Max_Hp;
    make_comb=false;
    
    
    //未写的
    atk=3.2;//攻击段数为3.
    Max_mp=20;
    nowmp=20;
    lv=1;  //等级
    Max_exe=50;//最大经验
    nowexe=0;//当前经验
    speed=4.2;//速度
    //未写的
    ui_name="张翼德";
    ui_picture="张飞.png";
    ui_description="张飞，字翼德，字益德 ，幽州涿郡\n（今河北省保定市涿州市）人氏，三国时\n期蜀汉名将。刘备长坂坡败退，\n张飞仅率二十骑断后，据水断桥\n曹军没人敢逼近；与诸葛亮、赵云扫荡西川时，\n于江州义释严颜；汉中之战时又于宕渠\n击败张郃，对蜀汉贡献极大，\n官至车骑将军、领司隶校尉，封西乡侯，\n后被范强、张达刺杀。后主时代追谥为“桓侯”。\n在中国传统文化中，张飞以其勇猛、鲁莽、\n嫉恶如仇而著称，虽然此形象主\n要来源于小说和戏剧等民间艺术，\n但已深入人心";
    
    
    this->initWithFile("zhf.png",Rect(0,0,192/4,256/4));
    
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

void zhangfei::loading_animation(){
    AnimationCache* ac=AnimationCache::getInstance();
    Animation*rundown=itool->makeAnimationfrommixpicture("zhf.png",4,4,1,1,4,1,0.1f,true,-1);
    ac->addAnimation(rundown,"zhangfeigodown");
    Animation*goleft=itool->makeAnimationfrommixpicture("zhf.png",4,4,1,2,4,2,0.1f,true,-1);
    ac->addAnimation(goleft,"zhangfeigoleft");
    Animation*goright=itool->makeAnimationfrommixpicture("zhf.png",4,4,1,3,4,3,0.1f,true,-1);
    ac->addAnimation(goright,"zhangfeigoright");
    Animation*goup=itool->makeAnimationfrommixpicture("zhf.png",4,4,1,4,4,4,0.1f,true,-1);
    ac->addAnimation(goup,"zhangfeigoup");
    
    Animation*attackdown=itool->makeAnimationfrommixpicture("zhf_melee.png",4,4,1,1,4,1,0.2f,true,1);
    ac->addAnimation(attackdown,"zhangfeiAdown");
    Animation*attackleft=itool->makeAnimationfrommixpicture("zhf_melee.png",4,4,1,2,4,2,0.2f,true,1);
    ac->addAnimation(attackleft,"zhangfeiAleft");
    Animation*attackright=itool->makeAnimationfrommixpicture("zhf_melee.png",4,4,1,3,4,3,0.2f,true,1);
    ac->addAnimation(attackright,"zhangfeiAright");
    Animation*attackup=itool->makeAnimationfrommixpicture("zhf_melee.png",4,4,1,4,4,4,0.2f,true,1);
    ac->addAnimation(attackup,"zhangfeiAup");
    
}
void zhangfei::update(float dt){
    
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
            walk("zhangfeigodown");
            animate=true;
        }
        else if (k==2) {
            direction=k;
            walk("zhangfeigoleft");
            animate=true;
        }
        else if (k==3) {
            direction=k;
            walk("zhangfeigoright");
            animate=true;
        }
        else if (k==4) {
            animate=true;
            direction=k;
            walk("zhangfeigoup");
        }
        else if(k==5){
            scheduleOnce(schedule_selector(zhaoyun::attack_update),0);
            animate=true;
        }
    }
    move(k);
    
    
}
void zhangfei::attack_update(float dt){
    switch (direction) {
        case 1:
            attack("zhangfeiAdown");
            break;
        case 2:
            attack("zhangfeiAleft");
            break;
        case 3:
            attack("zhangfeiAright");
            break;
        case 4:
            attack("zhangfeiAup");
            break;
            
        default:
            break;
    }
    
}
void zhangfei::level_up(){
    lv++;
    Max_Hp=110+15*(lv-1);
    nowhp=Max_Hp;
    atk+=0.7;
    Max_mp=20+5*(lv-1);
    nowmp=Max_mp;
    Max_exe=pow(lv,2)*50;//最大经验
    nowexe=0;//当前经验
}
