//
//  zhaoyun.cpp
//  animate_homework
//
//  Created by mac on 15-7-16.
//
//

#include "zhaoyun.h"
#include "UI_Layer.h"
#include "map_layer.h"
#include "HelloWorldScene.h"
#include "Animation_itools.h"
USING_NS_CC;

bool zhaoyun::init(){
    if (!Sprite::init()) {
        return false;
    }
    last_name="zy";
    name="zhaoyun";
    winsize=Director::getInstance()->getWinSize();
    animate=false;
     Max_Hp=100;
     nowhp=100;
    
    
    //未写的
    atk=2;//攻击段数为3.
    Max_mp=20;
    nowmp=20;
    lv=1;  //等级
    Max_exe=50;//最大经验
    nowexe=0;//当前经验
    speed=5;//速度
    ui_name="赵云";
    ui_picture="赵云.png";
    ui_description="赵云，字子龙，常山真定（今河北省\n正定）人。身长八尺，姿颜雄\n伟，三国时期蜀汉名将。\n汉末军阀混战，赵云受本郡推举\n，率领义从加入白马将军公孙瓒。\n期间结识了汉室皇亲刘备，但不久\n之后，赵云因为兄长去世而离开。\n赵云离开公孙瓒大约七年左右的时间\n在邺城与刘备相见，从此追随刘备。";
    //未写的
    //Tag 3是粒子系统专用，勿用
    
    make_comb=false;
    this->initWithFile("zy.png",Rect(0,0,192/4,256/4));

    Sprite*maxhp=Sprite::create("max_hp.0.png");
    maxhp->setRotation(90);
    maxhp->setAnchorPoint(ccp(0.5,0));
    maxhp->setPosition(0,this->getContentSize().height);
    this->addChild(maxhp);
    
    
    Sprite*hp=Sprite::create("hp.png");
    hp->setPosition(0,this->getContentSize().height);
    hp->setRotation(90);
    hp->setAnchorPoint(ccp(0.5,0));
    this->addChild(hp,0,1);
    
    
    
    loading_animation();
    

  
    return true;
}

void zhaoyun::onEnter(){
    Sprite::onEnter();
      scheduleUpdate();
}

void zhaoyun::onExit(){
    Sprite::onExit();
    unscheduleUpdate();
}

void zhaoyun::loading_animation(){
    AnimationCache* ac=AnimationCache::getInstance();
    Animation*rundown=itool->makeAnimationfrommixpicture(last_name+".png",4,4,1,1,4,1,0.1f,true,-1);
    ac->addAnimation(rundown,name+"godown");
    Animation*goleft=itool->makeAnimationfrommixpicture(last_name+".png",4,4,1,2,4,2,0.1f,true,-1);
    ac->addAnimation(goleft,name+"goleft");
    Animation*goright=itool->makeAnimationfrommixpicture(last_name+".png",4,4,1,3,4,3,0.1f,true,-1);
    ac->addAnimation(goright,name+"goright");
    Animation*goup=itool->makeAnimationfrommixpicture(last_name+".png",4,4,1,4,4,4,0.1f,true,-1);
    ac->addAnimation(goup,name+"goup");
    
    Animation*attackdown=itool->makeAnimationfrommixpicture(last_name+"_melee.png",4,4,1,1,4,1,0.2f,true,1);
    ac->addAnimation(attackdown,name+"Adown");
    Animation*attackleft=itool->makeAnimationfrommixpicture(last_name+"_melee.png",4,4,1,2,4,2,0.2f,true,1);
    ac->addAnimation(attackleft,name+"Aleft");
    Animation*attackright=itool->makeAnimationfrommixpicture(last_name+"_melee.png",4,4,1,3,4,3,0.2f,true,1);
    ac->addAnimation(attackright,name+"Aright");
    Animation*attackup=itool->makeAnimationfrommixpicture(last_name+"_melee.png",4,4,1,4,4,4,0.2f,true,1);
    ac->addAnimation(attackup,name+"Aup");
}

void zhaoyun::walk(std::string godirection){
    AnimationCache* ac=AnimationCache::getInstance();
    Animation *a=ac->getAnimation(godirection);
    Animate* animate=Animate::create(a);
    this->runAction(animate);
}
void zhaoyun::attack(std::string Adirection){
    AnimationCache* ac=AnimationCache::getInstance();
    Animation *a=ac->getAnimation(Adirection);
    Animate* animate=Animate::create(a);
    this->runAction(animate);
}
void zhaoyun::update(float dt){
  
    
    Sprite*hpimage=(Sprite*)this->getChildByTag(1);
    
    float sca=nowhp/float(Max_Hp);

    hpimage->setScaleY(sca);

   int k=UI_Layer::type;
   
    
    if (k==0||yester_direction!=k) {
        animate=false;
        this->stopAllActions();
    }
    if (animate==false) {
        yester_direction=k;
    if (k==1) {
        direction=k;
        walk(name+"godown");
          animate=true;
    }
    else if (k==2) {
         direction=k;
          walk(name+"goleft");
          animate=true;
    }
    else if (k==3) {
         direction=k;
          walk(name+"goright");
        animate=true;
    }
    else if (k==4) {
          animate=true;
         direction=k;
        walk(name+"goup");
    }
    else if(k==5){
        scheduleOnce(schedule_selector(zhaoyun::attack_update),0);
        animate=true;
    }
    }
    //CCLOG("K:%d",k);
    move(k);
   
}

void zhaoyun::attack_update(float dt){
    switch (direction) {
        case 1:
            attack(name+"Adown");
            break;
        case 2:
            attack(name+"Aleft");
            break;
        case 3:
            attack(name+"Aright");
            break;
        case 4:
            attack(name+"Aup");
            break;
            
        default:
            break;
    }
}
void zhaoyun::move(int direction){
    map_layer*m=(map_layer*)this->getParent()->getChildByTag(2);
    Point p=this->getParent()->convertToWorldSpace(this->getPosition());
   // CCLOG("p.x:%f,p.y:%f",p.x,p.y);
  
   // CCLOG("direction:%d",direction);
    
    if (direction==1) {
        if (p.y<this->getContentSize().height/2||collision(ccp(this->getPosition().x,this->getPosition().y-speed))) {
            return;
        }
        this->setPositionY(this->getPositionY()-speed);
    }
    else if (direction==2) {
        if (p.x<this->getContentSize().width/2||collision(ccp(this->getPosition().x-speed,this->getPosition().y))) {
            return;
        }
        this->setPositionX(this->getPositionX()-speed);
        
    }
    else if (direction==3) {
        if (p.x>this->winsize.width-this->getContentSize().width/2||collision(ccp(this->getPosition().x+speed,this->getPosition().y))) {
            return;
        }
            this->setPositionX(this->getPositionX()+speed);
    }
    else if (direction==4) {
        if (p.y>this->winsize.height-this->getContentSize().height/2||collision(ccp(this->getPosition().x,this->getPosition().y+speed))) {
            return;
        }
      
        this->setPositionY(this->getPositionY()+speed);
        
    }
    
    
}

bool zhaoyun::collision(Vec2 temp){
    map_layer*m=(map_layer*)this->getParent()->getChildByTag(2);
   
   // CCLOG("temp.x-----%f,temp.y------%f",temp.x,temp.y);
  
    Vec2 t2=m->tileCoordFromPosition(temp);
  //  CCLOG("t2.x:--%f,t2.y:----%f",t2.x,t2.y);
    
  
    int tileGid=m->_collodable->getTileGIDAt(t2);
   // CCLOG("tileGid----%d",tileGid);
    if (tileGid>0) {
    //    CCLOG("in-----");
        Value prop=m->_tileMap->getPropertiesForGID(tileGid);
        //   CCLOG("out1");
        ValueMap propValueMap=prop.asValueMap();
        
       //  CCLOG("out2");
       std::string collision=propValueMap["collidable"].asString();
      //  CCLOG("out3");
        if (collision=="true") {
            return  true;   //碰撞成功
        }
    }
    return false;
}
void zhaoyun::level_up(){
    lv++;
    Max_Hp=100+20*(lv-1);
    nowhp=Max_Hp;
    atk+=0.6;
    Max_mp=20+5*(lv-1);
    nowmp=Max_mp;
    Max_exe=pow(lv,2)*50;//最大经验
    nowexe=0;//当前经验
    
}

