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
	m_pDarkBG	= ResMgr::GetInst()->TexLoad(L"WhiteBack", L"Texture\\WhiteBG.bmp");
	m_pBack		= ResMgr::GetInst()->TexLoad(L"BackButton", L"Texture\\back.bmp");

	m_pFire		= ResMgr::GetInst()->TexLoad(L"Fire", L"Texture\\fire.bmp");
	m_pWater	= ResMgr::GetInst()->TexLoad(L"Water", L"Texture\\water.bmp");
	m_pGrass	= ResMgr::GetInst()->TexLoad(L"Grass", L"Texture\\grass.bmp");
	m_pWind		= ResMgr::GetInst()->TexLoad(L"Wind", L"Texture\\wind.bmp");
	m_pArrowRU	= ResMgr::GetInst()->TexLoad(L"Moveru", L"Texture\\arrowrightup.bmp");
	m_pArrowRD	= ResMgr::GetInst()->TexLoad(L"Moverd", L"Texture\\arrowrightdown.bmp");
	m_pArrowR	= ResMgr::GetInst()->TexLoad(L"Mover", L"Texture\\arrowright.bmp");
	m_pArrowL	= ResMgr::GetInst()->TexLoad(L"Movel", L"Texture\\arrowleft.bmp");
	m_pLockF	= ResMgr::GetInst()->TexLoad(L"LockFire1", L"Texture\\lockfire1.bmp");
	m_pLockW	= ResMgr::GetInst()->TexLoad(L"LockWater1", L"Texture\\lockwater1.bmp");
	m_pLockG	= ResMgr::GetInst()->TexLoad(L"LockGrass1", L"Texture\\lockgrass1.bmp");
	m_pPlus		= ResMgr::GetInst()->TexLoad(L"Plus", L"Texture\\plus.bmp");
	m_pMinus	= ResMgr::GetInst()->TexLoad(L"Minus", L"Texture\\minus.bmp");
	m_pTeleport	= ResMgr::GetInst()->TexLoad(L"Teleport", L"Texture\\teleport.bmp");
}

void GameInfoPanel::Render(HDC _dc)
{
	HFONT hFont = CreateFont(50, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"인천교육소통");
	SelectObject(_dc, hFont);
	
	BGRender(_dc);
	ExplainRender(_dc);
	TexRender(_dc);

	DeleteObject(hFont);
}

void GameInfoPanel::Update()
{
	BGUpdate();
}

void GameInfoPanel::ExplainRender(HDC _dc)
{
	TextOut(_dc, 440, 100, L"마우스 클릭으로 타일을 선택할 수 있습니다.",24);
	TextOut(_dc, 500, 150, L"모든 타일을 제거하면 승리합니다!",18);
	wstring help = L"";
	switch (DataManager::GetInst()->GetLastStage())
	{
	case 1:
		help = L"서로 다른 속성을 합칠 수 있습니다.";
		break;
	case 2:
		help = L"물과 불을 합치기 위해서는 물의 갯수가 많아야 합니다.";
		break;
	case 3:
		help = L"불과 풀을 합치기 위해서는 불의 갯수가 많아야 합니다.";
		break;
	case 4:
		help = L"풀과 물을 합치기 위해서는 풀의 갯수가 많아야 합니다.";
		break;
	case 5:
		help = L"같은 속성을 합치기 위해서는 갯수가 같아야 합니다.";
		break;
	case 6:
		help = L"자물쇠를 풀기 위해서는 색과 구멍의 수와 갯수가 같은 원소가 필요합니다.";
		break;
	}
		TextOut(_dc, 420, 700, help.c_str(), help.size());

}

void GameInfoPanel::BGRender(HDC _dc)
{
	{
		BLENDFUNCTION blendFunc;
		blendFunc.BlendOp = AC_SRC_OVER;
		blendFunc.BlendFlags = 0;
		blendFunc.SourceConstantAlpha = 255;
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

void GameInfoPanel::TexRender(HDC _dc)
{
	{
		Vec2 vPos = { 750,300 };
		Vec2 vScale = {20,20};
		int Width = m_pFire->GetWidth();
		int Height = m_pFire->GetHeight();
		float centerX = vPos.x;
		float centerY = vPos.y;

		float left = centerX - (Width * (vScale.x / 200));
		float top = centerY - (Height * (vScale.y / 200));

		TransparentBlt(_dc, left, top,
			Width * (vScale.x / 100), Height * (vScale.y / 100),
			m_pFire->GetDC(), 0, 0,
			Width, Height, RGB(255, 0, 255));
	}
	{
		Vec2 vPos = { 950,550 };
		Vec2 vScale = { 20,20 };
		int Width = m_pGrass->GetWidth();
		int Height = m_pGrass->GetHeight();
		float centerX = vPos.x;
		float centerY = vPos.y;

		float left = centerX - (Width * (vScale.x / 200));
		float top = centerY - (Height * (vScale.y / 200));

		TransparentBlt(_dc, left, top,
			Width * (vScale.x / 100), Height * (vScale.y / 100),
			m_pGrass->GetDC(), 0, 0,
			Width, Height, RGB(255, 0, 255));
	}
	{
		Vec2 vPos = { 550,550 };
		Vec2 vScale = { 20,20 };
		int Width = m_pWater->GetWidth();
		int Height = m_pWater->GetHeight();
		float centerX = vPos.x;
		float centerY = vPos.y;

		float left = centerX - (Width * (vScale.x / 200));
		float top = centerY - (Height * (vScale.y / 200));

		TransparentBlt(_dc, left, top,
			Width * (vScale.x / 100), Height * (vScale.y / 100),
			m_pWater->GetDC(), 0, 0,
			Width, Height, RGB(255, 0, 255));
	}
	{
		Vec2 vPos = { 750,450 };
		Vec2 vScale = { 20,20 };
		int Width = m_pWind->GetWidth();
		int Height = m_pWind->GetHeight();
		float centerX = vPos.x;
		float centerY = vPos.y;

		float left = centerX - (Width * (vScale.x / 200));
		float top = centerY - (Height * (vScale.y / 200));

		TransparentBlt(_dc, left, top,
			Width * (vScale.x / 100), Height * (vScale.y / 100),
			m_pWind->GetDC(), 0, 0,
			Width, Height, RGB(255, 0, 255));
	}
	{
		Vec2 vPos = { 650,425 };
		Vec2 vScale = { 20,20 };
		int Width = m_pArrowRU->GetWidth();
		int Height = m_pArrowRU->GetHeight();
		float centerX = vPos.x;
		float centerY = vPos.y;

		float left = centerX - (Width * (vScale.x / 200));
		float top = centerY - (Height * (vScale.y / 200));

		TransparentBlt(_dc, left, top,
			Width * (vScale.x / 100), Height * (vScale.y / 100),
			m_pArrowRU->GetDC(), 0, 0,
			Width, Height, RGB(255, 0, 255));
	}
	{
		Vec2 vPos = { 850,425 };
		Vec2 vScale = { 20,20 };
		int Width = m_pArrowRD->GetWidth();
		int Height = m_pArrowRD->GetHeight();
		float centerX = vPos.x;
		float centerY = vPos.y;

		float left = centerX - (Width * (vScale.x / 200));
		float top = centerY - (Height * (vScale.y / 200));

		TransparentBlt(_dc, left, top,
			Width * (vScale.x / 100), Height * (vScale.y / 100),
			m_pArrowRD->GetDC(), 0, 0,
			Width, Height, RGB(255, 0, 255));
	}
	{
		Vec2 vPos = { 750,550 };
		Vec2 vScale = { 20,20 };
		int Width = m_pArrowL->GetWidth();
		int Height = m_pArrowL->GetHeight();
		float centerX = vPos.x;
		float centerY = vPos.y;

		float left = centerX - (Width * (vScale.x / 200));
		float top = centerY - (Height * (vScale.y / 200));

		TransparentBlt(_dc, left, top,
			Width * (vScale.x / 100), Height * (vScale.y / 100),
			m_pArrowL->GetDC(), 0, 0,
			Width, Height, RGB(255, 0, 255));
	}
	{
		Vec2 vPos = { 750,225 };
		Vec2 vScale = { 10,10 };
		int Width = m_pLockF->GetWidth();
		int Height = m_pLockF->GetHeight();
		float centerX = vPos.x;
		float centerY = vPos.y;

		float left = centerX - (Width * (vScale.x / 200));
		float top = centerY - (Height * (vScale.y / 200));

		TransparentBlt(_dc, left, top,
			Width * (vScale.x / 100), Height * (vScale.y / 100),
			m_pLockF->GetDC(), 0, 0,
			Width, Height, RGB(255, 0, 255));
	}
	{
		Vec2 vPos = { 1000,625 };
		Vec2 vScale = { 10,10 };
		int Width = m_pLockG->GetWidth();
		int Height = m_pLockG->GetHeight();
		float centerX = vPos.x;
		float centerY = vPos.y;

		float left = centerX - (Width * (vScale.x / 200));
		float top = centerY - (Height * (vScale.y / 200));

		TransparentBlt(_dc, left, top,
			Width * (vScale.x / 100), Height * (vScale.y / 100),
			m_pLockG->GetDC(), 0, 0,
			Width, Height, RGB(255, 0, 255));
	}
	{
		Vec2 vPos = { 500,625 };
		Vec2 vScale = { 10,10 };
		int Width = m_pLockW->GetWidth();
		int Height = m_pLockW->GetHeight();
		float centerX = vPos.x;
		float centerY = vPos.y;

		float left = centerX - (Width * (vScale.x / 200));
		float top = centerY - (Height * (vScale.y / 200));

		TransparentBlt(_dc, left, top,
			Width * (vScale.x / 100), Height * (vScale.y / 100),
			m_pLockW->GetDC(), 0, 0,
			Width, Height, RGB(255, 0, 255));
	}
	{
		Vec2 vPos = { 250,275 };
		Vec2 vScale = { 20,20 };
		int Width = m_pArrowR->GetWidth();
		int Height = m_pArrowR->GetHeight();
		float centerX = vPos.x;
		float centerY = vPos.y;

		float left = centerX - (Width * (vScale.x / 200));
		float top = centerY - (Height * (vScale.y / 200));

		TransparentBlt(_dc, left, top,
			Width * (vScale.x / 100), Height * (vScale.y / 100),
			m_pArrowR->GetDC(), 0, 0,
			Width, Height, RGB(255, 0, 255));
	}
	{
		Vec2 vPos = { 1250,275 };
		Vec2 vScale = { 20,20 };
		int Width = m_pPlus->GetWidth();
		int Height = m_pPlus->GetHeight();
		float centerX = vPos.x;
		float centerY = vPos.y;

		float left = centerX - (Width * (vScale.x / 200));
		float top = centerY - (Height * (vScale.y / 200));

		TransparentBlt(_dc, left, top,
			Width * (vScale.x / 100), Height * (vScale.y / 100),
			m_pPlus->GetDC(), 0, 0,
			Width, Height, RGB(255, 0, 255));
	}
	{
		Vec2 vPos = { 1250,500 };
		Vec2 vScale = { 20,20 };
		int Width = m_pMinus->GetWidth();
		int Height = m_pMinus->GetHeight();
		float centerX = vPos.x;
		float centerY = vPos.y;

		float left = centerX - (Width * (vScale.x / 200));
		float top = centerY - (Height * (vScale.y / 200));

		TransparentBlt(_dc, left, top,
			Width * (vScale.x / 100), Height * (vScale.y / 100),
			m_pMinus->GetDC(), 0, 0,
			Width, Height, RGB(255, 0, 255));
	}
	{
		Vec2 vPos = { 250,500 };
		Vec2 vScale = { 20,20 };
		int Width = m_pTeleport->GetWidth();
		int Height = m_pTeleport->GetHeight();
		float centerX = vPos.x;
		float centerY = vPos.y;

		float left = centerX - (Width * (vScale.x / 200));
		float top = centerY - (Height * (vScale.y / 200));

		TransparentBlt(_dc, left, top,
			Width * (vScale.x / 100), Height * (vScale.y / 100),
			m_pTeleport->GetDC(), 0, 0,
			Width, Height, RGB(255, 0, 255));
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
