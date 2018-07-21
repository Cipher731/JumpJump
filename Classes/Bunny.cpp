//
// Created by 毛海销 on 2018/7/21.
//

#include "Bunny.h"
#include "Bullet.h"
#include "MyUtil.h"

USING_NS_CC;
using namespace myutil;

Bunny::Bunny() {
  _root = Sprite::create();
  _root->setScale(SCALE);

  auto bodyFrame = SpriteFrame::create("bunnypuca_X.png", Rect(0, 0, 124, 120));
  _body = Sprite::createWithSpriteFrame(bodyFrame);
  _body->setVisible(false);
  _root->addChild(_body);

  auto gunFrame = SpriteFrame::create("liknjuska_X.png", Rect(0, 0, 28, 116));
  _gun = Sprite::createWithSpriteFrame(gunFrame);
  _gun->setPosition(-2, 0);
  _gun->setVisible(false);
  _root->addChild(_gun);

  auto frameContainer = Vector<SpriteFrame *>(4);
  auto texture = Director::getInstance()->getTextureCache()->addImage("propellerbunny_X.png");
  _booster = Sprite::createWithTexture(texture, Rect(0, 0, 64, 64));
  _booster->setPosition(0, 36);
  _booster->setVisible(false);
  _root->addChild(_booster);

  auto leftFrame = SpriteFrame::create("bunnyleft_X.png", Rect(0, 0, 124, 120));
  _normal_left = Sprite::createWithSpriteFrame(leftFrame);
  _root->addChild(_normal_left);

  auto rightFrame = SpriteFrame::create("bunnyright_X.png", Rect(0, 0, 124, 120));
  _normal_right = Sprite::createWithSpriteFrame(rightFrame);
  _normal_right->setVisible(false);
  _root->addChild(_normal_right);


  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      auto frame = SpriteFrame::createWithTexture(
          texture,
          CC_RECT_PIXELS_TO_POINTS(Rect(64 * j, 64 * i, 64, 64))
      );
      frameContainer.pushBack(frame);
    }
  }
  cacheAnimation(frameContainer, "booster", 0.1f);
  _booster->runAction(RepeatForever::create(getCachedAnimateByName("booster")));
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

void Bunny::setLeft() {
	_body->setVisible(false);
	_gun->setVisible(false);
	_normal_right->setVisible(false);
	_normal_left->setVisible(true);
}

void Bunny::setRight() {
	_body->setVisible(false);
	_gun->setVisible(false);
	_normal_right->setVisible(true);
	_normal_left->setVisible(false);
}

void Bunny::boost() {
  _gun->setVisible(false);
  _booster->setVisible(true);
  _root->runAction(
      Sequence::create(
          DelayTime::create(2),
          CallFunc::create([this]() {
            _gun->setVisible(true);
            _booster->setVisible(false);
          }),
          nullptr
      )
  );
}

