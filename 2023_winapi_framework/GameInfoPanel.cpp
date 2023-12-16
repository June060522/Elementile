#include "pch.h"
#include "GameInfoPanel.h"
#include "ResMgr.h"
#include "KeyMgr.h"
#include "Texture.h"
#include "Core.h"
#include "GameSceneUI.h"
#include "DataManager.h"

GameInfoPanel::GameInfoPanel(GameSceneUI* _pGameSceneUI)
{
	m_pGameSceneUI = _pGameSceneUI;
	m_pDarkBG = ResMgr::GetInst()->TexLoad(L"DarkBack", L"Texture\\darkBG.bmp");
	m_pBack = ResMgr::GetInst()->TexLoad(L"BackButton", L"Texture\\back.bmp");
}

void GameInfoPanel::Render(HDC _dc)
{
	BGRender(_dc);
}

void GameInfoPanel::Update()
{
	BGUpdate();
}

void GameInfoPanel::ExplainRender(HDC _dc)
{
}

void GameInfoPanel::BGRender(HDC _dc)
{
	{
		BLENDFUNCTION blendFunc;
		blendFunc.BlendOp = AC_SRC_OVER;
		blendFunc.BlendFlags = 0;
		blendFunc.SourceConstantAlpha = 180;
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

}

void GameInfoPanel::BGUpdate()
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
			m_pGameSceneUI->SetInfoPenalOpen(false);
		}

	}
}
