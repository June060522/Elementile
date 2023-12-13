#include "pch.h"
#include "TileImage.h"
#include "ResMgr.h"
#include "Texture.h"

TileImage::TileImage(const TILE_TYPE& _eType, int _cnt)
	:m_eType(_eType)
{
	m_tileCnt = L"";
	switch (m_eType)
	{
	case TILE_TYPE::WATER:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Water", L"Texture\\water.bmp");
		break;
	case TILE_TYPE::FIRE:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Fire", L"Texture\\fire.bmp");
		break;
	case TILE_TYPE::GRASS:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Grass", L"Texture\\grass.bmp");
		break;
	case TILE_TYPE::FIRELOCK:
		m_pTex = ResMgr::GetInst()->TexLoad(L"LockFire", L"Texture\\lockfire.bmp");
		m_tileCnt = to_wstring(_cnt);
		break;
	case TILE_TYPE::WATERLOCK:
		m_pTex = ResMgr::GetInst()->TexLoad(L"LockWater", L"Texture\\lockwater.bmp");
		m_tileCnt = to_wstring(_cnt);
		break;
	case TILE_TYPE::GRASSLOCK:
		m_pTex = ResMgr::GetInst()->TexLoad(L"LockGrass", L"Texture\\lockgrass.bmp");
		m_tileCnt = to_wstring(_cnt);
		break;
	case TILE_TYPE::TELEPORT:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Teleport", L"Texture\\teleport.bmp");
		break;
	case TILE_TYPE::MOVEL:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Movel", L"Texture\\arrowleft.bmp");
		break;
	case TILE_TYPE::MOVELU:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Movelu", L"Texture\\arrowleftup.bmp");
		break;
	case TILE_TYPE::MOVELD:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Moveld", L"Texture\\arrowleftdown.bmp");
		break;
	case TILE_TYPE::MOVER:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Mover", L"Texture\\arrowright.bmp");
		break;
	case TILE_TYPE::MOVERU:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Moveru", L"Texture\\arrowrightup.bmp");
		break;
	case TILE_TYPE::MOVERD:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Moverd", L"Texture\\arrowrightdown.bmp");
		break;
	case TILE_TYPE::WIND:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Wind", L"Texture\\wind.bmp");
		break;
	case TILE_TYPE::PLUS:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Plus", L"Texture\\plus.bmp");
		break;
	case TILE_TYPE::MINUS:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Minus", L"Texture\\minus.bmp");
		break;
	}
}

TileImage::~TileImage()
{
}

void TileImage::Update()
{
}

void TileImage::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	int Width = m_pTex->GetWidth();
	int Height = m_pTex->GetHeight();
	float centerX = vPos.x;
	float centerY = vPos.y;

	float left = centerX - (Width * (vScale.x / 200));
	float top = centerY - (Height * (vScale.y / 200));

	TransparentBlt(_dc, left, top,
		Width * (vScale.x / 100), Height * (vScale.y / 100),
		m_pTex->GetDC(), 0, 0,
		Width, Height, RGB(255, 0, 255));

	if (m_tileCnt != L"")
	{
		HFONT hFont = CreateFont(50, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"인천교육소통");
		SelectObject(_dc, hFont);
		SetBkMode(_dc, 0);
		TextOut(_dc, left + 30, top + 5, m_tileCnt.c_str(), m_tileCnt.size());
		DeleteObject(hFont);
	}
}