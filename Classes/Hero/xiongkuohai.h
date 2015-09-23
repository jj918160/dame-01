//
//  xiongkuohai.h
//  animate_homework
//
//  Created by mac on 15-8-5.
//
//

#ifndef __animate_homework__xiongkuohai__
#define __animate_homework__xiongkuohai__

#include <stdio.h>
#include "zhaoyun.h"
class xiongkuohai:public zhaoyun{
public:
    
    CREATE_FUNC(xiongkuohai);
    //这三个函数必写。
    virtual bool init();
    virtual void update(float dt);
    virtual void level_up();//升级调用，主要控制成长
    
    
};

#endif /* defined(__animate_homework__xiongkuohai__) */
