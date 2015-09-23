//
//  zhaoyun_r.h
//  animate_homework
//
//  Created by mac on 15-7-31.
//
//

#ifndef __animate_homework__zhaoyun_r__
#define __animate_homework__zhaoyun_r__

#include <stdio.h>
class Animation_itools;

class zhaoyun_r:public cocos2d::Sprite{
public:
    CREATE_FUNC(zhaoyun_r);
    virtual bool init();
    void loading_animation();
    void walk(std::string godirection);
    void update(float dt);
    void move(int direction);
   void xiaotitu_move(int direction);
    void set_speed(float sp);
    float get_speed();
    bool big_map;

private:
 
    bool collision(cocos2d::Vec2 temp);
    float speed;
    int yester_direction;
      Animation_itools*itool;
      int direction;//方向
    cocos2d::Size winsize;
    bool animate;//标示是否有动画
};

#endif /* defined(__animate_homework__zhaoyun_r__) */
