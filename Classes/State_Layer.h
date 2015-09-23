//
//  State_Layer.h
//  animate_homework
//
//  Created by mac on 15-8-2.
//
//

#ifndef __animate_homework__State_Layer__
#define __animate_homework__State_Layer__

#include <stdio.h>
#include "cocos2d.h"
class zhaoyun;
class State_Layer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(State_Layer);
    
   
//    
    void set_hp();
    
    void set_exp();
    
    void set_atk();
    
    void  set_lv();
    
    void  set_speed();
    
    void layoutcopy(int i);
    
   
    
    
};

#endif /* defined(__animate_homework__State_Layer__) */
