//
//  zhaoyun.h
//  animate_homework
//
//  Created by mac on 15-7-16.
//
//

#ifndef __animate_homework__zhaoyun__
#define __animate_homework__zhaoyun__

#include <stdio.h>
#include "cocos2d.h"
class Animation_itools;

class zhaoyun:public cocos2d::Sprite{
public:
    std::string name;
     std::string last_name;
    CREATE_FUNC(zhaoyun);
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    Animation_itools*itool;
    virtual void loading_animation();
    int direction;//方向
    void walk(std::string godirection);
    void attack(std::string Adirection);
    virtual void update(float dt);
    virtual void attack_update(float dt);
    bool animate;//标示是否有动画
    bool strong;
    bool make_comb;//标示正在产生伤害
    void move(int direction);
    cocos2d::Size winsize;
    bool collision(cocos2d::Vec2 temp);
    int yester_direction;
    virtual void level_up();//升级调用，主要控制成长
    //属性成员变量：
    int Max_Hp;
    int nowhp;
    float atk;
    int Max_mp;
    int nowmp;
    int lv;    //等级
    int Max_exe;//最大经验
    int nowexe;//当前经验
    float speed;//速度
    std::string ui_name;
    std::string ui_picture;
    std::string ui_description;
};
#endif /* defined(__animate_homework__zhaoyun__) */
