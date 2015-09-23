//
//  liubei.cpp
//  animate_homework
//
//  Created by mac on 15-8-4.
//
//

#include "liubei.h"
#include "zhaoyun.h"
#include "Animation_itools.h"
#include "UI_Layer.h"
USING_NS_CC;
bool liubei::init(){
    if (!zhaoyun::init()) {
        return false;
    }
    name="liubei";
    winsize=Director::getInstance()->getWinSize();
    animate=false;
    Max_Hp=200;
    nowhp=Max_Hp;
    make_comb=false;
    
    
    //未写的
    atk=1.8;//攻击段数为3.
    Max_mp=20;
    nowmp=20;
    lv=1;  //等级
    Max_exe=50;//最大经验
    nowexe=0;//当前经验
    speed=3.8;//速度
    //未写的
    ui_name="刘备";
    ui_picture="刘备.png";
    ui_description="刘备字玄德，东汉末年幽州涿郡涿县人，西汉\n中山靖王刘胜的后代，三国时期蜀汉开国皇帝，\n政治家，史家又称他为先主刘备少年与公孙瓒\n拜卢植为师求学，而后参与镇压黄巾起义。与关\n羽、张飞先后救援过北海孔融、徐州陶谦等。刘备\n早期颠沛流离，后于赤壁之战与孙权联盟击败曹操，\n趁势夺取荆州，而后进取益州，建立蜀汉政权。陈寿\n评刘备机权干略不及曹操，但其弘毅宽厚，知人待士，\n百折不挠，终成帝业。刘备自己也曾说过，自己做事\n“每与操反，事乃成尔”。公元221年，刘备在成都称帝，\n国号汉，年号章武，史称蜀或蜀汉\n公元223年，刘备病逝于白帝城，终年63岁，\n谥号昭烈皇帝.";
    
    
    this->initWithFile("liub.png",Rect(0,0,192/4,256/4));
    
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

void liubei::loading_animation(){
    AnimationCache* ac=AnimationCache::getInstance();
    Animation*rundown=itool->makeAnimationfrommixpicture("liub.png",4,4,1,1,4,1,0.1f,true,-1);
    ac->addAnimation(rundown,"liubeigodown");
    Animation*goleft=itool->makeAnimationfrommixpicture("liub.png",4,4,1,2,4,2,0.1f,true,-1);
    ac->addAnimation(goleft,"liubeigoleft");
    Animation*goright=itool->makeAnimationfrommixpicture("liub.png",4,4,1,3,4,3,0.1f,true,-1);
    ac->addAnimation(goright,"liubeigoright");
    Animation*goup=itool->makeAnimationfrommixpicture("liub.png",4,4,1,4,4,4,0.1f,true,-1);
    ac->addAnimation(goup,"liubeigoup");
    
    Animation*attackdown=itool->makeAnimationfrommixpicture("liub_melee.png",4,4,1,1,4,1,0.2f,true,1);
    ac->addAnimation(attackdown,"liubeiAdown");
    Animation*attackleft=itool->makeAnimationfrommixpicture("liub_melee.png",4,4,1,2,4,2,0.2f,true,1);
    ac->addAnimation(attackleft,"liubeiAleft");
    Animation*attackright=itool->makeAnimationfrommixpicture("liub_melee.png",4,4,1,3,4,3,0.2f,true,1);
    ac->addAnimation(attackright,"liubeiAright");
    Animation*attackup=itool->makeAnimationfrommixpicture("liub_melee.png",4,4,1,4,4,4,0.2f,true,1);
    ac->addAnimation(attackup,"liubeiAup");
    
}
void liubei::update(float dt){
    
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
            walk("liubeigodown");
            animate=true;
        }
        else if (k==2) {
            direction=k;
            walk("liubeigoleft");
            animate=true;
        }
        else if (k==3) {
            direction=k;
            walk("liubeigoright");
            animate=true;
        }
        else if (k==4) {
            animate=true;
            direction=k;
            walk("liubeigoup");
        }
        else if(k==5){
            scheduleOnce(schedule_selector(zhaoyun::attack_update),0);
            animate=true;
        }
    }
    move(k);
    
    
}
void liubei::attack_update(float dt){
    switch (direction) {
        case 1:
            attack("liubeiAdown");
            break;
        case 2:
            attack("liubeiAleft");
            break;
        case 3:
            attack("liubeiAright");
            break;
        case 4:
            attack("liubeiAup");
            break;
            
        default:
            break;
    }
    
}
void liubei::level_up(){
    lv++;
    Max_Hp+=15;
    nowhp=Max_Hp;
    atk+=0.4;
    Max_mp=20+5*(lv-1);
    nowmp=Max_mp;
    Max_exe=pow(lv,2)*50;//最大经验
    nowexe=0;//当前经验
}
