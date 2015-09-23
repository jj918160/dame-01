//
//  Bag_layer.h
//  animate_homework
//
//  Created by mac on 15-8-8.
//
//

#ifndef __animate_homework__Bag_layer__
#define __animate_homework__Bag_layer__

#include <stdio.h>
using namespace::cocos2d;
class Bag_layer:public Layer{
public:
    Vector<Sprite*>wuping;
    Vector<Sprite*>zhuangbei;
    virtual bool init();
    CREATE_FUNC(Bag_layer);
    
};
#endif /* defined(__animate_homework__Bag_layer__) */
