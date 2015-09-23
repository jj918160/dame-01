//
//  About_Scene.cpp
//  animate_homework
//
//  Created by mac on 15-8-4.
//
//
#include "cocos2d.h"

#include "About_Scene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio::timeline;
using namespace CocosDenshion;
Scene* About_Layer::createScene()
{
  //  ControlButton*bbbbbbbbb=ControlButton::create();
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = About_Layer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool About_Layer::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    auto rootNode = CSLoader::createNode("About.csb");
    
    addChild(rootNode,0,1);
    
    Button*bt=(Button*)rootNode->getChildByTag(20);
    bt->addTouchEventListener([=](Ref*p,Widget::TouchEventType type){
        if(type==Widget::TouchEventType::BEGAN){
            SimpleAudioEngine::getInstance()->playEffect("dianji.wav");
        }
        else if(type==Widget::TouchEventType::ENDED){
            Director::getInstance()->popScene();
        }
    });
    
    ScrollView*sl=static_cast<ScrollView*>(rootNode->getChildByTag(19));
    sl->scrollToBottom(10,false);
 
    return true;
}
