#pragma once
#include "Image.h"
class Texture;
class GameSceneUI;
class SoundIcon :
    public Image
{
public:
	SoundIcon(Texture* _tex, Vec2 _pos, Vec2 _scale, Vec2 _vmenupos, GameSceneUI* _pGameSceneUI);
public:
	virtual void Function() override;
	virtual void Render(HDC _dc) override;
private:
	Texture* m_pTex;
	Texture* m_pOffTex;
	GameSceneUI* m_pGameSceneUI;
};

