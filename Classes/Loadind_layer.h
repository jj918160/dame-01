//
//  Loadind_layer.h
//  animate_homework
//
//  Created by mac on 15-7-31.
//
//

#ifndef __animate_homework__Loadind_layer__
#define __animate_homework__Loadind_layer__

#include <stdio.h>
#include "cocos2d.h"
class Animation_itools;
//class UIr_Layer;
class Loading_layer:public cocos2d::Layer{
public:
    CREATE_FUNC(Loading_layer);
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void update(float dt);
    bool change;
    void change_tp1(float dt);
    void change_tp2(float dt);
    void change_tp3(float dt);
    void change_4(float dt);
private:
    Animation_itools*itools;
    bool add;
    
   // UIr_Layer*ui_layer;
};

#endif /* defined(__animate_homework__Loadind_layer__) */
