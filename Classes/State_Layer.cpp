//
//  State_Layer.cpp
//  animate_homework
//
//  Created by mac on 15-8-2.
//
//
#include "Player.h"
#include "State_Layer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "zhaoyun.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio::timeline;
using namespace CocosDenshion;
Scene* State_Layer::createScene()
{
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = State_Layer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool State_Layer::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
//    if (Player::getInstance()->now==Player::hero_name::zhaoyun) {
//        Player::getInstance()->now=Player::hero_name::huangzhong;
//    }else if(Player::getInstance()->now==Player::hero_name::huangzhong){
//        Player::getInstance()->now=Player::hero_name::zhaoyun;
//    }

   
    auto rootNode = CSLoader::createNode("State.csb");

    addChild(rootNode,0,1);
    
    
    int k=Player::getInstance()->vecofhero.size();
 
    for (int i=1; i<k;i++){
       
        layoutcopy(i);
    }
    
    
    Button*bt=(Button*)rootNode->getChildByTag(100);
   
    bt->addTouchEventListener([=](Ref*p,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::BEGAN){
            SimpleAudioEngine::getInstance()->playEffect("dianji.wav");
        }
        else if(type==Widget::TouchEventType::ENDED){
            PageView*pg=(PageView*)rootNode->getChildByTag(44);
         

            Player::getInstance()->hero_now=pg->getCurPageIndex()+1;
            Director::getInstance()->popScene();
        }
    });

    
    set_hp();
    set_exp();
    set_speed();
    set_atk();
    set_lv();
    
    PageView*pg=(PageView*)rootNode->getChildByTag(44);
    pg->scrollToPage(Player::getInstance()->hero_now-1);
//    Player*player=Player::getInstance();
//    zhaoyun*zy=(zhaoyun*)player->vecofhero.at(0);
//    
//    Text*tx1=(Text*)rootNode->getChildByTag(44)->getChildByTag(46)->getChildByTag(63);
//    int max=zy->Max_Hp;
//    int now=zy->nowhp;
//    char tex[64]={0};
//    sprintf(tex,"%d/%d",now,max);
//    tx1->setString(tex);
//    
//    LoadingBar*lb1=(LoadingBar*)rootNode->getChildByTag(44)->getChildByTag(46)->getChildByTag(55);
//    lb1->setPercent(100*now/(float)max);
//    
//    
//    zhaoyun*zy2=(zhaoyun*)player->vecofhero.at(1);
//    Text*tx2=(Text*)rootNode->getChildByTag(44)->getChildByTag(66)->getChildByTag(75);
//    int max2=zy2->Max_Hp;
//    int now2=zy2->nowhp;
//    char tex2[64]={0};
//    sprintf(tex2,"%d/%d",now2,max2);
//    tx2->setString(tex2);
//    
//    LoadingBar*lb2=(LoadingBar*)rootNode->getChildByTag(44)->getChildByTag(66)->getChildByTag(70);
//    lb2->setPercent(100*now2/(float)max2);

    
    
    
    return true;
}






void State_Layer::set_hp(){
    
    auto rootNode=static_cast<Node*>(this->getChildByTag(1));
    
    Player*player=Player::getInstance();
    zhaoyun*zy=(zhaoyun*)player->vecofhero.at(0);
    
    Text*tx1=(Text*)rootNode->getChildByTag(44)->getChildByTag(46)->getChildByTag(63);
    int max=zy->Max_Hp;
    int now=zy->nowhp;
    char tex[64]={0};
    sprintf(tex,"%d/%d",now,max);
    tx1->setString(tex);
    
    LoadingBar*lb1=(LoadingBar*)rootNode->getChildByTag(44)->getChildByTag(46)->getChildByTag(55);
    lb1->setPercent(100*now/(float)max);
}

////
////    zhaoyun*zy2=(zhaoyun*)player->vecofhero.at(1);
////    Text*tx2=(Text*)rootNode->getChildByTag(44)->getChildByTag(66)->getChildByTag(75);
////    int max2=zy2->Max_Hp;
////    int now2=zy2->nowhp;
////    char tex2[64]={0};
////    sprintf(tex2,"%d/%d",now2,max2);
////    tx2->setString(tex2);
////    
////    LoadingBar*lb2=(LoadingBar*)rootNode->getChildByTag(44)->getChildByTag(66)->getChildByTag(70);
////    lb2->setPercent(100*now2/(float)max2);
//
//}



void State_Layer::set_exp(){
    auto rootNode=static_cast<Node*>(this->getChildByTag(1));
    
    Player*player=Player::getInstance();
    zhaoyun*zy=(zhaoyun*)player->vecofhero.at(0);
    
    
    
    
    
    Text*tx1=(Text*)rootNode->getChildByTag(44)->getChildByTag(46)->getChildByTag(65);
    int max=zy->Max_exe;
    int now=zy->nowexe;
    char tex[64]={0};
    sprintf(tex,"%d/%d",now,max);
    tx1->setString(tex);
    
    LoadingBar*lb1=(LoadingBar*)rootNode->getChildByTag(44)->getChildByTag(46)->getChildByTag(59);
    lb1->setPercent(100*now/(float)max);
}

//
////    zhaoyun*zy2=(zhaoyun*)player->vecofhero.at(1);
////    Text*tx2=(Text*)rootNode->getChildByTag(44)->getChildByTag(66)->getChildByTag(77);
////    int max2=zy2->Max_exe;
////    int now2=zy2->nowexe;
////    char tex2[64]={0};
////    sprintf(tex2,"%d/%d",now2,max2);
////    tx2->setString(tex2);
////    
////    LoadingBar*lb2=(LoadingBar*)rootNode->getChildByTag(44)->getChildByTag(66)->getChildByTag(74);
////    lb2->setPercent(100*now2/(float)max2);
//
//}

void State_Layer::set_atk(){
    auto rootNode=static_cast<Node*>(this->getChildByTag(1));
    
    Player*player=Player::getInstance();
    zhaoyun*zy=(zhaoyun*)player->vecofhero.at(0);
    
    Text*tx1=(Text*)rootNode->getChildByTag(44)->getChildByTag(46)->getChildByTag(44);
    float atk=zy->atk;
    char tex[64]={0};
    sprintf(tex,"%.1f",atk*3);
    tx1->setString(tex);
}
//
////    zhaoyun*zy2=(zhaoyun*)player->vecofhero.at(1);
////    Text*tx2=(Text*)rootNode->getChildByTag(44)->getChildByTag(66)->getChildByTag(52);
////    float atk2=zy2->atk;
////    CCLOG("hzatk2:%f",atk2);
////    char tex2[64]={0};
////    sprintf(tex2,"%.1f",atk2*3);
////    tx2->setString(tex2);
//
//}

void  State_Layer::set_lv(){
    auto rootNode=static_cast<Node*>(this->getChildByTag(1));
    
    Player*player=Player::getInstance();
    zhaoyun*zy=(zhaoyun*)player->vecofhero.at(0);
    
    Text*tx1=(Text*)rootNode->getChildByTag(44)->getChildByTag(46)->getChildByTag(42);
    int lev=zy->lv;
    char tex[64]={0};
    sprintf(tex,"%d",lev);
    tx1->setString(tex);
}
//
////    zhaoyun*zy2=(zhaoyun*)player->vecofhero.at(1);
////    Text*tx2=(Text*)rootNode->getChildByTag(44)->getChildByTag(66)->getChildByTag(49);
////    int lev2=zy2->lv;
////    char tex2[64]={0};
////    sprintf(tex2,"%d",lev2);
////    tx2->setString(tex2);
//}

void  State_Layer::set_speed(){
    auto rootNode=static_cast<Node*>(this->getChildByTag(1));
    
    Player*player=Player::getInstance();
    zhaoyun*zy=(zhaoyun*)player->vecofhero.at(0);
    
    Text*tx1=(Text*)rootNode->getChildByTag(44)->getChildByTag(46)->getChildByTag(46);
    float spe=zy->speed;
    char tex[64]={0};
    sprintf(tex,"%.1f",spe);
    tx1->setString(tex);
}

//    zhaoyun*zy2=(zhaoyun*)player->vecofhero.at(1);
//    Text*tx2=(Text*)rootNode->getChildByTag(44)->getChildByTag(66)->getChildByTag(53);
//    float spe2=zy2->speed;
//    char tex2[64]={0};
//    sprintf(tex2,"%.1f",spe2);
//    tx2->setString(tex2);
//    CCLOG("hzspeed:%f",spe2);

//}

void State_Layer::layoutcopy(int i){
  
    auto rootNode = (Node*)this->getChildByTag(1);
    
    auto la=(Layout*)rootNode->getChildByTag(44)->getChildByTag(46);
   
//Bug cocostudio资源要倾斜，并且这里要归正，不然触发断言。
    for(auto i:la->getChildren()){
        i->setRotation(0);
    }
    la->setRotation(0);
    
   auto la2=(Layout*)la->clone();
    
 

   
    PageView*page=(PageView*)rootNode->getChildByTag(44);
 
//
//   
//    
   zhaoyun*zy2=(zhaoyun*)Player::getInstance()->vecofhero.at(i);
    CCLOG("zy2->name%d`:%s",i,zy2->name.c_str());
    //加载姓名
    
   Text*tx1=(Text*)la2->getChildByTag(53);
    tx1->setString(zy2->ui_name);
    tx1->setColor(Color3B(0, 0, 255));

    //加载列传
    Text*tx2=(Text*)la2->getChildByTag(114);
    tx2->setString(zy2->ui_description);
    tx2->setColor(Color3B(0,255,0));

    //加载头像

    
    ImageView*image=(ImageView*)la2->getChildByTag(200);
    image->loadTexture(zy2->ui_picture);
    //image->setVisible(false);
   // ImageView*image2=ImageView::create(zy2->ui_picture);
   // image2->setPosition(Vec2(91,386));

    //la2->addChild(image2);
    
    
  

    //加载hp
    Text*tx3=(Text*)la2->getChildByTag(63);
    int max=zy2->Max_Hp;
    int now=zy2->nowhp;
    char tex[64]={0};
    sprintf(tex,"%d/%d",now,max);
    tx3->setString(tex);
    tx3->setColor(Color3B(255,0,0));
    //加载血条
    LoadingBar*lb1=(LoadingBar*)la2->getChildByTag(55);
    lb1->setPercent(100*now/(float)max);
   
 
    //加载经验
    Text*tx4=(Text*)la2->getChildByTag(65);
    int max2=zy2->Max_exe;
    int now2=zy2->nowexe;
    char tex2[64]={0};
    sprintf(tex2,"%d/%d",now2,max2);
    tx4->setString(tex2);
     tx4->setColor(Color3B(255,165,0));
    //加载经验条
    LoadingBar*lb2=(LoadingBar*)la2->getChildByTag(59);
    lb2->setPercent(100*now2/(float)max2);
    //加载atk
    Text*tx5=(Text*)la2->getChildByTag(44);
    float atk=zy2->atk;
    char tex3[64]={0};
    sprintf(tex3,"%.1f",atk*3);
    tx5->setString(tex3);
    tx5->setColor(Color3B(255,0,0));
    //加载等级
    Text*tx6=(Text*)la2->getChildByTag(42);
    int lev=zy2->lv;
    char tex4[64]={0};
    sprintf(tex4,"%d",lev);
    tx6->setString(tex4);
     tx6->setColor(Color3B(144,238,144));
    //加载速度

    Text*tx7=(Text*)la2->getChildByTag(46);
    float spe=zy2->speed;
    char tex5[64]={0};
    sprintf(tex5,"%.1f",spe);
    tx7->setString(tex5);
  tx7->setColor(Color3B(255,0,0));
     page->addPage(la2);
    
}
