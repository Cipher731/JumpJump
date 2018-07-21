//
// Created by 毛海销 on 2018/7/21.
//
#include "cocos2d.h"

#ifndef JUMPJUMP_BULLET_H
#define JUMPJUMP_BULLET_H

class Bullet {
 private:
  cocos2d::Sprite *_sprite;

  const float SCALE = 1;
  const float SPEED = 20;
 public:
  Bullet();
  Bullet(float x, float y, cocos2d::Scene *targetScene, int targetLayer);
  ~Bullet() = default;

  void moveTowards(float x, float y);
  cocos2d::Sprite *getSprite();
};

#endif //JUMPJUMP_BULLET_H
