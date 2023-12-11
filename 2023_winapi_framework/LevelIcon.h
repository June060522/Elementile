#pragma once
#include "Image.h"
class Texture;
class LevelIcon :
    public Image
{
public:
	LevelIcon(Texture* _tex, Vec2 _pos, Vec2 _scale, Vec2 _vmenupos);
public:
	virtual void Function() override;
};

