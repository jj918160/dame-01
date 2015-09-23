//
//  UI_Layer.h
//  animate_homework
//
//  Created by mac on 15-7-16.
//
//

#ifndef __animate_homework__UI_Layer__
#define __animate_homework__UI_Layer__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class zhaoyun;
class UI_Layer : public cocos2d::Layer
{
public:
    virtual void onEnter();
    virtual bool init();
    CREATE_FUNC(UI_Layer);
    static int type;
   // Sprite *p;
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void attori(float dt);
    float getRad(Vec2 pos1);
    Vec2 getAnglePosition(float r,float angle);
    Vec2 rokerPosition;
    float rockerBGR;
    
    
    void callback1(Ref* psender);
    void callback2(Ref* psender);
    void callback3(Ref* psender);
    void callback4(Ref* psender);
    bool workespaceopen;
    bool herostateopen;
    void set_workstring(const char *string);
    void load_message(int i);
    void update_Model();
};

#endif /* defined(__animate_homework__UI_Layer__) */
