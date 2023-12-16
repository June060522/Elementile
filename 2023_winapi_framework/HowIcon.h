#pragma once
#include "Image.h"
class Texture;
class GameInfoPanel;
class HowIcon :
    public Image
{
public:
	HowIcon(Texture* _tex, Vec2 _pos, Vec2 _scale, GameSceneUI* _pGameSceneUI, Vec2 _vmenupos);
public:
	virtual void Function() override;
	GameSceneUI* m_pGameSceneUI;
};