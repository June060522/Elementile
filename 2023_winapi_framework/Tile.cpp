#include "pch.h"
#include "Tile.h"
#include "ResMgr.h"
#include "Texture.h"

Tile::Tile(XY _posidx, TILE_TYPE _eType, int _cnt)
	: Object()
	, m_posidx(_posidx)
	, m_pTex(nullptr)
	, m_eType(_eType)
	, m_cnt(_cnt)
{
	switch (m_eType)
	{
	case TILE_TYPE::WATER:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Water Tile", L"Texture\\waterhexagon.bmp");
		break;
	case TILE_TYPE::FIRE:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Fire Tile", L"Texture\\firehexagon.bmp");
		break;
	case TILE_TYPE::GRASS:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Grass Tile", L"Texture\\grasshexagon.bmp");
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

}