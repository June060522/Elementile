#include "pch.h"
#include "RankingIcon.h"
#include "ResMgr.h"

RankingIcon::RankingIcon(Texture* _tex, Vec2 _pos, Vec2 _scale, Vec2 _vmenupos, GameSceneUI* _pGameSceneUI)
	:Image(_tex, _pos, _scale, _vmenupos, _pGameSceneUI)
{
}

void RankingIcon::Function()
{
	ResMgr::GetInst()->Play(L"Button");
}
