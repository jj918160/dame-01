//
//  Nofight_Scene_Base.cpp
//  animate_homework
//
//  Created by mac on 15-8-5.
//
//

#include "Nofight_Scene_Base.h"
#include "map_layer.h"
#include "zhaoyun_r.h"
#include "UIr_Layer.h"

Nofight_Scene_Base* Nofight_Scene_Base::create(const std::string filename){
    

        Nofight_Scene_Base *pRet = new(std::nothrow) Nofight_Scene_Base();
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

bool Nofight_Scene_Base::init(const std::string filename)
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    
    
    
    map_layer*map=map_layer::create(filename);
    //map->init("first_hur2_Map.tmx");
    map->setPosition(0, 0);
    this->addChild(map,0,2);
    
    
    zy=zhaoyun_r::create();
    zy->setPosition(300,300);
    zy->set_speed(10);
    this->addChild(zy,2,1);
    
    //
    
    scheduleUpdate();
    
    
    return true;
}



bool Nofight_Scene_Base::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }


    
    
    
    map_layer*map=map_layer::create("map2.tmx");
    //map->init("first_hur2_Map.tmx");
    map->setPosition(0, 0);
    this->addChild(map,0,2);
    
    
    zy=zhaoyun_r::create();

    zy->setPosition(300,300);
    zy->set_speed(10);
    this->addChild(zy,2,1);
    
    //
   
    scheduleUpdate();
    
    
    return true;
}


void Nofight_Scene_Base::update(float dt)
    {
        int k=UIr_Layer::type;
        map_layer* map=(map_layer*)this->getChildByTag(2);
        Size winsize=Director::getInstance()->getWinSize();
        Vec2 temp=this->convertToWorldSpace(zy->getPosition());
        float spd=zy->get_speed();
        
        switch (k) {
            case 1://右
            {
                if (temp.x>winsize.width*3/4&&zy->getPositionX()<map->size_width/2-winsize.width/4) {
                    this->setPositionX(this->getPositionX()-spd);
                }
            }
                break;
            case 2://右上
            {
                if (temp.y>winsize.height*3/4&&zy->getPositionY()<map->size_height/2-winsize.height/4) {
                    this->setPositionY(this->getPositionY()-spd/sqrt(2.0));
                }
                if (temp.x>winsize.width*3/4&&zy->getPositionX()<map->size_width/2-winsize.width/4) {
                    this->setPositionX(this->getPositionX()-spd/sqrt(2.0));
                }
            }
                break;
            case 3://上
            {
                if (temp.y>winsize.height*3/4&&zy->getPositionY()<map->size_height/2-winsize.height/4) {
                    this->setPositionY(this->getPositionY()-spd);
                }

            }
                break;
            case 4://左上
            {
                if (temp.y>winsize.height*3/4&&zy->getPositionY()<map->size_height/2-winsize.height/4) {
                    this->setPositionY(this->getPositionY()-spd/sqrt(2.0));
                }
                if (temp.x<winsize.width/4&&zy->getPositionX()>-map->size_width/2+winsize.width/4) {
                    this->setPositionX(this->getPositionX()+spd/sqrt(2.0));
                }

            }
                break;
            case 5://左
            {
                if (temp.x<winsize.width/4&&zy->getPositionX()>-map->size_width/2+winsize.width/4) {
                    this->setPositionX(this->getPositionX()+spd);
                }
            }
                break;
            case 6://坐下
            {
                if (temp.y<winsize.height/4&&zy->getPositionY()>-map->size_height/2+winsize.height/4) {
                    this->setPositionY(this->getPositionY()+spd/sqrt(2.0));
                }
                if (temp.x<winsize.width/4&&zy->getPositionX()>-map->size_width/2+winsize.width/4) {
                    this->setPositionX(this->getPositionX()+spd/sqrt(2.0));
                }

            }
                break;
            case 7://下
            {
                if (temp.y<winsize.height/4&&zy->getPositionY()>-map->size_height/2+winsize.height/4) {
                    this->setPositionY(this->getPositionY()+spd);
                }
            }
                break;
            case 8://右下
            {
                if (temp.y<winsize.height/4&&zy->getPositionY()>-map->size_height/2+winsize.height/4) {
                    this->setPositionY(this->getPositionY()+spd/sqrt(2.0));
                }
                if (temp.x>winsize.width*3/4&&zy->getPositionX()<map->size_width/2-winsize.width/4) {
                    this->setPositionX(this->getPositionX()-spd/sqrt(2.0));
                }

            }
                break;
                
            default:
                break;
        }
        
        
    }

//void Nofight_Scene_Base::update(float dt)
//{
//    int k=UIr_Layer::type;
//    CCLOG("k:%d",k);
//    map_layer* map=(map_layer*)this->getChildByTag(Tag_map);
//    
//    Size winsize=Director::getInstance()->getWinSize();
//    Vec2 temp=map->convertToWorldSpace(zy->getPosition());
//    float spd=zy->get_speed();
//    switch (k) {
//            
//        case 1://右
//        {
//            if (temp.x>winsize.width*3/4&&zy->getPositionX()<map->size_width/2-winsize.width/4) {
//                map->setPositionX(map->getPositionX()-spd);
//            }
//        }
//            break;
//        case 2://右上
//        {
//            if (temp.y>winsize.height*3/4&&zy->getPositionY()<map->size_height/2-winsize.height/4) {
//                map->setPositionY(map->getPositionY()-spd/sqrt(2.0));
//            }
//            if (temp.x>winsize.width*3/4&&zy->getPositionX()<map->size_width/2-winsize.width/4) {
//                map->setPositionX(map->getPositionX()-spd/sqrt(2.0));
//            }
//        }
//            break;
//        case 3://上
//        {
//            if (temp.y>winsize.height*3/4&&zy->getPositionY()<map->size_height/2-winsize.height/4) {
//                map->setPositionY(map->getPositionY()-spd);
//            }
//            
//        }
//            break;
//        case 4://左上
//        {
//            if (temp.y>winsize.height*3/4&&zy->getPositionY()<map->size_height/2-winsize.height/4) {
//                map->setPositionY(map->getPositionY()-spd/sqrt(2.0));
//            }
//            if (temp.x<winsize.width/4&&zy->getPositionX()>-map->size_width/2+winsize.width/4) {
//                map->setPositionX(map->getPositionX()+spd/sqrt(2.0));
//            }
//            
//        }
//            break;
//        case 5://左
//        {
//            if (temp.x<winsize.width/4&&zy->getPositionX()>-map->size_width/2+winsize.width/4) {
//                map->setPositionX(map->getPositionX()+spd);
//            }
//        }
//            break;
//        case 6://坐下
//        {
//            if (temp.y<winsize.height/4&&zy->getPositionY()>-map->size_height/2+winsize.height/4) {
//                map->setPositionY(map->getPositionY()+spd/sqrt(2.0));
//            }
//            if (temp.x<winsize.width/4&&zy->getPositionX()>-map->size_width/2+winsize.width/4) {
//                map->setPositionX(map->getPositionX()+spd/sqrt(2.0));
//            }
//            
//        }
//            break;
//        case 7://下
//        {
//            if (temp.y<winsize.height/4&&zy->getPositionY()>-map->size_height/2+winsize.height/4) {
//                map->setPositionY(map->getPositionY()+spd);
//            }
//        }
//            break;
//        case 8://右下
//        {
//            if (temp.y<winsize.height/4&&zy->getPositionY()>-map->size_height/2+winsize.height/4) {
//                map->setPositionY(map->getPositionY()+spd/sqrt(2.0));
//            }
//            if (temp.x>winsize.width*3/4&&zy->getPositionX()<map->size_width/2-winsize.width/4) {
//                map->setPositionX(map->getPositionX()-spd/sqrt(2.0));
//            }
//            
//        }
//            break;
//            
//            
//            
//        default:
//            break;
//    }
//    
//    
//}


