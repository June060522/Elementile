#include "pch.h"
#include "RankingIcon.h"
#include "ResMgr.h"
#include "GameSceneUI.h"
#include "ServerManager.h"

RankingIcon::RankingIcon(Texture* _tex, Vec2 _pos, Vec2 _scale, Vec2 _vmenupos, GameSceneUI* _pGameSceneUI)
	:Image(_tex, _pos, _scale, _vmenupos, _pGameSceneUI)
{
	m_pGameSceneUI = _pGameSceneUI;
}

void RankingIcon::Function()
{
	m_pGameSceneUI->SetRankingPenalOpen(true);
	ResMgr::GetInst()->Play(L"Button");
	ServerManager::GetInst()->GetRanking(m_pGameSceneUI);
}
