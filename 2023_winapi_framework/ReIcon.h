#pragma once
#include "Image.h"
class Texture;
class GameSceneUI;
class ReIcon :
    public Image
{
public:
	ReIcon(Texture* _tex, Vec2 _pos, Vec2 _scale, Vec2 _vmenupos, GameSceneUI* _pGameSceneUI);
public:
	virtual void Function() override;
};

