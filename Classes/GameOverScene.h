//
// Created by 毛海销 on 2018/7/22.
//

#ifndef JUMPJUMP_GAMEOVERSCENE_H
#define JUMPJUMP_GAMEOVERSCENE_H

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene {
 public:
  static cocos2d::Scene *createScene();
  bool init() override;
  CREATE_FUNC(GameOverScene);
};

#endif //JUMPJUMP_GAMEOVERSCENE_H
