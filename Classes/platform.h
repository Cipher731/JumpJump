#ifndef PLATFORM_H
#define PLATFORM_H


#include "cocos2d.h"

class platform
{
private:
	
	const float scale = 0.7f;

public:
	cocos2d::Sprite * _root;
	platform(int type,int x,int y, cocos2d::Node *);
	~platform();
	int type;
	int direction;
};


#endif // !PLATFORM_H