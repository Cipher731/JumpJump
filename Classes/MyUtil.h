//
// Created by 毛海销 on 2018/7/21.
//

#ifndef JUMPJUMP_MYUTIL_H
#define JUMPJUMP_MYUTIL_H

#include "cocos2d.h"

namespace myutil {
void cacheAnimation(cocos2d::Vector<cocos2d::SpriteFrame *> &frameContainer,
                    const std::string &name,
                    float delay);
cocos2d::Animate *getCachedAnimateByName(const std::string &name);
};

#endif //JUMPJUMP_MYUTIL_H
