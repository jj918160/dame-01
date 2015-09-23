//
//  soldier.h
//  animate_homework
//
//  Created by mac on 15-7-18.
//
//

#ifndef __animate_homework__soldier__
#define __animate_homework__soldier__

#include <stdio.h>

class soldier:public cocos2d::Sprite{
public:
    static soldier* create(std::string picname,int hp,int atk,float speed=2)
    {
        soldier *pRet = new(std::nothrow) soldier();
        if (pRet && pRet->init(picname,hp,atk,speed))
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    }
    bool init(std::string picname,int hp,int atk,float speed);
    bool A_ttack;
    bool move;
    std::string name;
    std::string direction;
    std::string oldirection;
    void walk(std::string godirection);
    void attack(std::string Adirection);
    void update(float dt);
    int max_hp;
    int hp;
    int atk;
    int exp;
    float speed;
    void attack_hero(float dt);
    void runactiondead(std::string direction);

    
};

#endif /* defined(__animate_homework__soldier__) */
