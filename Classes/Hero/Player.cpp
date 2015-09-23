//
//  Player.cpp
//  animate_homework
//
//  Created by mac on 15-8-2.
//
//

#include "Player.h"
#include "zhaoyun.h"
#include "huangzhong.h"
#include "machao.h"
using namespace std;
Player* Player::_cacheInstance=nullptr;


Player* Player::getInstance(){
    if (!_cacheInstance) {
        _cacheInstance=new Player();
        //_cacheInstance->init();
    }
    if(_cacheInstance->vecofhero.size()==0)
    {
        _cacheInstance->init();
    }
    
    return _cacheInstance;
}

bool Player::init(){
    zhaoyun*zy=zhaoyun::create();
    vecofhero.pushBack(zy);
    
    huangzhong*hz=huangzhong::create();
    vecofhero.pushBack(hz);
   
       
    
    machao*mc=machao::create();
    vecofhero.pushBack(mc);
    


    
    
    hero_now=1;
    hero_count=vecofhero.size();
    return true;
}

void Player::addhero(zhaoyun*z){
    vecofhero.pushBack(z);
    hero_count=vecofhero.size();
}
Player::Player(){
    
}
Player::~Player(){
    
}