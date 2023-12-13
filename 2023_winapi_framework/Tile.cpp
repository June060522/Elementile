#include "pch.h"
#include "Tile.h"
#include "ResMgr.h"
#include "Texture.h"
#include "TileImage.h"
#include "SelectManager.h"
#include "SceneMgr.h"
#include "Scene.h"
#include"Core.h"
#include "KeyMgr.h"
#include "Debug.h"

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
	case TILE_TYPE::PLUS:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Water Tile", L"Texture\\waterhexagon.bmp");
		m_pTexDark = ResMgr::GetInst()->TexLoad(L"Water Tile Dark", L"Texture\\waterhexagondark.bmp");
		break;
	case TILE_TYPE::FIRE:
	case TILE_TYPE::MINUS:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Fire Tile", L"Texture\\firehexagon.bmp");
		m_pTexDark = ResMgr::GetInst()->TexLoad(L"Fire Tile Dark", L"Texture\\firehexagondark.bmp");
		break;
	case TILE_TYPE::GRASS:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Grass Tile", L"Texture\\grasshexagon.bmp");
		m_pTexDark = ResMgr::GetInst()->TexLoad(L"Grass Tile Dark", L"Texture\\grasshexagondark.bmp");
		break;
	case TILE_TYPE::FIRELOCK:
	case TILE_TYPE::WATERLOCK:
	case TILE_TYPE::GRASSLOCK:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Black Tile", L"Texture\\lockhexagon.bmp");
		m_pTexDark = ResMgr::GetInst()->TexLoad(L"Black Dark", L"Texture\\lockhexagon.bmp");
		break;
	case TILE_TYPE::TELEPORT:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Teleport Tile", L"Texture\\teleporthexagon.bmp");
		m_pTexDark = ResMgr::GetInst()->TexLoad(L"Teleport Dark", L"Texture\\teleporthexagondark.bmp");
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
		m_pTex = ResMgr::GetInst()->TexLoad(L"Wind Tile", L"Texture\\windhexagon.bmp");
		m_pTexDark = ResMgr::GetInst()->TexLoad(L"Wind Tile Dark", L"Texture\\windhexagondark.bmp");
		break;
	}
	m_pBGDark = ResMgr::GetInst()->TexLoad(L"BGDark", L"Texture\\bgtiledark.bmp");
	m_pselect = ResMgr::GetInst()->TexLoad(L"BGSelect", L"Texture\\selecthexagon.bmp");
}

Tile::~Tile()
{
}

void Tile::Update()
{
	Tile* tempTile = SelectManager::GetInst()->GetSelectTile();

	if (tempTile != nullptr && tempTile != this)
	{
		if (CanGo(this))
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

	Vec2 pos = Vec2(GetposIdx().xidx * 128, GetposIdx().yidx * 105);
	if (GetposIdx().yidx % 2 == 1)
	{
		pos.x -= 65;
	}
	pos.x += (float)Core::GetInst()->GetResolution().x / 4.f;
	pos.y += (float)Core::GetInst()->GetResolution().y / 12;
	SetPos(pos);
}

void Tile::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	//짜피 타일인건 다 같아서 하나만
	int Width = m_pTex->GetWidth();
	int Height = m_pTex->GetHeight();

	float centerX = vPos.x + 73;
	float centerY = vPos.y + 80;

	float left = centerX - (Width * (vScale.x / 200));
	float top = centerY - (Height * (vScale.y / 200));

	if (SelectManager::GetInst()->GetSelectTile() == this)
	{
		TransparentBlt(_dc, left, top + 5,
			Width * (vScale.x / 100), Height * (vScale.y / 100),
			m_pselect->GetDC(), 0, 0,
			Width, Height, RGB(255, 0, 255));
	}
	if (m_eState == TILE_STATE::CANMOVE || m_eState == TILE_STATE::DEFAULT)
	{
		TransparentBlt(_dc, left, top,
			Width * (vScale.x / 100), Height * (vScale.y / 100),
			m_pTex->GetDC(), 0, 0,
			Width, Height, RGB(255, 0, 255));
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
	if (_type == TILE_TYPE::FIRE || _type == TILE_TYPE::GRASS || _type == TILE_TYPE::WATER)
		switch (_cnt) // 그릴 이미지 갯수 일단 5개까지만
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
			Vec2 midPos = Vec2(GetPos().x + 75, GetPos().y + 78);

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
	else if (_type == TILE_TYPE::FIRELOCK || _type == TILE_TYPE::GRASSLOCK || _type == TILE_TYPE::WATERLOCK)
	{
		pos = Vec2(GetPos().x + 75, GetPos().y + 75);
		scale = Vec2(13, 13);
		AddVec(scale, pos, _type);
	}
	else
	{
		pos = Vec2(GetPos().x + 75, GetPos().y + 75);
		scale = Vec2(13, 13);
		AddVec(scale, pos, _type);
	}
}

void Tile::AddVec(const Vec2& _vScale, const Vec2& _vPos, const TILE_TYPE& _type)
{
	TileImage* _tileImage = new TileImage(_type, m_cnt);
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
	Tile* selectTile = SelectManager::GetInst()->GetSelectTile();

#pragma region 인접한 타일인지 검사
	int difX = selectTile->GetposIdx().xidx - m_posidx.xidx;
	int difY = selectTile->GetposIdx().yidx - m_posidx.yidx;
	if (selectTile->GetposIdx().yidx % 2 == 0)
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

#pragma region 이동가능한 타일인지 검사
	switch (_temptile->GetType())
	{
	case TILE_TYPE::WATER:
	case TILE_TYPE::FIRE:
	case TILE_TYPE::GRASS:
	{
		if (selectTile->GetType() == _temptile->GetType() && selectTile->GetCnt() != _temptile->GetCnt())
		{
			return false;
		}
	}
	break;
	case TILE_TYPE::FIRELOCK:
		if (!(TILE_TYPE::FIRE == selectTile->GetType() &&
			selectTile->GetCnt() == _temptile->GetCnt()))
		{
			return false;
		}
		break;
	case TILE_TYPE::WATERLOCK:
		if (!(TILE_TYPE::WATER == selectTile->GetType() &&
			selectTile->GetCnt() == _temptile->GetCnt()))
		{
			return false;
		}
		break;
	case TILE_TYPE::GRASSLOCK:
		if (!(TILE_TYPE::GRASS == selectTile->GetType() &&
			selectTile->GetCnt() == _temptile->GetCnt()))
		{
			return false;
		}
		break;
	case TILE_TYPE::WIND:
		if (selectTile->GetType() == TILE_TYPE::GRASSLOCK ||
			selectTile->GetType() == TILE_TYPE::WATERLOCK ||
			selectTile->GetType() == TILE_TYPE::FIRELOCK ||
			selectTile->GetType() == TILE_TYPE::PLUS ||
			selectTile->GetType() == TILE_TYPE::MINUS)
			return false;
		break;
	case TILE_TYPE::PLUS:
	case TILE_TYPE::MINUS:
		if (selectTile->GetType() == TILE_TYPE::GRASSLOCK ||
			selectTile->GetType() == TILE_TYPE::WATERLOCK ||
			selectTile->GetType() == TILE_TYPE::FIRELOCK ||
			selectTile->GetType() == TILE_TYPE::WIND ||
			selectTile->GetType() == TILE_TYPE::PLUS ||
			selectTile->GetType() == TILE_TYPE::MINUS)
			return false;
	}
#pragma endregion

#pragma region 선택된 타일 입장에서 검사
	switch (selectTile->GetType())
	{
	case TILE_TYPE::FIRELOCK:
	case TILE_TYPE::WATERLOCK:
	case TILE_TYPE::GRASSLOCK:
		if (_temptile->GetType() != TILE_TYPE::TELEPORT)
			return false;
		break;
	case TILE_TYPE::TELEPORT:
		return false;
		break;
	case TILE_TYPE::MOVELU:
	case TILE_TYPE::MOVEL:
	case TILE_TYPE::MOVELD:
	case TILE_TYPE::MOVERU:
	case TILE_TYPE::MOVER:
	case TILE_TYPE::MOVERD:
		if (_temptile->GetType() != TILE_TYPE::TELEPORT)
			return false;
		break;
	case TILE_TYPE::WIND:
		if(_temptile->GetType() == TILE_TYPE::GRASSLOCK ||
			_temptile->GetType() == TILE_TYPE::WATERLOCK || 
			_temptile->GetType() == TILE_TYPE::FIRELOCK || 
			_temptile->GetType() == TILE_TYPE::PLUS ||
			_temptile->GetType() == TILE_TYPE::MINUS)
			return false;
	break;
	case TILE_TYPE::PLUS:
	case TILE_TYPE::MINUS:
		if (_temptile->GetType() == TILE_TYPE::GRASSLOCK ||
			_temptile->GetType() == TILE_TYPE::WATERLOCK ||
			_temptile->GetType() == TILE_TYPE::FIRELOCK ||
			_temptile->GetType() == TILE_TYPE::WIND ||
			_temptile->GetType() == TILE_TYPE::PLUS ||
			_temptile->GetType() == TILE_TYPE::MINUS)
			return false;
		break;
	}
#pragma endregion

#pragma region 갯수가 5개미만인지 검사
	if (_temptile->GetCnt() >= 5 || selectTile->GetCnt() >= 5)
		return false;
#pragma endregion

#pragma region 불물풀 속성 검사
	switch (_temptile->GetType())
	{
	case TILE_TYPE::WATER:
		if (selectTile->GetType() == TILE_TYPE::FIRE)
		{
			if (selectTile->GetCnt() > _temptile->GetCnt())
			{
				return false;
			}
		}
		else if (selectTile->GetType() == TILE_TYPE::GRASS)
		{
			if (selectTile->GetCnt() < _temptile->GetCnt())
			{
				return false;
			}
		}
		break;
	case TILE_TYPE::FIRE:
		if (selectTile->GetType() == TILE_TYPE::GRASS)
		{
			if (selectTile->GetCnt() > _temptile->GetCnt())
			{
				return false;
			}
		}
		else if (selectTile->GetType() == TILE_TYPE::WATER)
		{
			if (selectTile->GetCnt() < _temptile->GetCnt())
			{
				return false;
			}
		}
		break;
	case TILE_TYPE::GRASS:
		if (selectTile->GetType() == TILE_TYPE::FIRE)
		{
			if (selectTile->GetCnt() < _temptile->GetCnt())
			{
				return false;
			}
		}
		else if (selectTile->GetType() == TILE_TYPE::WATER)
		{
			if (selectTile->GetCnt() > _temptile->GetCnt())
			{
				return false;
			}
		}
		break;
	}
#pragma endregion

#pragma region 자기자신인지 검사
	if (_temptile->GetposIdx().xidx == selectTile->GetposIdx().xidx
		&& _temptile->GetposIdx().yidx == selectTile->GetposIdx().yidx)
		return false;
#pragma endregion

#pragma region 있는 타일있지 검사
	for (auto i : SceneMgr::GetInst()->GetCurScene()->GetGroupObject(OBJECT_GROUP::TILE))
	{
		Tile* t = (Tile*)i;
		if (t->GetposIdx().xidx == _temptile->GetposIdx().xidx
			&& t->GetposIdx().yidx == _temptile->GetposIdx().yidx)
		{

			switch (t->GetType())
			{
			case TILE_TYPE::WATER:
				if (t->GetCnt() != _temptile->GetCnt()
					&& t->GetType() == _temptile->GetType())
					return false;
				break;
			case TILE_TYPE::FIRE:
				if (t->GetCnt() != _temptile->GetCnt()
					&& t->GetType() == _temptile->GetType())
					return false;
				break;
			case TILE_TYPE::GRASS:
				if (t->GetCnt() != _temptile->GetCnt()
					&& t->GetType() == _temptile->GetType())
					return false;
				break;
			case TILE_TYPE::FIRELOCK:
				if (!(TILE_TYPE::FIRE == selectTile->GetType() &&
					t->GetCnt() == selectTile->GetCnt()))
				{
					return false;
				}
				break;
			case TILE_TYPE::WATERLOCK:
				if (!(TILE_TYPE::WATER == selectTile->GetType() &&
					t->GetCnt() == selectTile->GetCnt()))
				{
					return false;
				}
				break;
			case TILE_TYPE::GRASSLOCK:
				if (!(TILE_TYPE::GRASS == selectTile->GetType() &&
					selectTile->GetCnt() == t->GetCnt()))
				{
					return false;
				}
				break;
			case TILE_TYPE::MOVELU:
			{
				Tile* temptile = FindTile(XY{ (_temptile->GetposIdx().yidx % 2 == 0 ?
					_temptile->GetposIdx().xidx : _temptile->GetposIdx().xidx - 1),
					_temptile->GetposIdx().yidx - 1 });

				if (temptile == nullptr)
					return false;

				if (!CanGo(temptile))
					return false;
			}
			break;
			case TILE_TYPE::MOVEL:
			{
				Tile* temptile = FindTile(XY{ _temptile->GetposIdx().xidx - 1,
					_temptile->GetposIdx().yidx });

				if (temptile == nullptr)
					return false;

				if (!CanGo(temptile))
					return false;
			}
			break;
			case TILE_TYPE::MOVELD:
			{
				Tile* temptile = FindTile(XY{ (_temptile->GetposIdx().yidx % 2 == 0 ?
					_temptile->GetposIdx().xidx : _temptile->GetposIdx().xidx - 1) ,
					_temptile->GetposIdx().yidx + 1 });

				if (temptile == nullptr)
					return false;

				if (!CanGo(temptile))
					return false;
			}
			break;
			case TILE_TYPE::MOVERU:
			{
				Tile* temptile = FindTile(XY{ (_temptile->GetposIdx().yidx % 2 == 0 ?
					_temptile->GetposIdx().xidx + 1 : _temptile->GetposIdx().xidx),
					_temptile->GetposIdx().yidx - 1 });

				if (temptile == nullptr)
					return false;

				if (!CanGo(temptile))
					return false;
			}
			break;
			case TILE_TYPE::MOVER:
			{
				Tile* temptile = FindTile(XY{ _temptile->GetposIdx().xidx + 1,
					_temptile->GetposIdx().yidx });

				if (temptile == nullptr)
					return false;

				if (!CanGo(temptile))
					return false;
			}
			break;
			case TILE_TYPE::MOVERD:
			{
				Tile* temptile = FindTile(XY{ (_temptile->GetposIdx().yidx % 2 == 0 ?
					_temptile->GetposIdx().xidx + 1 : _temptile->GetposIdx().xidx),
					_temptile->GetposIdx().yidx + 1 });

				if (temptile == nullptr)
					return false;

				if (!CanGo(temptile))
					return false;
			}
			break;
			case TILE_TYPE::WIND:
				break;
			}

			return true;
		}
	}
#pragma endregion

	return false;

}

Tile* Tile::FindTile(XY pos)
{
	for (int i = 0; i < GET_OBJECT(OBJECT_GROUP::TILE).size(); ++i)
	{
		Tile* t = (Tile*)GET_OBJECT(OBJECT_GROUP::TILE)[i];
		if (t->GetposIdx().xidx == pos.xidx &&
			t->GetposIdx().yidx == pos.yidx)
		{
			return t;
		}
	}
	return nullptr;
}
