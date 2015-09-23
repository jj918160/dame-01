//
//  Second_Scene.h
//  animate_homework
//
//  Created by mac on 15-8-5.
//
//

#ifndef __animate_homework__Second_Scene__
#define __animate_homework__Second_Scene__

#include <stdio.h>
#include "cocos2d.h"

class Talking_Rush;
class Animation_itools;
class Nofight_Scene_Base;
class Second_Scene:public cocos2d::Layer{
public:
    CREATE_FUNC(Second_Scene);
    static cocos2d::Scene* createScene();
    virtual bool init();
    Nofight_Scene_Base*base;
    void update(float dt);
    bool talking;//对话中状态
     Animation_itools*itools;
    void talk1();
     void addhero1(float dt);
    bool addok;//添加完成
    bool isadding;//只执行一次动画标示
    bool changescene;//标示主线完成
    bool changing;//标示正在换剧场，之执行一次
    bool cantouch;//记录目标是否可点击
};
#endif /* defined(__animate_homework__Second_Scene__) */
