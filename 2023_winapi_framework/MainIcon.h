#pragma once
#include "Image.h"
class Texture;
class MainIcon :
    public Image
{
public:
	MainIcon(Texture* _tex, Vec2 _pos, Vec2 _scale);
public:
	virtual void Function() override;
};

