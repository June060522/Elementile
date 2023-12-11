#pragma once
#include "Image.h"
class Texture;
class GameSceneUI;
class LevelIcon :
    public Image
{
public:
	LevelIcon(Texture* _tex, Vec2 _pos, Vec2 _scale, Vec2 _vmenupos, GameSceneUI* _pGameSceneUI);
public:
	virtual void Function() override;
};

