//
// Created by 毛海销 on 2018/7/21.
//

#include "Bullet.h"
#include "MyUtil.h"

USING_NS_CC;
using namespace myutil;

Bullet::Bullet() {
  auto texture = Director::getInstance()->getTextureCache()->addImage("jetpackbunny_X.png");
  _sprite = Sprite::createWithTexture(
      texture,
      CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 64, 128))
  );
  _sprite->setScale(SCALE);

  auto animate = getCachedAnimateByName("bullet");
  if (animate == nullptr) {
    auto frameContainer = Vector<SpriteFrame *>();
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 4; j++) {
        auto frame = SpriteFrame::createWithTexture(
            texture,
            CC_RECT_PIXELS_TO_POINTS(Rect(64 * j, 128 * i, 64, 128))
        );
        frameContainer.pushBack(frame);
        if (frameContainer.size() == 10) {
          break;
        }
      }
    }
    cacheAnimation(frameContainer, "bullet", 0.2);
    animate = getCachedAnimateByName("bullet");
  }

  _sprite->runAction(RepeatForever::create(animate));
}

Bullet::Bullet(float x, float y, Scene *targetScene, int targetLayer) : Bullet() {
  _sprite->setPosition(x, y);
  targetScene->addChild(_sprite, targetLayer);
}

void Bullet::moveTowards(float x, float y) {
  auto dir = Vec2(x, y) - _sprite->getPosition();
  auto rotation = CC_RADIANS_TO_DEGREES(dir.getAngle());
  _sprite->setRotation(rotation);
  _sprite->runAction(RepeatForever::create(MoveBy::create(0.1, SPEED * dir.getNormalized())));
}

cocos2d::Sprite *Bullet::getSprite() {
  return _sprite;
}
