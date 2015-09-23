//
//  Begin_Layer.h
//  animate_homework
//
//  Created by mac on 15-7-19.
//
//

#ifndef __animate_homework__Begin_Layer__
#define __animate_homework__Begin_Layer__

#include <stdio.h>
#include "cocostudio/CocoStudio.h"

#include "ui/CocosGUI.h"
class Animation_itools;
class Begin_Layer : public cocos2d::Layer

{
    
public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    
    virtual bool init();
    
    // implement the "static create()" method manually
    
    CREATE_FUNC(Begin_Layer);
    
    void touchButton(cocos2d::Ref*ref ,cocos2d::ui::TouchEventType type);
    void loading_animation();
    Animation_itools*itools;
    void creat_botton(int t);
    void creat_name_IBM();
    Vector<MenuItem*>vecfoeitem;
    void callback1(Ref* psender);
    void callback2(Ref* psender);
    void callback3(Ref* psender);
    void callback4(Ref* psender);
    void callback5(Ref* psender);
    void create_bird(Vec2 point,Vec2 point2,float t);
    void create_bird(float t);
    void back_update(float dt);
    void create_flower(float dt);
};



#endif /* defined(__animate_homework__Begin_Layer__) */
