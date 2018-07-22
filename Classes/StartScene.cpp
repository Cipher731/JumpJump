//
// Created by 毛海销 on 2018/7/22.
//

#include "StartScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

cocos2d::Scene *StartScene::createScene() {
  return StartScene::create();
}

bool StartScene::init() {
  if (!Scene::init()) {
    return false;
  }

  auto bg = Sprite::create("hopbck_X.png");
  bg->setScale(4, 2);
  addChild(bg);

  auto start = MenuItemImage::create("play_X.png", "playon_X.png", [](Ref* ref){
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, HelloWorld::createScene()));
  });

  auto menu = Menu::create();
  menu->addChild(start);
  menu->setPosition(512, 384);
  addChild(menu);

  return true;
}
