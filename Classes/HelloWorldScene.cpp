#include "HelloWorldScene.h"
#include "Begin_Layer.h"
#include "zhaoyun.h"
#include "huangzhong.h"
#include "UI_Layer.h"
#include "map_layer.h"
#include "soldier.h"
#include "Items.h"
#include "SimpleAudioEngine.h"
#include "Player.h"
using namespace CocosDenshion;

USING_NS_CC;
#include "Animation_itools.h"

//Scene* HelloWorld::createScene()
//{
//    // 'scene' is an autorelease object
//    auto scene = Scene::create();
//    
//    // 'layer' is an autorelease object
//    auto layer = HelloWorld::create();
//    
//    
//    UI_Layer*ul=UI_Layer::create();
//    
//
//    // add layer as a child to scene
//    scene->addChild(layer);
//    scene->addChild(ul,1);
//
//    // return the scene
//    return scene;
//}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    areadyatt=false;
    gameover=false;
     loding_animation();

//
    three_atk=false;
    bigboun=false;
    leishenchui=nullptr;
    udlr=0;
    
    
    
    
  
         Items*it4=Items::create("fly.png");
        it4->setPosition(200,500);
     it4->type=3;
     this->addChild(it4,2);
     vec_ite.pushBack(it4);
    
    
//    Items*it5=Items::create("fly.png");
//    it5->setPosition(200,800);
//    it5->type=3;
//    this->addChild(it5,2);
//    vec_ite.pushBack(it5);

    
    
    
    
    
    map_layer*map=map_layer::create();
    map->setPosition(0, 0);
   
    this->addChild(map,0,2);
    //获取地图大小，存在场景中
    tilemapsize=map->_tileMap->getContentSize();
    
   zy=(zhaoyun*)Player::getInstance()->vecofhero.at(0);
    zy->setPosition(300,300);
    this->addChild(zy,2,1);
    
    
    schedule(schedule_selector(HelloWorld::getItems),1/60);
    schedule(schedule_selector(HelloWorld::creat_sold),5);
    schedule(schedule_selector(HelloWorld::creat_gene),30);
    schedule(schedule_selector(HelloWorld::creat_Items),10);
    schedule(schedule_selector(HelloWorld::update_map),1/60);
    schedule(schedule_selector(HelloWorld::levelup_update),1/60);
    scheduleUpdate();
   
    
    return true;
}

void HelloWorld::levelup_update(float dt){
    if (zy->nowexe>=zy->Max_exe) {
        zy->level_up();
        auto galaxy=ParticleFireworks::create();
        galaxy->setDuration(2);
        galaxy->setPosition(32,32);
        galaxy->setScale(0.5);
        zy->addChild(galaxy,3);
    }
}


void HelloWorld::creat_sold(float dt){
    Size winsize=Director::getInstance()->getWinSize();
    int t=arc4random()%3;
    int d=arc4random()%4;
    soldier*s1;
    switch (t) {
        case 0:
            s1=soldier::create("s",arc4random()%10+10,2);
            s1->exp=3;
            break;
        case 1:
            s1=soldier::create("qs",arc4random()%5+15,3);
            s1->exp=4;
            break;
        case 2:
            s1=soldier::create("mood",arc4random()%10+20,4);
            s1->exp=5;
            break;
        default:
            break;
    }
    switch (d) {
        case 0:
            s1->setPosition(-arc4random()%100-50,arc4random()%2000-1000);
            break;
        case 1:
            s1->setPosition(arc4random()%2000-1000,-arc4random()%100-50);
            break;
        case 2:
          s1->setPosition(winsize.width+arc4random()%100,arc4random()%2000-1000);
            break;
        case 3:
        s1->setPosition(arc4random()%2000-1000,winsize.height+arc4random()%100);
            break;
        default:
            break;
    }
    vecs.pushBack(s1);
    this->addChild(s1,2);
}
void HelloWorld::creat_gene(float dt){
    Size winsize=Director::getInstance()->getWinSize();
    int t=arc4random()%2;
    int d=arc4random()%4;
    soldier*s1;
    switch (t) {
        case 0:
            s1=soldier::create("xh",40,20);
            s1->exp=12;
             s1->speed=2.5;
            break;
        case 1:
            s1=soldier::create("xhd",50,18);
            s1->exp=14;
            s1->speed=3;
            break;
               default:
            break;
    }
    switch (d) {
        case 0:
            s1->setPosition(-arc4random()%100-50,arc4random()%2000-1000);
            break;
        case 1:
            s1->setPosition(arc4random()%2000-1000,-arc4random()%100-50);
            break;
        case 2:
            s1->setPosition(winsize.width+arc4random()%100,arc4random()%2000-1000);
            break;
        case 3:
            s1->setPosition(arc4random()%2000-1000,winsize.height+arc4random()%100);
            break;
        default:
            break;
    }
    vecs.pushBack(s1);
    this->addChild(s1,2);

}
void HelloWorld::creat_Items(float dt){
    int t=arc4random()%4;
    Items*it;
    if (t==0) {
        it=Items::create("addhp.png");
        it->setRotation(-90);
        it->type=0;
    }
    else if (t==1) {
        it=Items::create("addatk.png");
        it->type=1;
    }
    else if (t==2) {
        it=Items::create("strong.png");
        it->type=2;
    }
    else if (t==3) {
        it=Items::create("fly.png");
        it->type=3;
    }
    vec_ite.pushBack(it);
    Point pp=Vec2(-tilemapsize.width/2+arc4random()%(int)(tilemapsize.width),-tilemapsize.height/2+arc4random()%(int)(tilemapsize.height));
   // CCLOG("create_it");
    it->setPosition(pp);
     this->addChild(it);
    //该点在不可到的位置上，重置位置。
 

    while (it->collision(pp)) {
       pp=Vec2(-tilemapsize.width/2+arc4random()%(int)(tilemapsize.width),-tilemapsize.height/2+arc4random()%(int)(tilemapsize.height));
        it->setPosition(pp);
    }

}

void HelloWorld::update(float dt)//主要处理主角攻击敌人
{
   // zhaoyun*zy=(zhaoyun*)this->getChildByTag(1);
    if (zy->nowhp<=0) {
        gameover=true;
       // gameover();
    }
    
    
    int k=UI_Layer::type;
    //CCLOG("k----%d",k);
    if (k==0) {
        areadyatt=false;
    }
    if (areadyatt) {
        return;
    }
    
    for (auto i:vecs) {
    if (i->hp<=0) {
        zy->nowexe+=i->exp;
        i->stopAllActions();
        i->runactiondead(i->direction);
        vecs.eraseObject(i);
        //另一方案
        //i->runAction(Sequence::create(DelayTime::create(2),FadeOut::create(1.0f),NULL));
        //vecforremove.pushBack(i);
        //scheduleOnce(schedule_selector(HelloWorld::removecallback),3.0f);
       //方案一
        i->runAction(Sequence::create(DelayTime::create(2),CallFuncN::create(
                                                                             //方案2，lambda表达式
                                                                            // [=](){
                                                                              //   i->removeFromParent();
                                                                             //}),NULL));
                                                                             
                                                                             CC_CALLBACK_1(HelloWorld::test,this)), NULL));
       
        
    }
        
    }
    if (k==5) {
        if (bigboun) {
            leishenchui=Sprite::create("fly.png");
            leishenchui->setPosition(zy->getPosition());
            this->addChild(leishenchui);
            
            auto Meteor=ParticleMeteor::create();
            Meteor->setPosition(0,0);
            Meteor->setScale(0.3);
            leishenchui->addChild(Meteor,3);
            
           //  zhaoyun*zy=(zhaoyun*)this->getChildByTag(1);
              udlr=zy->direction;
                       schedule(schedule_selector(HelloWorld::leishenchuiaction),1/60);
            bigboun=false;
            
        }
        
        areadyatt=true;
        for (auto i:vecs) {
            if (zy->boundingBox().intersectsRect(i->boundingBox())) {
                beatt=i;
                schedule(schedule_selector(HelloWorld::akkack),0.15,3, 0.35);
            }
        }
    }
    
}

void HelloWorld::update_map(float dt)
{
        int k=UI_Layer::type;
        //zhaoyun*zy=(zhaoyun*)this->getChildByTag(1);
       map_layer* map=(map_layer*)this->getChildByTag(2);
        Size winsize=Director::getInstance()->getWinSize();
     Vec2 temp=this->convertToWorldSpace(zy->getPosition());
    
    float spd=zy->speed;
                switch (k) {
                case 1:
                {
                    if (temp.y<winsize.height/4&&zy->getPositionY()>-map->size_height/2+winsize.height/4) {
                           this->setPositionY(this->getPositionY()+spd);
                    }
                }
                    break;
                case 2:
                {
                    if (temp.x<winsize.width/4&&zy->getPositionX()>-map->size_width/2+winsize.width/4) {
                    this->setPositionX(this->getPositionX()+spd);
                    }
                }
                    break;
                case 3:
                {
                    if (temp.x>winsize.width*3/4&&zy->getPositionX()<map->size_width/2-winsize.width/4){
                        this->setPositionX(this->getPositionX()-spd);
                      }
                }
                    break;
                case 4:
                {
                    if (temp.y>winsize.height*3/4&&zy->getPositionY()<map->size_height/2-winsize.height/4){
                    this->setPositionY(this->getPositionY()-spd);
                    }
                }
                    break;
                default:
                    break;
            }
    

}

void HelloWorld::leishenchuiaction(float dt)
{
   // zhaoyun*zy=(zhaoyun*)this->getChildByTag(1);
    if (leishenchui) {
        if (udlr==1) {
               leishenchui->setPositionY(leishenchui->getPositionY()-10);
        }
        else if (udlr==2) {
            leishenchui->setPositionX(leishenchui->getPositionX()-10);
        }
        else if (udlr==3) {
            leishenchui->setPositionX(leishenchui->getPositionX()+10);
        }
        else if (udlr==4) {
            leishenchui->setPositionY(leishenchui->getPositionY()+10);
        }
        leishenchui->setRotation(leishenchui->getRotation()+30);
        
        for (auto i:vecs){
            if (i->boundingBox().intersectsRect(leishenchui->boundingBox())) {
               // this->removeChild(i);
                i->hp=0;
               // vecforremove.pushBack(i);
            }
        }
        Vec2 lscwrdposition=this->convertToWorldSpace(leishenchui->getPosition());
        if (lscwrdposition.x<-20||lscwrdposition.x>1000||lscwrdposition.y<-20||lscwrdposition.y>700) {
            udlr=0;
            this->removeChild(leishenchui);
            leishenchui=nullptr;
        }
    }
}
void HelloWorld::getItems(float dt){
    if (bigboun==false&&zy->getChildByTag(3)) {
        zy->removeChildByTag(3);
    }
    for (auto i:vec_ite) {
        if (zy->boundingBox().containsPoint(i->getPosition())) {
            if (i->type==0) {
                auto flower=ParticleFlower::create();
                flower->setDuration(1);
                flower->setScale(0.5);
                flower->setPosition(32,32);
                zy->addChild(flower,3);
                vec_ite.eraseObject(i);
                this->removeChild(i);
                zy->nowhp+=(5+arc4random()%15);
            }
            else if (i->type==1) {
                auto fire=ParticleFire::create();
                fire->setDuration(10);
                fire->setScale(0.5);
                fire->setPosition(32,32);
                zy->addChild(fire,3);
                vec_ite.eraseObject(i);
                this->removeChild(i);
                zy->atk=zy->atk*3;
                three_atk=true;
                scheduleOnce(schedule_selector(HelloWorld::come_back_atk), 10);
            }
            else if (i->type==2) {
                auto galaxy=ParticleGalaxy::create();
                galaxy->setDuration(10);
                  galaxy->setPosition(32,32);
                galaxy->setScale(0.5);
                zy->addChild(galaxy,3);
                vec_ite.eraseObject(i);
                galaxy->runAction(Blink::create(10,10));
                this->removeChild(i);
                zy->strong=true;
                scheduleOnce(schedule_selector(HelloWorld::come_back_normal), 10);
            }
           else if (i->type==3) {
               auto Meteor=ParticleMeteor::create();
               Meteor->setScale(0.5);
               Meteor->setPosition(0,0);
               zy->addChild(Meteor,3,3);
               vec_ite.eraseObject(i);
                this->removeChild(i);
               bigboun=true;
            }
          
        }
    }
}

void HelloWorld::come_back_atk(float dt)//恢复攻击
{
    if (three_atk) {
        zy->atk=zy->atk/3;
        three_atk=false;
    }

}
    void HelloWorld::come_back_normal(float dt)//解除无敌
{
    //zhaoyun*zy=(zhaoyun*)this->getChildByTag(1);
    zy->strong=false;
}
void HelloWorld::will_changehero(){
    if (three_atk) {
         zy->atk=zy->atk/3;
        three_atk=false;
    }
    zy->strong=false;
}

void HelloWorld::akkack(float dt)//主角多段伤害
{
  
   // zhaoyun*zy=(zhaoyun*)this->getChildByTag(1);
    if (zy->boundingBox().intersectsRect(beatt->boundingBox())) {
        beatt->hp=beatt->hp-zy->atk;
    }
}
void HelloWorld::loding_animation(){

    loding_moveByname("s");
    loding_attackByname("s_melee");
    loding_deadByname("s_dead");
    loding_attackByname("qs_melee");
    loding_moveByname("qs");
    loding_deadByname("qs_dead");
    loding_moveByname("mood");
    loding_attackByname("mood_melee");
    loding_deadByname("mood_dead");
    loding_moveByname("xhd");
    loding_attackByname("xhd_melee");
    loding_deadByname("xhd_dead");
    loding_moveByname("xh");
    loding_attackByname("xh_melee");
    loding_deadByname("xh_dead");
    

}
void HelloWorld::loding_moveByname(std::string name){
    AnimationCache* ac=AnimationCache::getInstance();
    std::string pic_name;
    pic_name=name+".png";
   
    Animation*down=itool->makeAnimationfrommixpicture(pic_name,4,4,1,1,4,1,0.2f,true,-1);
    ac->addAnimation(down,name+"down");
    Animation*left=itool->makeAnimationfrommixpicture(pic_name,4,4,1,2,4,2,0.2f,true,-1);
    ac->addAnimation(left,name+"left");
    Animation*right=itool->makeAnimationfrommixpicture(pic_name,4,4,1,3,4,3,0.2f,true,-1);
    ac->addAnimation(right,name+"right");
    Animation*up=itool->makeAnimationfrommixpicture(pic_name,4,4,1,4,4,4,0.2f,true,-1);
    ac->addAnimation(up,name+"up");
   
   }

void HelloWorld::loding_attackByname(std::string name){
    AnimationCache* ac=AnimationCache::getInstance();
    std::string pic_name;
    pic_name=name+".png";
    Animation*down=itool->makeAnimationfrommixpicture(pic_name,4,4,1,1,4,1,0.25f,true,1);
    ac->addAnimation(down,name+"down");
    Animation*left=itool->makeAnimationfrommixpicture(pic_name,4,4,1,2,4,2,0.25f,true,1);
    ac->addAnimation(left,name+"left");
    Animation*right=itool->makeAnimationfrommixpicture(pic_name,4,4,1,3,4,3,0.25f,true,1);
    ac->addAnimation(right,name+"right");
    Animation*up=itool->makeAnimationfrommixpicture(pic_name,4,4,1,4,4,4,0.25f,true,1);
    ac->addAnimation(up,name+"up");

}
void HelloWorld::loding_deadByname(std::string name){
    AnimationCache* ac=AnimationCache::getInstance();
    std::string pic_name;
    pic_name=name+".png";
    Animation*down=itool->makeAnimationfrommixpicture(pic_name,4,4,1,1,4,1,0.25f,false,2);
    ac->addAnimation(down,name+"down");
    Animation*left=itool->makeAnimationfrommixpicture(pic_name,4,4,1,2,4,2,0.25f,false,2);
    ac->addAnimation(left,name+"left");
    Animation*right=itool->makeAnimationfrommixpicture(pic_name,4,4,1,3,4,3,0.25f,false,2);
    ac->addAnimation(right,name+"right");
    Animation*up=itool->makeAnimationfrommixpicture(pic_name,4,4,1,4,4,4,0.25f,false,2);
    ac->addAnimation(up,name+"up");

}




                     void HelloWorld::test(Ref*p){
                         soldier*sp=static_cast<soldier*>(p);
                         this->removeChild(sp);
                         
                     }

