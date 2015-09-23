//
//  Nofight_Scene_Base.h
//  animate_homework
//
//  Created by mac on 15-8-5.
//
//

#ifndef __animate_homework__Nofight_Scene_Base__
#define __animate_homework__Nofight_Scene_Base__

#include <stdio.h>
#include "cocos2d.h"
//这个基类包含主角和地图
//城镇场景＝这个＋UIr＋他自己的逻辑。
typedef enum{
    tag_player,
    Tag_map,
}Tag_Nofight;
class zhaoyun_r;
class Nofight_Scene_Base: public cocos2d::Layer
{
public:
    // static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Nofight_Scene_Base);
    static Nofight_Scene_Base* create(const std::string filename);
    virtual bool init(const std::string filename);
    zhaoyun_r*zy;

    void update(float dt);//地图更新
    
};

#endif /* defined(__animate_homework__Nofight_Scene_Base__) */
