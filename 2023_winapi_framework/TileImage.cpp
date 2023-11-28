#include "pch.h"
#include "TileImage.h"
#include "ResMgr.h"
#include "Texture.h"

TileImage::TileImage(const TILE_TYPE& _eType)
	:m_eType(_eType)
{
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
	case TILE_TYPE::LOCK:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Lock", L"Texture\\lock.bmp");
		break;
	case TILE_TYPE::TELEPORT:
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
		break;
	case TILE_TYPE::END:
		break;
	default:
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
}