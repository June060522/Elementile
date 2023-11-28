#include "pch.h"
#include "Tile.h"
#include "ResMgr.h"
#include "Texture.h"
#include "TileImage.h"
#include "SelectManager.h"
#include"Core.h"

Tile::Tile(XY _posidx, TILE_TYPE _eType, int _cnt)
	: Object()
	, m_posidx(_posidx)
	, m_pTex(nullptr)
	, m_eType(_eType)
	, m_cnt(_cnt)
	, m_eState(TILE_STATE::DEFAULT)
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
	case TILE_TYPE::MOVEL:
	case TILE_TYPE::MOVELU:
	case TILE_TYPE::MOVELD:
	case TILE_TYPE::MOVER:
	case TILE_TYPE::MOVERU:
	case TILE_TYPE::MOVERD:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Arrow Tile", L"Texture\\arrowhexagon.bmp");
		m_pTexDark = ResMgr::GetInst()->TexLoad(L"Arrow Tile Dark", L"Texture\\arrowhexagondark.bmp");
		break;
	case TILE_TYPE::WIND:
		break;
	case TILE_TYPE::END:
		break;
	}
	m_pBGDark = ResMgr::GetInst()->TexLoad(L"BGDark", L"Texture\\bgtiledark.bmp");
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
			m_eState = TILE_STATE::CANMOVE;
		}
		else
		{
			m_eState = TILE_STATE::NOTSELECT;
		}
	}
	else
	{
		m_eState = TILE_STATE::DEFAULT;
	}
}

void Tile::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	//¥�� Ÿ���ΰ� �� ���Ƽ� �ϳ���
	int Width = m_pTex->GetWidth();
	int Height = m_pTex->GetHeight();

	float centerX = vPos.x + 73;
	float centerY = vPos.y + 80;

	float left = centerX - (Width * (vScale.x / 200));
	float top = centerY - (Height * (vScale.y / 200));

	if (m_eState == TILE_STATE::DEFAULT || m_eState == TILE_STATE::CANMOVE)
	{
		TransparentBlt(_dc, left,top,
			Width * (vScale.x / 100),Height * (vScale.y / 100),
			m_pTex->GetDC(),0,0,
			Width,Height,RGB(255, 0, 255));
	}
	else
	{
		if (m_pTexDark != nullptr)
		{
			TransparentBlt(_dc, left, top,
				Width * (vScale.x / 100), Height * (vScale.y / 100),
				m_pTexDark->GetDC(), 0, 0,
				Width, Height, RGB(255, 0, 255));
		}
		TransparentBlt(_dc, left, top,
			Width * (vScale.x / 100), Height * (vScale.y / 100),
			m_pBGDark->GetDC(), 0, 0,
			Width, Height, RGB(255, 0, 255));
	}

	for (size_t i = 0; i < m_tilevec.size(); ++i)
	{
		m_tilevec[i]->SetPos(Vec2(
			GetPos().x + m_tilevec[i]->GetCorrectionPosX()
			, GetPos().y + m_tilevec[i]->GetCorrectionPosY()));
		m_tilevec[i]->SetScale(Vec2(
			GetScale().x - m_tilevec[i]->GetCorrectionScaleX()
			, GetScale().y - m_tilevec[i]->GetCorrectionScaleY()));
		m_tilevec[i]->Render(_dc);
	}
}

void Tile::AddImage(const int& _cnt, const TILE_TYPE& _type)
{
	Vec2 pos;
	Vec2 scale;
	switch (_cnt) // �׸� �̹��� ���� �ϴ� 5��������
	{
	case 1:
	{
		pos = Vec2(GetPos().x + 75, GetPos().y + 75);
		scale = Vec2(13, 13);
		AddVec(scale, pos, _type);
	}
	break;
	case 2:
	{
		scale = Vec2(10, 10);
		pos = Vec2(GetPos().x + 100, GetPos().y + 80);
		AddVec(scale, pos, _type);

		pos = Vec2(GetPos().x + 50, GetPos().y + 80);
		AddVec(scale, pos, _type);
	}
	break;
	case 3:
	{
		scale = Vec2(8, 8);
		Vec2 midPos = Vec2(GetPos().x + 75, GetPos().y + 80);
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
		Vec2 midPos = Vec2(GetPos().x + 75, GetPos().y + 78);
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
		Vec2 midPos = Vec2(GetPos().x +75, GetPos().y + 78);

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
	_tileImage->SetCorrectionPosX(_vPos.x - GetPos().x);
	_tileImage->SetCorrectionPosY(_vPos.y - GetPos().y);
	_tileImage->SetCorrectionScaleX(GetScale().x - _vScale.x);
	_tileImage->SetCorrectionScaleY(GetScale().y - _vScale.y);
	m_tilevec.push_back(_tileImage);
}

const bool Tile::CanGo(Tile* _temptile)
{
#pragma region ������ Ÿ������ �˻�
	int difX = _temptile->GetposIdx().xidx - m_posidx.xidx;
	int difY = _temptile->GetposIdx().yidx - m_posidx.yidx;
	if (_temptile->GetposIdx().yidx % 2 == 0)
	{
		//(y - 1, x - 1)  (y - 1, x)
		//(y,     x - 1)  (y,     x)  (y, x + 1)
		//(y + 1, x - 1)  (y + 1, x)
		if (difX == -1 || difX == 0)
		{
			if (!(difY == 1 || difY == 0 || difY == -1))
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

#pragma region �̵������� �Ӽ�,Ÿ������ �˻�
	switch (_temptile->GetType())
	{
	case TILE_TYPE::WATER:
	case TILE_TYPE::FIRE:
	case TILE_TYPE::GRASS:
	{
		if (_temptile->GetType() != m_eType || _temptile->GetCnt() != m_cnt)
		{
			if(m_eType == TILE_TYPE::WATER ||
				m_eType == TILE_TYPE::FIRE ||
				m_eType == TILE_TYPE::GRASS )
			return false;
		}

	}
	break;
	default:
		if (m_eType == TILE_TYPE::WATER ||
			m_eType == TILE_TYPE::FIRE ||
			m_eType == TILE_TYPE::GRASS)
			return false;
		break;
	}
#pragma endregion

#pragma region ������ 5���̸����� �˻�
	if (GetCnt() >= 5)
		return false;
#pragma endregion
	return true;
}

