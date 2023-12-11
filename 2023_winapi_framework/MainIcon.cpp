#include "pch.h"
#include "MainIcon.h"
#include "SceneMgr.h"
#include "GameSceneUI.h"

MainIcon::MainIcon(Texture* _tex, Vec2 _pos, Vec2 _scale, Vec2 _vmenupos, GameSceneUI* _pGameSceneUI)
	:Image(_tex, _pos, _scale, _vmenupos,_pGameSceneUI)
{
}

void MainIcon::Function()
{
	SceneMgr::GetInst()->LoadScene(L"StartScene");
}