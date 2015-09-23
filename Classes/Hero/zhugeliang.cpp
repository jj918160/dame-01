//
//  zhugeliang.cpp
//  animate_homework
//
//  Created by mac on 15-8-4.
//
//

#include "zhugeliang.h"
#include "zhaoyun.h"
#include "Animation_itools.h"
#include "UI_Layer.h"
USING_NS_CC;
bool zhugeliang::init(){
    if (!zhaoyun::init()) {
        return false;
    }
    name="zhugeliang";
    winsize=Director::getInstance()->getWinSize();
    animate=false;
    Max_Hp=80;
    nowhp=Max_Hp;
    make_comb=false;
    
    
    //未写的
    atk=5;//攻击段数为3.
    Max_mp=50;
    nowmp=50;
    lv=1;  //等级
    Max_exe=50;//最大经验
    nowexe=0;//当前经验
    speed=3;//速度
    //未写的
    ui_name="诸葛亮";
    ui_picture="诸葛亮.png";
    ui_description="诸葛亮，字孔明，号卧龙，汉族，徐州琅琊\n阳都人，三国时期蜀汉丞相，杰出的政治家、\n军事家、散文家、书法家、发明家。在世时\n被封为武乡侯，死后追谥忠武侯，东晋政权\n因其军事才能特追封他为武兴王。其散文代表\n作有《出师表》、《诫子书》等。曾发明木\n牛流马、孔明灯等，并改造连弩，叫做诸葛\n连弩，可一弩十矢俱发。于建兴十二年\n（234年）在五丈原逝世。";
    
    
    this->initWithFile("zgl.png",Rect(0,0,192/4,256/4));
    
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

void zhugeliang::loading_animation(){
    AnimationCache* ac=AnimationCache::getInstance();
    Animation*rundown=itool->makeAnimationfrommixpicture("zgl.png",4,4,1,1,4,1,0.1f,true,-1);
    ac->addAnimation(rundown,"zhugelianggodown");
    Animation*goleft=itool->makeAnimationfrommixpicture("zgl.png",4,4,1,2,4,2,0.1f,true,-1);
    ac->addAnimation(goleft,"zhugelianggoleft");
    Animation*goright=itool->makeAnimationfrommixpicture("zgl.png",4,4,1,3,4,3,0.1f,true,-1);
    ac->addAnimation(goright,"zhugelianggoright");
    Animation*goup=itool->makeAnimationfrommixpicture("zgl.png",4,4,1,4,4,4,0.1f,true,-1);
    ac->addAnimation(goup,"zhugelianggoup");
    
    Animation*attackdown=itool->makeAnimationfrommixpicture("zgl_melee.png",4,4,1,1,4,1,0.2f,true,1);
    ac->addAnimation(attackdown,"zhugeliangAdown");
    Animation*attackleft=itool->makeAnimationfrommixpicture("zgl_melee.png",4,4,1,2,4,2,0.2f,true,1);
    ac->addAnimation(attackleft,"zhugeliangAleft");
    Animation*attackright=itool->makeAnimationfrommixpicture("zgl_melee.png",4,4,1,3,4,3,0.2f,true,1);
    ac->addAnimation(attackright,"zhugeliangAright");
    Animation*attackup=itool->makeAnimationfrommixpicture("zgl_melee.png",4,4,1,4,4,4,0.2f,true,1);
    ac->addAnimation(attackup,"zhugeliangAup");
    
}
void zhugeliang::update(float dt){
    
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
            walk("zhugelianggodown");
            animate=true;
        }
        else if (k==2) {
            direction=k;
            walk("zhugelianggoleft");
            animate=true;
        }
        else if (k==3) {
            direction=k;
            walk("zhugelianggoright");
            animate=true;
        }
        else if (k==4) {
            animate=true;
            direction=k;
            walk("zhugelianggoup");
        }
        else if(k==5){
            scheduleOnce(schedule_selector(zhaoyun::attack_update),0);
            animate=true;
        }
    }
    move(k);
    
    
}
void zhugeliang::attack_update(float dt){
    switch (direction) {
        case 1:
            attack("zhugeliangAdown");
            break;
        case 2:
            attack("zhugeliangAleft");
            break;
        case 3:
            attack("zhugeliangAright");
            break;
        case 4:
            attack("zhugeliangAup");
            break;
            
        default:
            break;
    }
    
}
void zhugeliang::level_up(){
    lv++;
    Max_Hp+=10;
    nowhp=Max_Hp;
    atk+=1.0;
    Max_mp=50+5*(lv-1);
    nowmp=Max_mp;
    Max_exe=pow(lv,2)*50;//最大经验
    nowexe=0;//当前经验
}
