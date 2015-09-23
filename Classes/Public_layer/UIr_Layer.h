//
//  UIr_Layer.h
//  animate_homework
//
//  Created by mac on 15-7-31.
//
//

#ifndef __animate_homework__UIr_Layer__
#define __animate_homework__UIr_Layer__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class zhaoyun_r;
class UIr_Layer : public cocos2d::Layer
{
public:
    
    virtual bool init();
    CREATE_FUNC(UIr_Layer);
    static int type;
    float getRad(Vec2 pos1);
  
    Vec2 getAnglePosition(float r,float angle);
    Vec2 rokerPosition;
    float rockerBGR;
     void callback1(Ref* psender);
    bool workespaceopen;
    void set_workstring(const char *string);
    void callback2(Ref* psender);
    void callback3(Ref* psender);
    bool bag_open;
   };

#endif /* defined(__animate_homework__UIr_Layer__) */
