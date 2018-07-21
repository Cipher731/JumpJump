//
// Created by 毛海销 on 2018/7/21.
//

#ifndef JUMPJUMP_BUNNY_H
#define JUMPJUMP_BUNNY_H

#include "cocos2d.h"

class Bunny {
 private:
  cocos2d::Sprite *_root;
  cocos2d::Sprite *_body;
  cocos2d::Sprite *_gun;

  const float SCALE = 1;
 public:
  Bunny();
  Bunny(float x, float y, cocos2d::Node *targetNode, int targetLayer);
  ~Bunny() = default;
  cocos2d::Sprite *getSprite();

  void shootAt(cocos2d::Vec2 target);
  void lookAt(cocos2d::Vec2 target);
};

#endif //JUMPJUMP_BUNNY_H
