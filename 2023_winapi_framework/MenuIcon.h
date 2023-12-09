#pragma once
#include "Image.h"
#include "Texture.h"
class MenuIcon :
	public Image
{
public:
	MenuIcon(Texture* _tex, Vec2 _pos, Vec2 _scale);
public:
	virtual void Update() override;
};

