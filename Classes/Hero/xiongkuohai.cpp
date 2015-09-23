//
//  xiongkuohai.cpp
//  animate_homework
//
//  Created by mac on 15-8-5.
//
//

#include "xiongkuohai.h"
#include "zhaoyun.h"
#include "Animation_itools.h"
#include "UI_Layer.h"
USING_NS_CC;
bool xiongkuohai::init(){
    if (!zhaoyun::init()) {
        return false;
    }
    last_name="xiongkh";
    name="xiongkuohai";
    winsize=Director::getInstance()->getWinSize();
    animate=false;
    Max_Hp=150;
    nowhp=Max_Hp;
    make_comb=false;
    
    
    //未写的
    atk=5.5;//攻击段数为3.
    Max_mp=20;
    nowmp=20;
    lv=1;  //等级
    Max_exe=50;//最大经验
    nowexe=0;//当前经验
    speed=3.0;//速度
    //未写的
    ui_name="雄阔海";
    ui_picture="雄阔海.png";
    ui_description="雄阔海，隋唐第四条好汉。。待写没网";
    
    
    this->initWithFile("xiongkh.png",Rect(0,0,192/4,256/4));
    
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
void xiongkuohai::update(float dt){
    
    Sprite*hpimage=(Sprite*)this->getChildByTag(2);
    
    float sca=nowhp/float(Max_Hp);
    
    hpimage->setScaleY(sca);
    float t=hpimage->getScaleY();

    int k=UI_Layer::type;
    
    
    if (k==0||yester_direction!=k) {
        animate=false;
        this->stopAllActions();
    }
    if (animate==false) {
        yester_direction=k;
        if (k==1) {
            direction=k;
            walk("xiongkuohaigodown");
            animate=true;
        }
        else if (k==2) {
            direction=k;
            walk("xiongkuohaigoleft");
            animate=true;
        }
        else if (k==3) {
            direction=k;
            walk("xiongkuohaigoright");
            animate=true;
        }
        else if (k==4) {
            animate=true;
            direction=k;
            walk("xiongkuohaigoup");
        }
        else if(k==5){
            scheduleOnce(schedule_selector(zhaoyun::attack_update),0);
            animate=true;
        }
    }
    move(k);
    
    
}


void xiongkuohai::level_up(){
    lv++;
    Max_Hp+=80;
    nowhp=Max_Hp;
    atk+=0.9;
    Max_mp=20+5*(lv-1);
    nowmp=Max_mp;
    speed+=0.1;
    Max_exe=pow(lv,2)*50;//最大经验
    nowexe=0;//当前经验
}
