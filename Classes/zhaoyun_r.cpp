//
//  zhaoyun_r.cpp
//  animate_homework
//
//  Created by mac on 15-7-31.
//
//

#include "zhaoyun_r.h"
#include "Animation_itools.h"
#include "UIr_Layer.h"
#include "map_layer.h"
using namespace::cocos2d;
bool zhaoyun_r::init(){
    if (!Sprite::init()) {
        return false;
    }
    winsize=Director::getInstance()->getWinSize();
    animate=false;
   
    this->initWithFile("zy_r.png",Rect(0,0,240/4,432/4));
    speed=2;
    big_map=false;
    loading_animation();
    
    scheduleUpdate();
    
    return true;

    
    
}
void zhaoyun_r::loading_animation(){
    AnimationCache* ac=AnimationCache::getInstance();
    Animation*rundown=itool->makeAnimationfrommixpicture("zy_r.png",4,4,1,1,4,1,0.1f,true,-1);
    ac->addAnimation(rundown,"go_down");
    Animation*goleft=itool->makeAnimationfrommixpicture("zy_r.png",4,4,1,2,4,2,0.1f,true,-1);
    ac->addAnimation(goleft,"go_left");
    Animation*goright=itool->makeAnimationfrommixpicture("zy_r.png",4,4,1,3,4,3,0.1f,true,-1);
    ac->addAnimation(goright,"go_right");
    Animation*goup=itool->makeAnimationfrommixpicture("zy_r.png",4,4,1,4,4,4,0.1f,true,-1);
    ac->addAnimation(goup,"go_up");
    
    Animation*runxdown=itool->makeAnimationfrommixpicture("zy_xr.png",4,4,1,1,4,1,0.1f,true,-1);
    ac->addAnimation(runxdown,"left_down");
    Animation*goxleft=itool->makeAnimationfrommixpicture("zy_xr.png",4,4,1,2,4,2,0.1f,true,-1);
    ac->addAnimation(goxleft,"left_up");
    Animation*goxright=itool->makeAnimationfrommixpicture("zy_xr.png",4,4,1,3,4,3,0.1f,true,-1);
    ac->addAnimation(goxright,"right_down");
    Animation*goxup=itool->makeAnimationfrommixpicture("zy_xr.png",4,4,1,4,4,4,0.1f,true,-1);
    ac->addAnimation(goxup,"right_up");

   
}
void zhaoyun_r::walk(std::string godirection){
  
        AnimationCache* ac=AnimationCache::getInstance();
        Animation *a=ac->getAnimation(godirection);
        Animate* animate=Animate::create(a);
        this->runAction(animate);
    

}
void zhaoyun_r::update(float dt){
    
    
    Sprite*hpimage=(Sprite*)this->getChildByTag(1);

    
    int k=UIr_Layer::type;
    
    
    if (k==0||yester_direction!=k) {
        animate=false;
        this->stopAllActions();
    }
    if (animate==false) {
        yester_direction=k;
        if (k==1) {
            direction=k;
            walk("go_right");
            animate=true;
        }
        else if (k==2) {
            direction=k;
            walk("right_up");
            animate=true;
        }
        else if (k==3) {
            direction=k;
            walk("go_up");
            animate=true;
        }
        else if (k==4) {
            animate=true;
            direction=k;
            walk("left_up");
        }
        else if (k==5) {
            animate=true;
            direction=k;
            walk("go_left");
        }
        else if (k==6) {
            animate=true;
            direction=k;
            walk("left_down");
        }

        else if (k==7) {
            animate=true;
            direction=k;
            walk("go_down");
        }

        else if (k==8) {
            animate=true;
            direction=k;
            walk("right_down");
        }


    }
    if (big_map) {
           move(k);
    }
    else{
        xiaotitu_move(k);
    }
    

}
void zhaoyun_r::xiaotitu_move(int direction){
    
    if (direction==1) {
        if (this->getPositionX()>940)
            return;
        this->setPositionX(this->getPositionX()+speed);
    }
    else if (direction==2) {
        if (this->getPositionX()>940||this->getPositionY()>620)
            return;
        this->setPosition(this->getPosition()+Vec2(speed/sqrt(2),speed/sqrt(2)));
    }
    else if (direction==3) {
        if (this->getPositionY()>620)
            return;
        this->setPositionY(this->getPositionY()+speed);
    }
    else if (direction==4) {
        if (this->getPositionY()>620||this->getPositionX()<20)
            return;
        this->setPosition(this->getPosition()+Vec2(-speed/sqrt(2),speed/sqrt(2)));
    }
    else if (direction==5) {
        if (this->getPositionX()<20)
            return;
        this->setPositionX(this->getPositionX()-speed);
    }
    else if (direction==6) {
        if (this->getPositionX()<20||this->getPositionY()<20)
            return;
        this->setPosition(this->getPosition()+Vec2(-speed/sqrt(2),-speed/sqrt(2)));
    }
    else if (direction==7) {
        if (this->getPositionY()<20)
            return;
        this->setPositionY(this->getPositionY()-speed);
    }
    else if (direction==8) {
        if (this->getPositionY()<20||this->getPositionX()>940) 
            return;
        
        this->setPosition(this->getPosition()+Vec2(speed/sqrt(2),-speed/sqrt(2)));
    }
}

void zhaoyun_r::move(int direction){
   Vec2 p=this->getParent()->convertToWorldSpace(this->getPosition());
    float sqspeed=speed/sqrt(2);
    
    if (direction==1) {
        if (p.x>940||collision(Vec2(this->getPositionX()+speed,this->getPositionY())))
            return;
        this->setPositionX(this->getPositionX()+speed);
    }
    else if (direction==2) {
        if (p.x>940||p.y>620||collision(this->getPosition()+Vec2(sqspeed,sqspeed)))
            return;
        this->setPosition(this->getPosition()+Vec2(sqspeed,sqspeed));
    }
    else if (direction==3) {
        if (p.y>620||collision(Vec2(this->getPositionX(),this->getPositionY()+speed)))
            return;
        this->setPositionY(this->getPositionY()+speed);
    }
    else if (direction==4) {
        if (p.y>620||p.x<20||collision(this->getPosition()+Vec2(-sqspeed,sqspeed)))
            return;
        this->setPosition(this->getPosition()+Vec2(-sqspeed,sqspeed));
    }
    else if (direction==5) {
        if (p.x<20||collision(Vec2(this->getPositionX()-speed,this->getPositionY())))
            return;
        this->setPositionX(this->getPositionX()-speed);
    }
    else if (direction==6) {
        if (p.x<20||p.y<20||collision(this->getPosition()+Vec2(-sqspeed,-sqspeed)))
            return;
        this->setPosition(this->getPosition()+Vec2(-sqspeed,-sqspeed));
    }
    else if (direction==7) {
        if (p.y<20||collision(Vec2(this->getPositionX(),this->getPositionY()-speed)))
            return;
        this->setPositionY(this->getPositionY()-speed);
    }
    else if (direction==8) {
        if (p.y<20||p.x>940||collision(this->getPosition()+Vec2(sqspeed,-sqspeed)))
            return;
        this->setPosition(this->getPosition()+Vec2(sqspeed,-sqspeed));
    }
   
}


void zhaoyun_r::set_speed(float sp){
    this->speed=sp;
}
float zhaoyun_r::get_speed(){
    return this->speed;
}

bool zhaoyun_r::collision(Vec2 temp){
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

