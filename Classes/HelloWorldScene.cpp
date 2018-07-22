/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"

USING_NS_CC;

using namespace CocosDenshion;

Scene *HelloWorld::createScene() {
  return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename) {
  printf("Error while loading: %s\n", filename);
  printf(
      "Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
  if (!Scene::init()) {
    return false;
  }

  //create Background

  auto bg = Sprite::create("hopbck_X.png");
  bg->setScaleX(4);
  bg->setScaleY(2);
  this->addChild(bg, 0);

  visibleSize = Director::getInstance()->getVisibleSize();

  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();

  _character = new Bunny(visibleSize.width / 2, 160, this, 3);
  _character->setLeft();

  for (int i = 200; i < visibleSize.height; i += 80) {
    generate_platform(i);
  }
  generate_platform(visibleSize.width / 2, 100);
  remain = 80;

  addKeyboardListener();

  schedule(schedule_selector(HelloWorld::update), 0.02f, kRepeatForever, 0);
  up_or_down = true;
  vertical_speed = 100;
  return true;
}

void HelloWorld::update(float f) {
  if (isMove) {
    moveCharacter(movekey);
  }
  auto pos = _character->getSprite()->getPosition();
  if (up_or_down) {
    if (pos.y < visibleSize.height / 2)
      pos.y += vertical_speed * 0.1;
    else {
      for (auto &it : thing) {
        auto t = it->getPosition();
        t.y -= vertical_speed * 0.1;
        it->setPosition(t);
      }
      remain -= vertical_speed * 0.1;
      if (remain < 0) {
        remain = 80;
        generate_platform(visibleSize.height - 20);
      }
    }
    vertical_speed -= 2;
  } else {
    pos.y -= vertical_speed * 0.1;
    vertical_speed += 2;
  }

  if (up_or_down && vertical_speed <= 0) {
    up_or_down = false;
    vertical_speed = 0;
  }

  _character->getSprite()->setPosition(pos);
  if (!up_or_down) {
    for (auto &it : thing) {
      if (pos.x > it->getPositionX() - 50
          && pos.x < it->getPositionX() + 50
          && pos.y > it->getPositionY() + 40
          && pos.y - it->getPositionY() < (40 + vertical_speed * 0.1)) {
        up_or_down = true;
        vertical_speed = 100;
      }
    }
  }
  
  for (auto it = thing.begin(); it != thing.end(); it++) {
	  if ((*it)->getPositionY() < -20) {
		  this->removeChild(*it);
		  for (auto &t : plats) {
			  if (t->_root == (*it)) {
				  plats.remove(t);
				  break;
			  }
		  }
		  it = thing.erase(it);
	  }
  }

  for (auto &it : plats) {
	  if (it->type == 1) {
		  auto pos = it->_root->getPosition();
		  if (it->direction == 0) {
			  pos.x -= 4;
		  }
		  else {
			  pos.x += 4;
		  }
		  it->_root->setPosition(pos);
		  if (pos.x < 20)
			  it->direction = 1;
		  else if (pos.x > visibleSize.width - 20)
			  it->direction = 0;
	  }
  }

  if (pos.y < 0) {
    unscheduleAllCallbacks();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, GameOverScene::createScene()));
  }
}

void HelloWorld::moveCharacter(char c) {
  auto pos = _character->getSprite()->getPosition();
  if (c == 'A') {
    if (pos.x > 0)
      pos.x -= 8;
    else
      pos.x = visibleSize.width;
    _character->setLeft();
  } else {
    if (pos.x < visibleSize.width)
      pos.x += 8;
    else
      pos.x = 0;
    _character->setRight();
  }
  _character->getSprite()->setPosition(pos);
}

void HelloWorld::addKeyboardListener() {
  auto keyboardListener = EventListenerKeyboard::create();
  keyboardListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
  keyboardListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
  _eventDispatcher->addEventListenerWithFixedPriority(keyboardListener, 1);
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode code, Event *event) {
  switch (code) {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    case EventKeyboard::KeyCode::KEY_CAPITAL_A:
    case EventKeyboard::KeyCode::KEY_A:
      movekey = 'A';
      isMove = true;
      break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    case EventKeyboard::KeyCode::KEY_CAPITAL_D:
    case EventKeyboard::KeyCode::KEY_D:
      movekey = 'D';
      isMove = true;
      break;
  }
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode code, Event *event) {
  switch (code) {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    case EventKeyboard::KeyCode::KEY_A:
    case EventKeyboard::KeyCode::KEY_CAPITAL_A:
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    case EventKeyboard::KeyCode::KEY_D:
    case EventKeyboard::KeyCode::KEY_CAPITAL_D:
      isMove = false;
      break;
  }
}

void HelloWorld::generate_platform(int y) {
  int x = cocos2d::RandomHelper::random_int(20, (int) visibleSize.width - 60);
  generate_platform(x, y);
}

void HelloWorld::generate_platform(int x, int y) {
	auto t = new platform(cocos2d::RandomHelper::random_int(0, 100) > 20 ? 0 : 1, x, y, this);
  plats.push_back(t);
  thing.push_back(t->_root);
}

void HelloWorld::menuCloseCallback(Ref *pSender) {
  //Close the cocos2d-x game scene and quit the application
  Director::getInstance()->end();
}
