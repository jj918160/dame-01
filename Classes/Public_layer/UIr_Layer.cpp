//
//  UIr_Layer.cpp
//  animate_homework
//
//  Created by mac on 15-7-31.
//
//

#include "UIr_Layer.h"
#include "zhaoyun_r.h"
#include "State_Layer.h"
#include "Bag_layer.h"
#define PI 3.1415926
USING_NS_CC;
int UIr_Layer::type=0;

bool UIr_Layer::init(){
    if (!Layer::init()) {
        return false;
    }
   
    bag_open=false;
    rokerPosition=Vec2(150,150);
    workespaceopen=true;
    CCSprite *spRockerBG=CCSprite::create("CG-1086.png");
    spRockerBG->setPosition(rokerPosition);
    spRockerBG->setOpacity(50);
    addChild(spRockerBG,1);
    rockerBGR=spRockerBG->getContentSize().width*0.5;
    
    auto spRockerF = Sprite::create("CG-7005.png");
    spRockerF->setPosition(rokerPosition);
    addChild(spRockerF, 2,1);
    
    auto work = Sprite::create("work.png");
    work->setPosition(160,470);
    addChild(work,2,8);
    
    auto labelttf=Label::createWithSystemFont("任务：", "Arial", 16);
    labelttf->setAnchorPoint(Vec2(0,1));
    labelttf->setPosition(40,200);
    labelttf->setColor(ccc3(255, 0, 0));
    labelttf->setString("任务：从左下角离开去找刘备");
    work->addChild(labelttf,2,8);
    
    
    
 
    auto tol=MenuItemToggle::createWithCallback(CC_CALLBACK_1(UIr_Layer::callback1,this),
                                                MenuItemImage::create("close1.png", "close1.png"),
                                                MenuItemImage::create("open1.png", "open1.png"),
                                               
                                                NULL);
    tol->setPosition(24,613);
    //this->addChild(tol,2);
    
    auto item=MenuItemImage::create("CG-6997.png", "CG-6998.png", CC_CALLBACK_1(UIr_Layer::callback2,this));
    item->setPosition(500,600);
    
    //test_began
    auto item2=MenuItemImage::create("CG-1487.png", "CG-1486.png", CC_CALLBACK_1(UIr_Layer::callback3,this));
    item2->setPosition(600,600);
    
    //test_end
    auto menu=Menu::create(tol,item,item2,NULL);
    menu->setPosition(0,0);
    this->addChild(menu);
    
    
    auto attlistener=EventListenerTouchOneByOne::create();
    attlistener->onTouchBegan=[=](Touch*touch,Event*event){
        auto target=static_cast<Sprite*>(event->getCurrentTarget());
        Vec2 locationInNode=target->convertToNodeSpace(touch->getLocation());
        Size s=target->getContentSize();//点到判断碰撞
        Rect rect=Rect(0,0,s.width,s.height);
        if (rect.containsPoint(locationInNode)) {
            return  true;
        }
        return false;

           };
    
    attlistener->onTouchMoved=[&](Touch*touch,Event*event){
        Vec2 point=touch->getLocation();
        
        auto target=static_cast<Sprite*>(event->getCurrentTarget());
        if (sqrt(pow((rokerPosition.x-point.x),2)+pow((rokerPosition.y-point.y),2))>=rockerBGR){
           
            float angle=getRad(point);
            target->setPosition(ccpAdd(getAnglePosition(rockerBGR, angle),rokerPosition));
        }else{
            target->setPosition(target->getPosition()+touch->getDelta());
        }
       
        
         float angle=getRad(point);
        //CCLOG("hudu:%f",angle);
        if (angle<=PI/8&&angle>-PI/8) {
            type=1;
        }
        else if (angle>PI/8&&angle<=PI*3/8) {
            type=2;
        }
        else if (angle>PI*3/8&&angle<=PI*5/8) {
            type=3;
        }
        else if (angle>PI*5/8&&angle<=PI*7/8) {
            type=4;
        }
        else if (angle>PI*7/8||angle<=-PI*7/8) {
            type=5;
        }
        else if (angle>-PI*7/8&&angle<=-PI*5/8) {
            type=6;
        }
        else if (angle>-PI*5/8&&angle<=-PI*3/8) {
            type=7;
        }
        else if (angle>-PI*3/8&&angle<=-PI*1/8) {
            type=8;
        }
       // CCLOG("type:%d",type);
        

    };

    
    attlistener->onTouchEnded=[&](Touch*touch,Event*event){
        Sprite *spRockerF=(Sprite*)this->getChildByTag(1);
        spRockerF->runAction(CCMoveTo::create(0.05, rokerPosition));
            type=0;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(attlistener,spRockerF);
    
    
    
    return true;
}


float UIr_Layer::getRad(Vec2 pos1){
    float px1=pos1.x;
    float py1=pos1.y;
    float x=px1-rokerPosition.x;
    float y=py1-rokerPosition.y;
    float xie=sqrt(pow(x,2)+pow(y,2));
    float cosAngle=x/xie;
    float rad=acos(cosAngle);
    if (py1<rokerPosition.y) {
        rad=-rad;
    }
    
    return rad;
}



Vec2 UIr_Layer::getAnglePosition(float r,float angle){
    return ccp(r*cos(angle),r*sin(angle));
}
void UIr_Layer::callback1(Ref* psender){
    Sprite*sp=static_cast<Sprite*>(this->getChildByTag(8));
    if (workespaceopen) {
        sp->runAction(FadeOut::create(0.5));
        sp->getChildByTag(8)->runAction(FadeOut::create(0.5));
        workespaceopen=false;
        
    }
    else if (!workespaceopen) {
        sp->runAction(FadeIn::create(0.5));
         sp->getChildByTag(8)->runAction(FadeIn::create(0.5));
        workespaceopen=true;
        
    }

    
    
}
void UIr_Layer::callback2(Ref* psender){
    
    Director::getInstance()->pushScene(State_Layer::createScene());
    
}
void UIr_Layer::set_workstring(const char *string){
    Label*sp=(Label*)this->getChildByTag(8)->getChildByTag(8);
    sp->setString(string);
}


void UIr_Layer::callback3(Ref* psender){
    
    if (bag_open) {
        this->removeChildByTag(100);
        bag_open=false;
    }
    else if (!bag_open) {
        Bag_layer*bg=Bag_layer::create();
        bg->setPosition(Vec2(0,0));
        this->addChild(bg,5,100);
        bag_open=true;
    }

    
}
