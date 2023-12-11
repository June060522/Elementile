#include "pch.h"
#include "ReIcon.h"
#include "SceneMgr.h"
#include "GameSceneUI.h"

ReIcon::ReIcon(Texture* _tex, Vec2 _pos, Vec2 _scale, Vec2 _vmenupos, GameSceneUI* _pGameSceneUI)
	:Image(_tex, _pos, _scale, _vmenupos, _pGameSceneUI)
{
}

void ReIcon::Function()
{
	SceneMgr::GetInst()->LoadScene(L"GameScene");
}
