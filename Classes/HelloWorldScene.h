#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "soldier.h"
#include "Items.h"
class Animation_itools;
class zhaoyun;
class HelloWorld : public cocos2d::Layer
{
public:
    
    //三个生命周期函数
 
    // virtual void onEnterTransitionDidFinish();
  

    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    //static cocos2d::Scene* createScene$();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    //主要功能成员变量
    cocos2d::Vector<soldier*> vecs;
    cocos2d::Vector<Items*> vec_ite;
    cocos2d::Sprite*leishenchui;
    zhaoyun*zy;
    soldier*beatt;
    Animation_itools*itool;
    cocos2d::Size tilemapsize;
    
    //成员函数
    virtual bool init();
    CREATE_FUNC(HelloWorld);
    void loding_animation();
    void loding_moveByname(std::string name);
    void loding_attackByname(std::string name);
    void loding_deadByname(std::string name);
    void levelup_update(float dt);
    void creat_sold(float dt);//生产士兵
    void creat_gene(float dt);//生产将军
    void creat_Items(float dt);//生产道具
    void update(float dt);//主要处理主角攻击敌人。
    void update_map(float dt);//地图更新
    void akkack(float dt);//主角多段伤害
    void getItems(float dt);//获取道具
    void test(Ref*p);
    void come_back_atk(float dt);//恢复攻击
    void come_back_normal(float dt);//解除无敌
    void leishenchuiaction(float dt);//雷神锤更新函数
    void will_changehero();

    //辅助变量
    bool gameover;
    bool areadyatt;
    bool bigboun;//拥有投掷武器
   
    int udlr;
    //标示增益
    bool three_atk;
    
    
 
};

#endif // __HELLOWORLD_SCENE_H__
