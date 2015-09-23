//
//  soldier.cpp
//  animate_homework
//
//  Created by mac on 15-7-18.
//
//
#include "Player.h"
#include "map_layer.h"
#include "soldier.h"
#include "zhaoyun.h"
#include "HelloWorldScene.h"
USING_NS_CC;
bool soldier::init(std::string pic_name,int hp,int a,float spd){
    if (!Sprite::init()) {
        return false;
    }
    this->name=pic_name;
    this->max_hp=hp;
    this->hp=hp;
    this->atk=a;
    direction="up";
    move=false;
    speed=spd;
    
    this->initWithFile(pic_name+".png",Rect(0,0,192/4,256/4));
    Sprite*maxhp=Sprite::create("max_hp.0.png");
    maxhp->setRotation(90);
    maxhp->setAnchorPoint(ccp(0.5,0));
    maxhp->setPosition(0,this->getContentSize().height);
    this->addChild(maxhp);
    
    Sprite*hpn=Sprite::create("hp.png");
    hpn->setPosition(0,this->getContentSize().height);
    hpn->setRotation(90);
    hpn->setAnchorPoint(ccp(0.5,0));
    this->addChild(hpn,0,1);

    
    A_ttack=false;
    scheduleUpdate();
    
    return true;
}

void soldier::walk(std::string direction){
    AnimationCache* ac=AnimationCache::getInstance();
    Animation *a=ac->getAnimation(name+direction);
    Animate* animate=Animate::create(a);
    this->runAction(animate);
}
void soldier::attack(std::string direction){
    AnimationCache* ac=AnimationCache::getInstance();
    Animation *a=ac->getAnimation(name+"_melee"+direction);
    Animate* animate=Animate::create(a);
    this->runAction(animate);
}
void soldier::runactiondead(std::string direction){
    AnimationCache* ac=AnimationCache::getInstance();
    Animation *a=ac->getAnimation(name+"_dead"+direction);
    Animate* animate=Animate::create(a);
    this->runAction(animate);
}
void soldier::update(float dt){
   
    
    Sprite*hpimage=(Sprite*)this->getChildByTag(1);
    
    float sca=hp/float(max_hp);
    if (hp>0) {
        hpimage->setScaleY(sca);
    }
    else{
        hpimage->setScaleY(0);
    }
    
    if (this->hp<=0)
        return;
    

//    CCLOG("hp---%d",hp);
    
    
       zhaoyun*zy=(zhaoyun*)this->getParent()->getChildByTag(1);
      map_layer*m=(map_layer*)this->getParent()->getChildByTag(2);

    
    Point des=zy->getPosition();
   // CCLOG("des.x----%f,des.y-----%f",des.x,des.y);

    if (this->boundingBox().containsPoint(des)) {
       

        
        move=false;
        //这个if保证动画只执行一次
        if (A_ttack==false) {
            this->stopAllActions();
           // CCLOG("inonce");
            scheduleOnce(schedule_selector(soldier::attack_hero),1.0f);
            attack(direction);
            A_ttack=true;
            return;
        }
    }
    else{
        //保证动画只执行一次
        if (A_ttack&&move==false) {
            stopAllActions();
            walk(direction);
            A_ttack=false;
            move=true;
            
        }
        //移动动画逻辑
     
        //转向动画的切换
        if(oldirection!=direction){
            oldirection=direction;
    if (des.x>this->getPositionX()+10) {
        stopAllActions();
        walk(direction);
        
    }
    else if(des.x<this->getPositionX()-10){
        
        stopAllActions();
         walk(direction);
        
    }
    else if(des.y>this->getPositionY()){
        
         stopAllActions();
         walk(direction);
        
    }
    else if(des.y<this->getPositionY()){
      
         stopAllActions();
         walk(direction);
    }
        }
        
        
        
        
        
        //坐标移动逻辑
        if (des.x>this->getPositionX()+10) {
               direction="right";
            this->setPositionX(this->getPositionX()+speed);
        }
        else if(des.x<this->getPositionX()-10){
               direction="left";
            this->setPositionX(this->getPositionX()-speed);
            
        }
        else if(des.y>this->getPositionY()){
             direction="up";
            this->setPositionY(this->getPositionY()+speed);
            
        }
        else if(des.y<this->getPositionY()){
              direction="down";
            this->setPositionY(this->getPositionY()-speed);
        }
      
        
    }

}

void soldier::attack_hero(float dt){
    if (this->hp) {
        HelloWorld*game=(HelloWorld*)this->getParent();
       // CCLOG("name:%s",game->zy->name.c_str());
        if (game->zy->strong==false&&this->boundingBox().containsPoint(game->zy->getPosition())) {
             game->zy->nowhp=game->zy->nowhp-this->atk;
        }
//        CCLOG("name2:%s",game->zy->name.c_str());
//        CCLOG("hp:%d",game->zy->nowhp);
//        Player*p=Player::getInstance();
//        CCLOG("size:%d",p->vecofhero.size());
//        zhaoyun*hero=(zhaoyun*)p->vecofhero.at(p->hero_now-1);
//        CCLOG("hp2:%d",hero->nowhp);
       
       
    A_ttack=false;
    }

}
