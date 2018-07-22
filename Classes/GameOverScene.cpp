//
// Created by 毛海销 on 2018/7/22.
//

#include "GameOverScene.h"
#include "HelloWorldScene.h"
USING_NS_CC;

cocos2d::Scene *GameOverScene::createScene() {
  return GameOverScene::create();
}

bool GameOverScene::init() {
  if (!Scene::init()) {
    return false;
  }

  auto bg = Sprite::create("hopbck_X.png");
  bg->setScale(4, 2);
  addChild(bg);

  auto start = MenuItemImage::create("playagainon_X.png", "playagainon_X.png", [](Ref* ref){
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, HelloWorld::createScene()));
  });

  auto menu = Menu::create();
  menu->addChild(start);
  menu->setPosition(512, 384);
  addChild(menu);

  return true;
}
