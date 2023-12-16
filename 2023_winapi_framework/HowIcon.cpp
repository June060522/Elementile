#include "pch.h"
#include "HowIcon.h"
#include "ResMgr.h"
#include "GameSceneUI.h"

HowIcon::HowIcon(Texture* _tex, Vec2 _pos, Vec2 _scale, GameSceneUI* _pGameSceneUI, Vec2 _vmenupos)
	:Image(_tex, _pos, _scale, _vmenupos, _pGameSceneUI)
{
	m_pGameSceneUI = _pGameSceneUI;
}

void HowIcon::Function()
{
	m_pGameSceneUI->SetInfoPenalOpen(true);
	ResMgr::GetInst()->Play(L"Button");
}
