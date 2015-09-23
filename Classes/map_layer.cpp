//
//  map_layer.cpp
//  animate_homework
//
//  Created by mac on 15-7-18.
//
//
#include "HelloWorldScene.h"
#include "zhaoyun.h"
#include "map_layer.h"
#include "UI_Layer.h"
//#include "cocos-ext.h"
//USING_NS_CC_EXT;


map_layer*map_layer::create(const std::string filename)
{
    map_layer *pRet = new(std::nothrow) map_layer();
    if (pRet && pRet->init(filename))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool map_layer::init(const std::string filename){
    if (!Layer::init()) {
        return false;
    }
   // ControlButton*bbbb=ControlButton::create();
    CCLOG("cre");
    winsize=Director::getInstance()->getWinSize();
    
    _tileMap=TMXTiledMap::create(filename);
    CCLOG("out");
    
    size_height=_tileMap->getContentSize().height;
    size_width=_tileMap->getContentSize().width;
    
    _tileMap->setAnchorPoint(ccp(0.5,0.5));
    _tileMap->setPosition(0,0);
    this->addChild(_tileMap,0);
    // CCLOG("size:---%zd",_tileMap->getChildren().size());
    CCLOG("in");
    _collodable=_tileMap->getLayer("collidable");
    CCLOG("out");
    _collodable->setVisible(false);
    
    // CCLOG("Tx:%f-----Ty:%f",size_width,size_height);
    return true;
}


bool map_layer::init(){
    if (!Layer::init()) {
        return false;
    }
    winsize=Director::getInstance()->getWinSize();

    _tileMap=TMXTiledMap::create("first_hur2_Map.tmx");
    

    size_height=_tileMap->getContentSize().height;
    size_width=_tileMap->getContentSize().width;

    _tileMap->setAnchorPoint(ccp(0.5,0.5));
    _tileMap->setPosition(0,0);
    this->addChild(_tileMap,0);
   // CCLOG("size:---%zd",_tileMap->getChildren().size());

    _collodable=_tileMap->getLayer("collodable");

    _collodable->setVisible(false);

   // CCLOG("Tx:%f-----Ty:%f",size_width,size_height);
    return true;
}
Vec2 map_layer::tileCoordFromPosition(Vec2 pos){
    //CCLOG("pos.x:---  %f,pos.y---  %f",pos.x,pos.y);
    //CCLOG("size_width--- %f",size_width);
    
    int x=(pos.x+size_width/2)/_tileMap->getTileSize().width;
    int y=((_tileMap->getMapSize().height*_tileMap->getTileSize().height)-(pos.y+size_height/2))/_tileMap->getTileSize().height;
    //
    //CCLOG("x:---  %zd,y:---  %zd",x,y);
    return Vec2(x,y);
}

