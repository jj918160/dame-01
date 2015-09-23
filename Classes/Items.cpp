//
//  Items.cpp
//  animate_homework
//
//  Created by mac on 15-7-18.
//
//

#include "Items.h"
#include "map_layer.h"
#include "zhaoyun.h"
bool Items::init(std::string picname){
    if (!Sprite::init()) {
        return false;
    }
    this->initWithFile(picname);
    type=0;
   // scheduleUpdate();
    return true;
}

bool Items::collision(Vec2 temp){
    CCLOG("collision");
   
    map_layer*m=(map_layer*)this->getParent()->getChildByTag(2);
    
     CCLOG("temp.x-----%f,temp.y------%f",temp.x,temp.y);
    
    Vec2 t2=m->tileCoordFromPosition(temp);
     CCLOG("t2.x:--%f,t2.y:----%f",t2.x,t2.y);
    
    
    int tileGid=m->_collodable->getTileGIDAt(t2);
    CCLOG("tileGid----%d",tileGid);
    if (tileGid>0) {
           CCLOG("in-----");
        Value prop=m->_tileMap->getPropertiesForGID(tileGid);
           CCLOG("out1");
        ValueMap propValueMap=prop.asValueMap();
        //
          CCLOG("out2");
        std::string collision=propValueMap["collidable"].asString();
          CCLOG("out3");
        if (collision=="true") {
            return  true;   //碰撞成功
        }
    }
    return false;
}
