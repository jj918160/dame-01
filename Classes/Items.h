//
//  Items.h
//  animate_homework
//
//  Created by mac on 15-7-18.
//
//

#ifndef __animate_homework__Items__
#define __animate_homework__Items__

#include <stdio.h>
class Items:public cocos2d::Sprite{
public:
    static Items* create(const char* filename)
    {
        Items *pRet = new(std::nothrow) Items();
        if (pRet && pRet->init(filename))
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
    bool init(std::string picname);
    int type;
   // void update(float dt);
    bool collision(cocos2d::Vec2 temp);
};

#endif /* defined(__animate_homework__Items__) */
