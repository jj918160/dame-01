//
//  map_layer.h
//  animate_homework
//
//  Created by mac on 15-7-18.
//
//

#ifndef __animate_homework__map_layer__
#define __animate_homework__map_layer__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class zhaoyun;
class map_layer : public cocos2d::Layer
{
public:
    TMXTiledMap* _tileMap;
    TMXLayer*_collodable;
    virtual bool init();
    CREATE_FUNC(map_layer);
    static map_layer* create(const std::string filename);
    virtual bool init(const std::string filename);
    
   // void update(float dt);
    float size_width;
    float size_height;
    Size winsize;
  
      Vec2 tileCoordFromPosition(Vec2 pos);
};

#endif /* defined(__animate_homework__map_layer__) */
