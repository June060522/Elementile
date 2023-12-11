#pragma once
#include "Image.h"
class Texture;
class MainIcon :
    public Image
{
public:
	MainIcon(Texture* _tex, Vec2 _pos, Vec2 _scale, Vec2 _vmenupos);
public:
	virtual void Function() override;
};

