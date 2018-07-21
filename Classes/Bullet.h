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
  Bullet(float x, float y, cocos2d::Node *targetNode, int targetLayer);
  ~Bullet() = default;
  cocos2d::Sprite *getSprite();

  void moveTowards(const cocos2d::Vec2 &target);
};

#endif //JUMPJUMP_BULLET_H
