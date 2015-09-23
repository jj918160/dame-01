//
//  First_Scene.h
//  animate_homework
//
//  Created by mac on 15-7-31.
//
//

#ifndef __animate_homework__First_Scene__
#define __animate_homework__First_Scene__

#include <stdio.h>
#include "cocos2d.h"
class Talking_Rush;
class Animation_itools;
class First_Scene:public cocos2d::Layer{
public:
    CREATE_FUNC(First_Scene);
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void update(float dt);
    bool change;
    //Talking_Rush*talk_layer;
    void talk_1();
        void talk_2();
    void  talk_3();
    bool talking;
    void LoadingAnimation();
    Animation_itools*itools;
    bool changescene;
    int renwu_jindu;
    void addhero1(float dt);
    bool addok;
    bool isadding;
    void callback0();
};

#endif /* defined(__animate_homework__First_Scene__) */
