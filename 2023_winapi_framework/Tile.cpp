#include "pch.h"
#include "Tile.h"
#include "ResMgr.h"
#include "Texture.h"
#include "TileImage.h"
#include "SelectManager.h"

Tile::Tile(XY _posidx, TILE_TYPE _eType, int _cnt)
	: Object()
	, m_posidx(_posidx)
	, m_pTex(nullptr)
	, m_eType(_eType)
	, m_cnt(_cnt)
	, m_islight(true)
{
	switch (m_eType)
	{
	case TILE_TYPE::WATER:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Water Tile", L"Texture\\waterhexagon.bmp");
		m_pTexDark = ResMgr::GetInst()->TexLoad(L"Water Tile Dark", L"Texture\\waterhexagondark.bmp");
		break;
	case TILE_TYPE::FIRE:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Fire Tile", L"Texture\\firehexagon.bmp");
		m_pTexDark = ResMgr::GetInst()->TexLoad(L"Fire Tile Dark", L"Texture\\firehexagondark.bmp");
		break;
	case TILE_TYPE::GRASS:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Grass Tile", L"Texture\\grasshexagon.bmp");
		m_pTexDark = ResMgr::GetInst()->TexLoad(L"Grass Tile Dark", L"Texture\\grasshexagondark.bmp");
		break;
	case TILE_TYPE::LOCK:
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
	Tile* tempTile = SelectManager::GetInst()->GetSelectTile();

	if (tempTile != nullptr && tempTile != this)
	{
		if (CanGo(tempTile))
		{
			m_islight = true;
		}
		else
		{
			m_islight = false;
		}
	}
	else
	{
		m_islight = true;
	}
}

void Tile::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	int Width = m_pTex->GetWidth();
	int Height = m_pTex->GetHeight();

	if (m_islight)
	{
		TransparentBlt(_dc, (int)(vPos.x - vScale.x / 2)
			, (int)(vPos.y - vScale.y / 2),
			Width * (vScale.x / 100), Height * (vScale.y / 100), m_pTex->GetDC(),
			0, 0, Width, Height, RGB(255, 0, 255));
	}
	else
	{
		TransparentBlt(_dc, (int)(vPos.x - vScale.x / 2)
			, (int)(vPos.y - vScale.y / 2),
			Width * (vScale.x / 100), Height * (vScale.y / 100), m_pTexDark->GetDC(),
			0, 0, Width, Height, RGB(255, 0, 255));
	}

	for (size_t i = 0; i < m_tilevec.size(); ++i)
	{
		m_tilevec[i]->Render(_dc);
	}
}

void Tile::AddImage(const int& _cnt, const TILE_TYPE& _type)
{
	Vec2 pos;
	Vec2 scale;
	switch (_cnt) // 그릴 이미지 갯수 일단 5개까지만
	{
	case 1:
	{
		pos = Vec2(GetPos().x + 50, GetPos().y + 45);
		scale = Vec2(13, 13);
		AddVec(scale, pos, _type);
	}
	break;
	case 2:
	{
		scale = Vec2(10, 10);
		pos = Vec2(GetPos().x + 80, GetPos().y + 50);
		AddVec(scale, pos, _type);

		pos = Vec2(GetPos().x + 30, GetPos().y + 50);
		AddVec(scale, pos, _type);
	}
	break;
	case 3:
	{
		scale = Vec2(8, 8);
		Vec2 midPos = Vec2(GetPos().x + 60, GetPos().y + 57);
		float radius = 27.0f;
		for (int i = 0; i < 3; i++)
		{
			float angle = i * (2 * M_PI / 3.0f) + M_PI / 6.0f;

			pos.x = midPos.x + radius * cos(angle);
			pos.y = midPos.y + radius * sin(angle);
			AddVec(scale, pos, _type);

		}
	}
	break;
	case 4:
	{
		float middis = 20.f;
		Vec2 midPos = Vec2(GetPos().x + 65, GetPos().y + 55);
		scale = Vec2(7, 7);

		pos.x = midPos.x + middis;
		pos.y = midPos.y + middis;
		AddVec(scale, pos, _type);

		pos.x = midPos.x + middis;
		pos.y = midPos.y - middis;
		AddVec(scale, pos, _type);

		pos.x = midPos.x - middis;
		pos.y = midPos.y + middis;
		AddVec(scale, pos, _type);

		pos.x = midPos.x - middis;
		pos.y = midPos.y - middis;
		AddVec(scale, pos, _type);
	}
	break;
	case 5:
	{
		scale = Vec2(7, 7);
		Vec2 midPos = Vec2(GetPos().x + 60, GetPos().y + 57);

		float radius = 28.0f;

		for (int i = 0; i < 5; i++)
		{
			float angle = (i * (2 * M_PI / 5.0f)) + M_PI / 2.f;

			pos.x = midPos.x + radius * cos(angle);
			pos.y = midPos.y + radius * sin(-angle);

			AddVec(scale, pos, _type);
		}
	}
	break;
	default:
		assert(_cnt);
		break;
	}
}

void Tile::AddVec(const Vec2& _vScale, const Vec2& _vPos, const TILE_TYPE& _type)
{
	TileImage* _tileImage = new TileImage(_type);
	_tileImage->SetPos(_vPos);
	_tileImage->SetScale(_vScale);
	m_tilevec.push_back(_tileImage);
}

const bool Tile::CanGo(Tile* _temptile)
{
#pragma region 인접한 타일인지 검사
	int difX = _temptile->GetposIdx().xidx - m_posidx.xidx;
	int difY = _temptile->GetposIdx().yidx - m_posidx.yidx;
	if (_temptile->GetposIdx().yidx % 2 == 0)
	{
		//(y - 1, x - 1)  (y - 1, x)
		//(y,     x - 1)  (y,     x)  (y, x + 1)
		//(y + 1, x - 1)  (y + 1, x)
		if (difX == -1 || difX == 0)
		{
			if(!(difY == 1 || difY == 0 || difY == -1))
				return false;
		}
		else if (difX == 1)
		{
			if (difY != 0)
				return false;
		}
		else
			return false;
	}
	else
	{
		//(y - 1, x - 1)  (y - 1, x)
		//(y,     x - 1)  (y,     x)  (y, x + 1)
		//(y + 1, x - 1)  (y + 1, x)
		if (difX == 1 || difX == 0)
		{
			if (!(difY == 1 || difY == 0 || difY == -1))
				return false;
		}
		else if (difX == -1)
		{
			if (difY != 0)
				return false;
		}
		else
			return false;
	}
#pragma endregion

#pragma region 이동가능한 속성인지 검사
	switch (_temptile->GetType())
	{
	case TILE_TYPE::WATER:
	case TILE_TYPE::FIRE:
	case TILE_TYPE::GRASS:
	{
		if (_temptile->GetType() != m_eType || _temptile->GetCnt() != m_cnt)
			return false;
	}
		break;
	case TILE_TYPE::LOCK:
		break;
	case TILE_TYPE::TELEPORT:
		break;
	case TILE_TYPE::ForcedMovement:
		break;
	case TILE_TYPE::WIND:
		break;
	}
#pragma endregion

	return true;
}

