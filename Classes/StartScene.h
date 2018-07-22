//
// Created by 毛海销 on 2018/7/22.
//

#ifndef JUMPJUMP_STARTSCENE_H
#define JUMPJUMP_STARTSCENE_H

#include "cocos2d.h"

class StartScene : public cocos2d::Scene {
 public:
  static cocos2d::Scene *createScene();
  bool init() override;
  CREATE_FUNC(StartScene);
};

#endif //JUMPJUMP_STARTSCENE_H
