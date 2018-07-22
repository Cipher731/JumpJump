#include "platform.h"

USING_NS_CC;

platform::platform(int type,int x,int y, cocos2d::Node *targetNode)
{
	_root = cocos2d::Sprite::create();
	_root->setScale(scale);

	if (type == 0) {
		auto p1 = SpriteFrame::create("gametilesbunny_X.png", Rect(0, 0, 130, 32));
		_root->addChild(Sprite::createWithSpriteFrame(p1));
	}
	else if(type ==1) {
		auto p1 = SpriteFrame::create("gametilesbunny_X.png", Rect(0, 36, 130, 32));
		_root->addChild(Sprite::createWithSpriteFrame(p1));
	}
	else {
		auto p1 = SpriteFrame::create("gametilesbunny_X.png", Rect(0, 144, 130, 36));
		_root->addChild(Sprite::createWithSpriteFrame(p1));
	}

	_root->setPosition(Vec2(x, y));
	targetNode->addChild(_root);
	this->type = type;
	direction = 0;
	remain = 2;
}


platform::~platform()
{
}

