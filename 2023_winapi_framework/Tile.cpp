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
		break;
	case TILE_TYPE::FIRE:
		break;
	case TILE_TYPE::GRASS:
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
	m_pTex = ResMgr::GetInst()->TexLoad(L"Tile", L"Texture\\hexagon.bmp");
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
		Width, Height, m_pTex->GetDC(),
		0, 0, Width, Height, RGB(255, 0, 255));

	Component_Render(_dc);
}