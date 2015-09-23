//
//  Bag_layer.cpp
//  animate_homework
//
//  Created by mac on 15-8-8.
//
//
#include <Player.h>
#include "Bag_layer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "cocos-ext.h"


using namespace ui;

bool Bag_layer::init(){
    if (!Layer::init()) {
        return false;
    }
    auto rootNode = CSLoader::createNode("Layer.csb");

    
    ImageView*bt1=static_cast<ImageView*>(rootNode->getChildByTag(25));

    wuping=Player::getInstance()->wuping;
    zhuangbei=Player::getInstance()->zhuangbei;
//测试代码，后应删除
    for (int i=0; i<9; i++) {
        wuping.pushBack((Sprite*)bt1->clone());
    }
    
    for (int i=0; i<123; i++) {
        zhuangbei.pushBack((Sprite*)bt1->clone());
    }
//测试代码，后应删除
    ScrollView*sv2=static_cast<ScrollView*>(rootNode->getChildByTag(18));
    int k=wuping.size()/45+1;
    sv2->setInnerContainerSize(Size(300,500*(k)));
    for (int i=0; i<wuping.size(); i++) {
        int y=10*k-1-i/5;int x=i%5+1;
        ImageView*bt=(ImageView*)wuping.at(i);
        bt->setPosition(Vec2(50*x,50*y));
        sv2->addChild(bt);
    }
    
    ScrollView*sv1=static_cast<ScrollView*>(rootNode->getChildByTag(21));
    int k2=zhuangbei.size()/45+1;
    sv1->setInnerContainerSize(Size(300,500*(k2)));
    for (int i=0; i<zhuangbei.size(); i++) {
        int y=10*k2-1-i/5;int x=i%5+1;
        ImageView*bt=(ImageView*)zhuangbei.at(i);
        ImageView*btup=(ImageView*)bt->getChildByTag(26);
        btup->loadTexture("163.png");
               bt->setPosition(Vec2(50*x,50*y));
        sv1->addChild(bt);
    }
    
    
    
    
      addChild(rootNode,0,1);
    
    bt1->setVisible(false);
    
    
    
    return true;
}
