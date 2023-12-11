#include "pch.h"
#include "LevelIcon.h"
#include "GameSceneUI.h"
#include "ResMgr.h"

LevelIcon::LevelIcon(Texture* _tex, Vec2 _pos, Vec2 _scale, Vec2 _vmenupos, GameSceneUI* _pGameSceneUI)
	:Image(_tex, _pos, _scale, _vmenupos, _pGameSceneUI)
{
}

void LevelIcon::Function()
{
	ResMgr::GetInst()->Play(L"Button");
	m_pGameSceneUI->SetStagePenalOpen(!m_pGameSceneUI->GetStagePenalOpen());
}