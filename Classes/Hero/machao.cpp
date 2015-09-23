//
//  machao.cpp
//  animate_homework
//
//  Created by mac on 15-8-4.
//
//

#include "machao.h"
#include "zhaoyun.h"
#include "Animation_itools.h"
#include "UI_Layer.h"
USING_NS_CC;
bool machao::init(){
    if (!zhaoyun::init()) {
        return false;
    }
    name="macao";
    winsize=Director::getInstance()->getWinSize();
    animate=false;
    Max_Hp=90;
    nowhp=Max_Hp;
    make_comb=false;
    
    
    //未写的
    atk=3.2;//攻击段数为3.
    Max_mp=20;
    nowmp=20;
    lv=1;  //等级
    Max_exe=50;//最大经验
    nowexe=0;//当前经验
    speed=6;//速度
    //未写的
    ui_name="马超";
    ui_picture="马超.png";
    ui_description="马超，字孟起，扶风茂陵人，卫尉马腾\n之子，东汉末年及蜀汉开国名将，汉末群雄之\n一。早年随父征战，马腾入京后，马超留驻割\n据三辅。潼关之战被曹操击败后，又割据陇上\n诸郡。失败后投靠张鲁，又转投刘备。刘备建\n立蜀汉后，马超官至骠骑将军、斄乡侯、凉州\n牧。于章武二年十二月病逝（223年1月），\n终年47岁，追谥威侯。《三国演义》及民间\n文化中绰号“锦马超”，因俊秀容貌与狮盔兽\n带、白袍银甲的非凡装束而得名，\n有“不减吕布之勇”。";
    
    
    this->initWithFile("mac.png",Rect(0,0,192/4,256/4));
    
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

void machao::loading_animation(){
    AnimationCache* ac=AnimationCache::getInstance();
    Animation*rundown=itool->makeAnimationfrommixpicture("mac.png",4,4,1,1,4,1,0.1f,true,-1);
    ac->addAnimation(rundown,"machaogodown");
    Animation*goleft=itool->makeAnimationfrommixpicture("mac.png",4,4,1,2,4,2,0.1f,true,-1);
    ac->addAnimation(goleft,"machaogoleft");
    Animation*goright=itool->makeAnimationfrommixpicture("mac.png",4,4,1,3,4,3,0.1f,true,-1);
    ac->addAnimation(goright,"machaogoright");
    Animation*goup=itool->makeAnimationfrommixpicture("mac.png",4,4,1,4,4,4,0.1f,true,-1);
    ac->addAnimation(goup,"machaogoup");
    
    Animation*attackdown=itool->makeAnimationfrommixpicture("mac_melee.png",4,4,1,1,4,1,0.2f,true,1);
    ac->addAnimation(attackdown,"machaoAdown");
    Animation*attackleft=itool->makeAnimationfrommixpicture("mac_melee.png",4,4,1,2,4,2,0.2f,true,1);
    ac->addAnimation(attackleft,"machaoAleft");
    Animation*attackright=itool->makeAnimationfrommixpicture("mac_melee.png",4,4,1,3,4,3,0.2f,true,1);
    ac->addAnimation(attackright,"machaoAright");
    Animation*attackup=itool->makeAnimationfrommixpicture("mac_melee.png",4,4,1,4,4,4,0.2f,true,1);
    ac->addAnimation(attackup,"machaoAup");
    
}
void machao::update(float dt){
    
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
            walk("machaogodown");
            animate=true;
        }
        else if (k==2) {
            direction=k;
            walk("machaogoleft");
            animate=true;
        }
        else if (k==3) {
            direction=k;
            walk("machaogoright");
            animate=true;
        }
        else if (k==4) {
            animate=true;
            direction=k;
            walk("machaogoup");
        }
        else if(k==5){
            scheduleOnce(schedule_selector(zhaoyun::attack_update),0);
            animate=true;
        }
    }
    move(k);
    
    
}
void machao::attack_update(float dt){
    switch (direction) {
        case 1:
            attack("machaoAdown");
            break;
        case 2:
            attack("machaoAleft");
            break;
        case 3:
            attack("machaoAright");
            break;
        case 4:
            attack("machaoAup");
            break;
            
        default:
            break;
    }
    
}
void machao::level_up(){
    lv++;
    Max_Hp+=12;
    nowhp=Max_Hp;
    atk+=0.75;
    Max_mp=20+5*(lv-1);
    nowmp=Max_mp;
    Max_exe=pow(lv,2)*50;//最大经验
    nowexe=0;//当前经验
}
