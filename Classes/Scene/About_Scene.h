//
//  About_Scene.h
//  animate_homework
//
//  Created by mac on 15-8-4.
//
//

#ifndef __animate_homework__About_Scene__
#define __animate_homework__About_Scene__

#include <stdio.h>
#include "cocos2d.h"

class About_Layer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(About_Layer);
    
    
    
    
};


#endif /* defined(__animate_homework__About_Scene__) */
