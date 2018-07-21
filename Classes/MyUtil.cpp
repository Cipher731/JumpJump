//
// Created by 毛海销 on 2018/7/21.
//

#include "MyUtil.h"

void myutil::cacheAnimation(cocos2d::Vector<cocos2d::SpriteFrame *> &frameContainer,
                            const std::string &name,
                            float delay) {
  auto animation = cocos2d::Animation::createWithSpriteFrames(frameContainer, delay);
  cocos2d::AnimationCache::getInstance()->addAnimation(animation, name);
}

cocos2d::Animate *myutil::getCachedAnimateByName(const std::string &name) {
  auto animation = cocos2d::AnimationCache::getInstance()->getAnimation(name);
  return animation == nullptr ? nullptr : cocos2d::Animate::create(animation);
}