#include "pch.h"
#include "RankingPanel.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Core.h"
#include "KeyMgr.h"
#include "GameSceneUI.h"

RankingPanel::RankingPanel(GameSceneUI* _pGameSceneUI)
{
	m_pGameSceneUI = _pGameSceneUI;

	m_pDarkBG = ResMgr::GetInst()->TexLoad(L"DarkBack", L"Texture\\darkBG.bmp");
	m_pBack = ResMgr::GetInst()->TexLoad(L"BackButton", L"Texture\\back.bmp");
	m_pFirstPlace = ResMgr::GetInst()->TexLoad(L"First Price", L"Texture\\firstplace.bmp");
	m_pSecondPlace = ResMgr::GetInst()->TexLoad(L"Second Price", L"Texture\\secondplace.bmp");
	m_pThirdPlace = ResMgr::GetInst()->TexLoad(L"Third Price", L"Texture\\thirdplace.bmp");
}

void RankingPanel::Update()
{
	if (KeyMgr::GetInst()->GetKey(KEY_TYPE::LBUTTON) == KEY_STATE::DOWN)
	{
		POINT mousePos;
		Vec2 leftTop;
		Vec2 rightBottom;
		mousePos = KeyMgr::GetInst()->GetMousePos();
		leftTop = { 50, 750 };
		rightBottom = { 150,850 };
		if (mousePos.x >= leftTop.x && mousePos.x <= rightBottom.x &&
			mousePos.y >= leftTop.y && mousePos.y <= rightBottom.y)
		{
			ResMgr::GetInst()->Play(L"Button");
			m_pGameSceneUI->SetRankingPenalOpen(false);
		}

	}
}

void RankingPanel::Render(HDC _dc)
{
	BGRender(_dc);
	BackIconRender(_dc);
	RankingRender(_dc);
}

void RankingPanel::BGRender(HDC _dc)
{
	BLENDFUNCTION blendFunc;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.BlendFlags = 0;
	blendFunc.SourceConstantAlpha = 230;
	blendFunc.AlphaFormat = AC_SRC_ALPHA;

	float width = m_pDarkBG->GetWidth();
	float height = m_pDarkBG->GetHeight();
	Vec2 vScale = { 300, 200 };
	Vec2 vPos = { (int)Core::GetInst()->GetResolution().x / 2, (int)Core::GetInst()->GetResolution().y / 2 };
	float left = vPos.x - (width * (vScale.x / 200.f));
	float top = vPos.y - (height * (vScale.y / 200.f));

	AlphaBlend(_dc, left, top, width * (vScale.x / 100.f), height * (vScale.y / 100.f),
		m_pDarkBG->GetDC(), 0, 0, width, height, blendFunc);
}

void RankingPanel::BackIconRender(HDC _dc)
{
	float width = m_pBack->GetWidth();
	float height = m_pBack->GetHeight();
	Vec2 vScale = { 15, 15 };
	Vec2 vPos = { 75, 800 };
	float left = vPos.x - (width * (vScale.x / 200.f));
	float top = vPos.y - (height * (vScale.y / 200.f));
	TransparentBlt(_dc, left, top,
		width * (vScale.x / 100.f), height * (vScale.y / 100.f),
		m_pBack->GetDC(), 0, 0,
		width, height, RGB(255, 0, 255));
}

void RankingPanel::RankingRender(HDC _dc)
{
	{
		Vec2 vPos = {725, 300};
		Vec2 vScale = {35,35};
		int Width = m_pFirstPlace->GetWidth();
		int Height = m_pFirstPlace->GetHeight();

		float centerX = vPos.x + 73;
		float centerY = vPos.y + 80;

		float left = centerX - (Width * (vScale.x / 200));
		float top = centerY - (Height * (vScale.y / 200));
		wstring id = L"이름 : ";
		wstring score = L"스테이지 : ";
		id += m_pGameSceneUI->GetId(0);
		score += to_wstring(m_pGameSceneUI->GetScore(0));
		TransparentBlt(_dc, left, top + 5,
			Width * (vScale.x / 100), Height * (vScale.y / 100),
			m_pFirstPlace->GetDC(), 0, 0,
			Width, Height, RGB(255, 0, 255));

		TextOut(_dc, vPos.x, vPos.y + 200,
			id.c_str(),
			id.size());
		TextOut(_dc, vPos.x, vPos.y + 250,
			score.c_str(),
			score.size());
	}

	{
		Vec2 vPos = { 725, 300 };
		Vec2 vScale = { 35,35 };
		int Width = m_pFirstPlace->GetWidth();
		int Height = m_pFirstPlace->GetHeight();

		float centerX = vPos.x + 73;
		float centerY = vPos.y + 80;

		float left = centerX - (Width * (vScale.x / 200));
		float top = centerY - (Height * (vScale.y / 200));
		wstring id = L"이름 : ";
		wstring score = L"스테이지 : ";
		id += m_pGameSceneUI->GetId(0);
		score += to_wstring(m_pGameSceneUI->GetScore(0));
		TransparentBlt(_dc, left, top + 5,
			Width * (vScale.x / 100), Height * (vScale.y / 100),
			m_pFirstPlace->GetDC(), 0, 0,
			Width, Height, RGB(255, 0, 255));

		TextOut(_dc, vPos.x, vPos.y + 200,
			id.c_str(),
			id.size());
		TextOut(_dc, vPos.x, vPos.y + 250,
			score.c_str(),
			score.size());
	}


	{
		Vec2 vPos = { 725, 300 };
		Vec2 vScale = { 35,35 };
		int Width = m_pFirstPlace->GetWidth();
		int Height = m_pFirstPlace->GetHeight();

		float centerX = vPos.x + 73;
		float centerY = vPos.y + 80;

		float left = centerX - (Width * (vScale.x / 200));
		float top = centerY - (Height * (vScale.y / 200));
		wstring id = L"이름 : ";
		wstring score = L"스테이지 : ";
		id += m_pGameSceneUI->GetId(0);
		score += to_wstring(m_pGameSceneUI->GetScore(0));
		TransparentBlt(_dc, left, top + 5,
			Width * (vScale.x / 100), Height * (vScale.y / 100),
			m_pFirstPlace->GetDC(), 0, 0,
			Width, Height, RGB(255, 0, 255));

		TextOut(_dc, vPos.x, vPos.y + 200,
			id.c_str(),
			id.size());
		TextOut(_dc, vPos.x, vPos.y + 250,
			score.c_str(),
			score.size());
	}
}