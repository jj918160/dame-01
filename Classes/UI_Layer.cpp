//
//  UI_Layer.cpp
//  animate_homework
//
//  Created by mac on 15-7-16.
//
//

#include "UI_Layer.h"
#include "zhaoyun.h"
#include "huangzhong.h"
#include "State_Layer.h"
#include "Player.h"
#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio::timeline;
int UI_Layer::type=0;
bool UI_Layer::init(){
    if (!Layer::init()) {
        return false;
    }
    herostateopen=true;
    rokerPosition=Vec2(200,200);
    
    CCSprite *spRockerBG=CCSprite::create("CG-1086.png");
    spRockerBG->setPosition(rokerPosition);
    spRockerBG->setOpacity(50);
    addChild(spRockerBG,1);
    
    rockerBGR=spRockerBG->getContentSize().width*0.5;
    
    
    auto rootNode = CSLoader::createNode("UI_Hero_State.csb");
    addChild(rootNode,2,20);
    
    ListView*lview=(ListView*)rootNode->getChildByTag(55);
  //  ImageView* Imagetemp=(ImageView*)lview->getChildByTag(64);
    lview->setItemsMargin(20.f);


//    lview->addEventListener([=](Ref*pSender,ListView::EventType type){
//        switch (type) {
//                CCLOG("EVENT");
//            case ListView::EventType::ON_SELECTED_ITEM_START:
//            {
//                ListView*listView=static_cast<ListView*>(pSender);
//                int k=listView->getCurSelectedIndex();
//                CCLOG("shuzi:%d",k);
//                break;
//            }
//            case ListView::EventType::ON_SELECTED_ITEM_END:
//            {
//                ListView*listView=static_cast<ListView*>(pSender);
//                int k=listView->getCurSelectedIndex();
//                CCLOG("shuzi:%d",k);
//            }
//                
//            default:
//                break;
//        }
//    });
 
  
    
    
    auto spRockerF = Sprite::create("CG-7005.png");
    spRockerF->setPosition(rokerPosition);
    addChild(spRockerF, 2,1);
    
    
    Sprite*sp5=Sprite::create("2824.1.png");
    sp5->setPosition(760,200);
    this->addChild(sp5,1,2);
    
    
    auto work = Sprite::create("work.png");
    work->setPosition(160,470);
    addChild(work,2,8);
    
    auto labelttf=Label::createWithSystemFont("任务：", "Arial", 16);
    labelttf->setAnchorPoint(Vec2(0,1));
    labelttf->setPosition(40,200);
    labelttf->setColor(ccc3(255, 0, 0));
    labelttf->setString("任务：杀敌100！");
    work->addChild(labelttf,2,8);
    
    
    
    
    auto tol=MenuItemToggle::createWithCallback(CC_CALLBACK_1(UI_Layer::callback1,this),
                                                MenuItemImage::create("close1.png", "close1.png"),
                                                MenuItemImage::create("open1.png", "open1.png"),
                                                
                                                NULL);
    tol->setPosition(24,613);
   
    auto item=MenuItemImage::create("CG-6997.png", "CG-6998.png", CC_CALLBACK_1(UI_Layer::callback2,this));
    item->setPosition(500,600);
 
    auto item2=MenuItemImage::create("CG-7001.png", "CG-7000.png", CC_CALLBACK_1(UI_Layer::callback3,this));
    item2->setPosition(700,600);
   
    auto item3=MenuItemImage::create("76-5.png", "76-9.png", CC_CALLBACK_1(UI_Layer::callback4,this));
    item3->setPosition(930,360);
    
    
    auto menu=Menu::create(tol,item,item2,item3,NULL);
    menu->setPosition(0,0);
    this->addChild(menu);

    
    
    auto touchEvt=EventListenerTouchOneByOne::create();
    touchEvt->onTouchBegan=CC_CALLBACK_2(UI_Layer::onTouchBegan,this);
    touchEvt->onTouchMoved=CC_CALLBACK_2(UI_Layer::onTouchMoved,this);

    
    
    touchEvt->onTouchEnded=CC_CALLBACK_2(UI_Layer::onTouchEnded,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEvt,spRockerF);
    
    
    
     auto attlistener=EventListenerTouchOneByOne::create();
    attlistener->onTouchBegan=[=](Touch*touch,Event*event){
        auto target=static_cast<Sprite*>(event->getCurrentTarget());
        Vec2 locationInNode=target->convertToNodeSpace(touch->getLocation());
        
        
        Size s=target->getContentSize();//点到判断碰撞
        Rect rect=Rect(0,0,s.width,s.height);
        if (rect.containsPoint(locationInNode)) {
            type=5;
            target->runAction(ScaleTo::create(0,0.8));
           scheduleOnce(schedule_selector(UI_Layer::attori),0.9);
            return  true;
        }
        return false;

    };
    attlistener->onTouchEnded=[](Touch*touch,Event*event){
         auto p=static_cast<Sprite*>(event->getCurrentTarget());
        p->runAction(ScaleTo::create(0,1));
    };
     Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(attlistener,sp5);
 
    return true;

}


float UI_Layer::getRad(Vec2 pos1){
    float px1=pos1.x;
    float py1=pos1.y;
    float x=px1-rokerPosition.x;
    float y=py1-rokerPosition.y;
    float xie=sqrt(pow(x,2)+pow(y,2));
    float cosAngle=x/xie;
    float rad=acos(cosAngle);
    if (py1<rokerPosition.x) {
        rad=-rad;
    }
    return rad;
}

Vec2 UI_Layer::getAnglePosition(float r,float angle){
    return ccp(r*cos(angle),r*sin(angle));
}





bool UI_Layer::onTouchBegan(Touch* touch,Event* evt)
{
  auto target=static_cast<Sprite*>(evt->getCurrentTarget());
    Vec2 locationInNode=target->convertToNodeSpace(touch->getLocation());
    Size s=target->getContentSize();//点到判断碰撞
    Rect rect=Rect(0,0,s.width,s.height);
    if (rect.containsPoint(locationInNode)) {
        return  true;
    }
    return false;
}

void UI_Layer::onTouchMoved(Touch* touch,Event* evt)
{
    Vec2 point=touch->getLocation();
    
     auto target=static_cast<Sprite*>(evt->getCurrentTarget());
    
    if (sqrt(pow((rokerPosition.x-point.x),2)+pow((rokerPosition.y-point.y),2))>=rockerBGR){
        float angle=getRad(point);
        
        target->setPosition(ccpAdd(getAnglePosition(rockerBGR, angle),rokerPosition));
    }else{
        target->setPosition(target->getPosition()+touch->getDelta());
    }
    if (target->getPosition().x<rokerPosition.x-50) {
        type=2;
    }
    else if (target->getPosition().x>rokerPosition.x+50) {
        type=3;
    }
    else if (target->getPosition().y<rokerPosition.y-50&&target->getPosition().x>rokerPosition.x-50&&target->getPosition().x<rokerPosition.x+50) {
        type=1;
    }
    else if (target->getPosition().y>rokerPosition.y+50&&target->getPosition().x>rokerPosition.x-50&&target->getPosition().x<rokerPosition.x+50) {
        type=4;
    }


}
void UI_Layer::onTouchEnded(Touch* touch,Event* evt)
{
    CCSprite *spRockerF=(CCSprite*)this->getChildByTag(1);
    spRockerF->runAction(CCMoveTo::create(0.05, rokerPosition));
    if (type<5)
        type=0;
    
    
}

void UI_Layer::callback1(Ref* psender){
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

void UI_Layer::onEnter(){
    Layer::onEnter();
    HelloWorld*he=(HelloWorld*)getParent()->getChildByTag(1);
    zhaoyun*z=he->zy;
    Vec2 point=he->getChildByTag(1)->getPosition();
    he->removeChildByTag(1);
    Player*p=Player::getInstance();
//    if (p->hero_now==p->hero_count) {
//        p->hero_now=0;
//    }
    z=(zhaoyun*)p->vecofhero.at(p->hero_now-1);
    z->setPosition(point);
    he->addChild(z,2,1);
  //  p->hero_now++;
    he->zy=z;

}
void UI_Layer::callback2(Ref* psender){
     Director::getInstance()->pushScene(State_Layer::createScene());
}
void UI_Layer::callback3(Ref* psender){

    
    HelloWorld*he=(HelloWorld*)getParent()->getChildByTag(1);
    he->will_changehero();
    zhaoyun*z=he->zy;
    Vec2 point=he->getChildByTag(1)->getPosition();
      he->removeChildByTag(1);
    Player*p=Player::getInstance();
    if (p->hero_now==p->hero_count) {
        p->hero_now=0;
    }
    z=(zhaoyun*)p->vecofhero.at(p->hero_now);
    z->setPosition(point);
      he->addChild(z,2,1);
    p->hero_now++;
    he->zy=z;

}

void UI_Layer::callback4(Ref* psender){
    
    ListView*lv=(ListView*)this->getChildByTag(20)->getChildByTag(55);
    
    
    if (herostateopen) {
        lv->runAction(MoveTo::create(0.3,Vec2(630,0)));
        MenuItemImage*Mit=static_cast<MenuItemImage*>(psender);
         Mit->runAction(MoveTo::create(0.3,Vec2(600,60)));
        herostateopen=false;
        
        update_Model();
        
        int num=Player::getInstance()->vecofhero.size();
        for (int i=1; i<num; i++) {
            load_message(i);
        }
        
//        for (auto i:lv->getItems()) {
//            i->setFocused(false);
//            i->setFocusEnabled(false);
//        }

 
   }
    else if (!herostateopen) {
        int num=Player::getInstance()->vecofhero.size();
        for (int i=1; i<num; i++) {
            lv->removeItem(1);
        }
        
        lv->runAction(MoveTo::create(0.3,Vec2(960,0)));
        MenuItemImage*Mit=static_cast<MenuItemImage*>(psender);
        Mit->runAction(MoveTo::create(0.3,Vec2(930,360)));

        herostateopen=true;
    }
}
void UI_Layer::update_Model(){
    Player*player=Player::getInstance();
    zhaoyun*zy=(zhaoyun*)player->vecofhero.at(0);
    ListView*lv=(ListView*)this->getChildByTag(20)->getChildByTag(55);
    ImageView*newimage=(ImageView*)lv->getChildByTag(64);
    newimage->loadTexture(zy->ui_picture);
    Text*text=(Text*)newimage->getChildByTag(68);
    text->setString(zy->ui_name);
    LoadingBar*lb=(LoadingBar*)newimage->getChildByTag(65);
    int max=zy->Max_Hp;
    int now=zy->nowhp;
    float percent=100*now/(float)max;
    lb->setPercent(percent);
    ImageView*hpbk=(ImageView*)newimage->getChildByTag(63);
    hpbk->setOpacity((100-percent)/2);
    

}

void UI_Layer::set_workstring(const char *string){
    Label*sp=(Label*)this->getChildByTag(8)->getChildByTag(8);
    sp->setString(string);
}

void UI_Layer::load_message(int i){

    Player*player=Player::getInstance();
    zhaoyun*zy=(zhaoyun*)player->vecofhero.at(i);
    ListView*lv=(ListView*)this->getChildByTag(20)->getChildByTag(55);
  
    ImageView*temp=(ImageView*)lv->getChildByTag(64);
    ImageView*newimage=(ImageView*)temp->clone();

    newimage->loadTexture(zy->ui_picture);
    Text*text=(Text*)newimage->getChildByTag(68);
    text->setString(zy->ui_name);
 
    LoadingBar*lb=(LoadingBar*)newimage->getChildByTag(65);
    int max=zy->Max_Hp;
    int now=zy->nowhp;
    float percent=100*now/(float)max;
    lb->setPercent(percent);
    ImageView*hpbk=(ImageView*)newimage->getChildByTag(63);
    hpbk->setOpacity((100-percent)/2);
    
    lv->pushBackCustomItem(newimage);
    
}

void UI_Layer::attori(float dt){
    type=0;
}