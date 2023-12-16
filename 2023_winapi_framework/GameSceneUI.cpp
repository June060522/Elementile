#include "pch.h"
#include "GameSceneUI.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "DataManager.h"
#include "UIText.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Image.h"
#include "MenuIcon.h"
#include "MainIcon.h"
#include "LevelIcon.h"
#include "SoundIcon.h"
#include "ReIcon.h"
#include "RankingIcon.h"
#include "StagePanel.h"
#include "RankingPanel.h"

void GameSceneUI::Init()
{
	m_isOpen = false;
	m_isStageOpen = false;
	m_isRankingOpen = false;
	m_pMenuTex = ResMgr::GetInst()->TexLoad(L"Menu", L"Texture\\menu.bmp");
	m_pRETex = ResMgr::GetInst()->TexLoad(L"Regame", L"Texture\\regame.bmp");
	m_pMainTex = ResMgr::GetInst()->TexLoad(L"Main", L"Texture\\main.bmp");
	m_pLvTex = ResMgr::GetInst()->TexLoad(L"Lv", L"Texture\\level.bmp");
	m_pSoundTex = ResMgr::GetInst()->TexLoad(L"Sound", L"Texture\\sound.bmp");
	m_pRankingTex = ResMgr::GetInst()->TexLoad(L"Ranking", L"Texture\\ranking.bmp");

	m_pMenu = new MenuIcon(m_pMenuTex, { 1450,90 }, { 20,20 }, this, { 1450,90 });
	m_pMain = new MainIcon(m_pMainTex, { 1450, 220 }, { 35,35 }, { 1450,90 }, this);
	m_pLv = new LevelIcon(m_pLvTex, { 1450, 320 }, { 20,20 }, { 1450,90 }, this);
	m_pSound = new SoundIcon(m_pSoundTex, { 1450, 420 }, { 20,20 }, { 1450,90 }, this);
	m_pRe = new ReIcon(m_pRETex, { 1450, 530 }, { 20,20 }, { 1450,90 }, this);
	m_pRanking = new RankingIcon(m_pRankingTex, { 1450, 640 }, { 20,20 }, { 1450,90 }, this);

	SceneMgr::GetInst()->GetCurScene()->AddObject(m_pMenu, OBJECT_GROUP::UI);
	SceneMgr::GetInst()->GetCurScene()->AddObject(m_pMain, OBJECT_GROUP::UI);
	SceneMgr::GetInst()->GetCurScene()->AddObject(m_pLv, OBJECT_GROUP::UI);
	SceneMgr::GetInst()->GetCurScene()->AddObject(m_pSound, OBJECT_GROUP::UI);
	SceneMgr::GetInst()->GetCurScene()->AddObject(m_pRe, OBJECT_GROUP::UI);
	SceneMgr::GetInst()->GetCurScene()->AddObject(m_pRanking, OBJECT_GROUP::UI);


	m_pStagePanel = new StagePanel(this);
	m_pRankingPanel = new RankingPanel(this);

}

void GameSceneUI::Update()
{
	if (m_isStageOpen)
		m_pStagePanel->Update();
	if (m_isRankingOpen)
		m_pRankingPanel->Update();
}

void GameSceneUI::Render(HDC _dc)
{
	UIRender(_dc);
	if (m_isStageOpen)
		m_pStagePanel->Render(_dc);
	if (m_isRankingOpen)
		m_pRankingPanel->Render(_dc);
}

void GameSceneUI::Release()
{
	RemoveFontResource(L"Res\\Font\\인천교육소통.ttf");
}

void GameSceneUI::UIRender(HDC _dc)
{
	AddFontResource(L"Res\\Font\\인천교육소통.ttf");
	HFONT hFont = CreateFont(100, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"인천교육소통");
	SelectObject(_dc, hFont);

	SetTextColor(_dc, RGB(0, 0, 0));
	wstring s = to_wstring(DataManager::GetInst()->GetLastStage());
	TextOut(_dc, 25.f, 25.f, s.c_str(), s.size());

	DeleteObject(hFont);
}