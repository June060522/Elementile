#include "pch.h"
#include "SelectManager.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Object.h"
#include "KeyMgr.h"
#include "Tile.h"
#include "Debug.h"
#include "Core.h"
#include "Dotween.h"
#include "TimeMgr.h"

void SelectManager::Init()
{
	m_selectTile = nullptr;
	m_fRadius = 70.f;
	m_fmovetime = 0.2f;
	m_ftime = m_fmovetime;
	m_canMove = true;
	m_fCorrectionX = 75.f;
	m_fCorrectionY = 75.f;
}

void SelectManager::Update()
{
	m_ftime += TimeMgr::GetInst()->GetDT();
	if (m_ftime >= m_fmovetime)
	{
		if (!m_canMove)
		{
			m_canMove = true;
			Merge();
		}
	}
	else
	{
		m_canMove = false;
	}
}

const void SelectManager::TileClick(const vector<Object*>& _tilegroup)
{
	if (KeyMgr::GetInst()->GetKey(KEY_TYPE::LBUTTON) == KEY_STATE::DOWN && m_canMove)
	{
		Vec2 tileCenterPos;
		Vec2 p1, p2, p3;
		float angle1, angle2;
		m_pMousePos = KeyMgr::GetInst()->GetMousePos();
		for (auto tile : _tilegroup)
		{
			Tile* a = (Tile*)tile;
			tileCenterPos = a->GetPos();
			tileCenterPos.x += m_fCorrectionX;
			tileCenterPos.y += m_fCorrectionY;
			for (int i = 0; i < 6; i++)
			{
				angle1 = (i * (2 * M_PI / 6.0f)) + M_PI / 2.f;
				angle2 = ((i + 1) * (2 * M_PI / 6.0f)) + M_PI / 2.f;

				p1.x = tileCenterPos.x + m_fRadius * cos(angle1);
				p1.y = tileCenterPos.y + m_fRadius * sin(angle1);

				p2.x = tileCenterPos.x + m_fRadius * cos(angle2);
				p2.y = tileCenterPos.y + m_fRadius * sin(angle2);

				p3 = tileCenterPos;

				if (TriangleInPoint(p1, p2, p3, m_pMousePos))
				{
					if (m_selectTile == a)
					{
						m_selectTile = nullptr;
					}
					else if (m_selectTile == nullptr)
					{
						m_selectTile = a;

					}
					else
					{
						if (a->GetState() == TILE_STATE::CANMOVE)
						{
							m_to = a;
							m_ftime = 0;
							SceneMgr::GetInst()->GetCurScene()->
								AddObject(new Dotween(m_selectTile, m_to->GetPos()
									, m_fmovetime, DOTWEEN_TYPE::MOVE), OBJECT_GROUP::DOTWEEN);
						}
						else
						{
							m_selectTile = a;
						}
					}
					return;
				}
			}
		}
	}
}

const bool& SelectManager::TriangleInPoint(Vec2& _p1,
	Vec2& _p2, Vec2& _p3, Vec2& _point)
{
	Vec2 v1 = _p2 - _p1;
	Vec2 v2 = _point - _p1;

	float cross1 = Cross(v1, v2);

	v1 = _p3 - _p2;
	v2 = _point - _p2;

	float cross2 = Cross(v1, v2);

	v1 = _p1 - _p3;
	v2 = _point - _p3;

	float cross3 = Cross(v1, v2);

	if ((cross1 > 0 && cross2 > 0 && cross3 > 0)
		|| (cross1 < 0 && cross2 < 0 && cross3 < 0))
	{
		return true;
	}

	return false;
}

const void SelectManager::Merge()
{
	Vec2 tempScale = m_to->GetScale();
	Tile* newTile = m_to;
	newTile->SetCnt(1);
	auto& tilevec = SceneMgr::GetInst()->GetCurScene()->GetGroupObject(OBJECT_GROUP::TILE);
	for (int i = 0; i < tilevec.size();)
	{
		if (tilevec[i] == m_selectTile || tilevec[i] == m_to)
			tilevec.erase(tilevec.begin() + i);
		else
			++i;
	}
	newTile->ResetVec();
	newTile->AddImage(newTile->GetCnt(), newTile->GetType());
	newTile->SetScale(Vec2(10.f, 10.f));
	SceneMgr::GetInst()->GetCurScene()->AddObject(newTile, OBJECT_GROUP::TILE);
	SceneMgr::GetInst()->GetCurScene()->AddObject(new Dotween(newTile, tempScale, 0.15f,
		DOTWEEN_TYPE::SCALE), OBJECT_GROUP::DOTWEEN);
	m_to = nullptr;
	m_selectTile = nullptr;
}
