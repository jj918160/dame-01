//
//  zhangfei.h
//  animate_homework
//
//  Created by mac on 15-8-4.
//
//

#ifndef __animate_homework__zhangfei__
#define __animate_homework__zhangfei__

#include <stdio.h>
#include "zhaoyun.h"
class zhangfei:public zhaoyun{
public:
    
    CREATE_FUNC(zhangfei);
    virtual bool init();
    virtual void loading_animation();
    virtual void update(float dt);
    virtual void attack_update(float dt);
    virtual void level_up();//升级调用，主要控制成长
    
    
};
#endif /* defined(__animate_homework__zhangfei__) */
