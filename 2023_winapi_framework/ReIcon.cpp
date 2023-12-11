#include "pch.h"
#include "ReIcon.h"
#include "SceneMgr.h"
#include "GameSceneUI.h"
#include "ResMgr.h"

ReIcon::ReIcon(Texture* _tex, Vec2 _pos, Vec2 _scale, Vec2 _vmenupos, GameSceneUI* _pGameSceneUI)
	:Image(_tex, _pos, _scale, _vmenupos, _pGameSceneUI)
{
}

void ReIcon::Function()
{
	ResMgr::GetInst()->Play(L"Button");
	SceneMgr::GetInst()->LoadScene(L"GameScene");
}
