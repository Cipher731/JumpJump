//
// Created by 毛海销 on 2018/7/21.
//

#include "Bunny.h"
#include "Bullet.h"

USING_NS_CC;

Bunny::Bunny() {
  _root = Sprite::create();
  _root->setScale(SCALE);

  auto bodyFrame = SpriteFrame::create("bunnypuca_X.png", Rect(0, 0, 124, 120));
  _body = Sprite::createWithSpriteFrame(bodyFrame);
  _root->addChild(_body);

  auto gunFrame = SpriteFrame::create("liknjuska_X.png", Rect(0, 0, 28, 120));
  _gun = Sprite::createWithSpriteFrame(gunFrame);
  _root->addChild(_gun);
}

Bunny::Bunny(float x, float y, Node *targetNode, int targetLayer) : Bunny() {
  _root->setPosition(x, y);
  targetNode->addChild(_root, targetLayer);
}

cocos2d::Sprite *Bunny::getSprite() {
  return _root;
}

void Bunny::shootAt(cocos2d::Vec2 target) {
  Bullet(0, 0, _root, 0).moveTowards(target);
}

void Bunny::lookAt(cocos2d::Vec2 target) {
  auto dir = target - _root->getPosition();
  auto rotation = 90 - CC_RADIANS_TO_DEGREES(dir.getAngle());
  _gun->setRotation(rotation);
}
