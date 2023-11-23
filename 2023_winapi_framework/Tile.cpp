#include "pch.h"
#include "Tile.h"
#include "ResMgr.h"
#include "Texture.h"

Tile::Tile(XY _posidx, TILE_TYPE _eType)
	: Object()
	, m_posidx(_posidx)
	, m_pTex(nullptr)
	, m_eType(_eType)
{
	switch (m_eType)
	{
	case TILE_TYPE::WATER:
		m_pTex = ResMgr::GetInst()->TexLoad(L"WaterTile", L"Texture\\waterhexagon.bmp");
		break;
	case TILE_TYPE::FIRE:
		m_pTex = ResMgr::GetInst()->TexLoad(L"FireTile", L"Texture\\firehexagon.bmp");
		break;
	case TILE_TYPE::GRASS:
		m_pTex = ResMgr::GetInst()->TexLoad(L"GrassTile", L"Texture\\grasshexagon.bmp");
		break;
	case TILE_TYPE::GRAY:
		break;
	case TILE_TYPE::TELEPORT:
		break;
	case TILE_TYPE::ForcedMovement:
		break;
	case TILE_TYPE::WIND:
		break;
	case TILE_TYPE::END:
		break;
	}
}

Tile::~Tile()
{
}

void Tile::Update()
{
}

void Tile::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	int Width = m_pTex->GetWidth();
	int Height = m_pTex->GetHeight();

	TransparentBlt(_dc, (int)(vPos.x - vScale.x / 2)
		, (int)(vPos.y - vScale.y / 2),
		Width * (vScale.x / 100), Height * (vScale.y / 100), m_pTex->GetDC(),
		0, 0, Width, Height, RGB(255, 0, 255));

	Component_Render(_dc);
}