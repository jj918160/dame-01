//
//  Player.h
//  animate_homework
//
//  Created by mac on 15-8-2.
//
//

#ifndef __animate_homework__Player__
#define __animate_homework__Player__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class zhaoyun;
class Player{
public:
    enum class hero_name{
        zhaoyun=0,
        huangzhong,
    };
    //道具数组
    Vector<Sprite*>wuping;
    Vector<Sprite*>zhuangbei;
    
    Vector <Sprite*> vecofhero;
    virtual bool init();
    static Player* getInstance();
   // hero_name now;
    int hero_now;
    int hero_count;
    void addhero(zhaoyun*);
    Player();
    ~Player();
private:

    static Player* _cacheInstance; //cache instance
   
    //以及一堆自己的属性。
    
    
    
};

#endif /* defined(__animate_homework__Player__) */
