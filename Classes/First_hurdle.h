//
//  First_hurdle.h
//  animate_homework
//
//  Created by mac on 15-7-23.
//
//

#ifndef __animate_homework__First_hurdle__
#define __animate_homework__First_hurdle__

#include <stdio.h>
#include "cocos2d.h"
class First_hurdle:public cocos2d::Layer{
public:
    CREATE_FUNC(First_hurdle);
    static cocos2d::Scene* createScene();
   virtual bool init();
    virtual void onEnterTransitionDidFinish();
    void gameover();
    void back_game(cocos2d::Ref *sender);
   virtual void update(float dt);
    
};
#endif /* defined(__animate_homework__First_hurdle__) */
