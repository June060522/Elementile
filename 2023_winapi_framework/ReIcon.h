#pragma once
#include "Image.h"
class Texture;
class ReIcon :
    public Image
{
public:
	ReIcon(Texture* _tex, Vec2 _pos, Vec2 _scale);
public:
	virtual void Function() override;
};

