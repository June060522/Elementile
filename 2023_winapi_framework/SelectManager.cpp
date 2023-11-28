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

void SelectManager::Init()
{
	m_selectTile = nullptr;
	m_fRadius = 70.f;
	m_fCorrectionX = 75.f;
	m_fCorrectionY = 75.f;
}

const void SelectManager::TileClick(const vector<Object*>& _tilegroup)
{
	if (KeyMgr::GetInst()->GetKey(KEY_TYPE::LBUTTON) == KEY_STATE::DOWN)
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
						if (a->GetGo())
						{
							Merge(m_selectTile, a);
							m_selectTile = nullptr;
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

const void SelectManager::Merge(Tile* _from, Tile* _to)
{
	Tile* newTile = _to;
	newTile->SetCnt(1);
	auto& tilevec = SceneMgr::GetInst()->GetCurScene()->GetGroupObject(OBJECT_GROUP::TILE);
	for (int i = 0; i < tilevec.size();)
	{
		if (tilevec[i] == _from || tilevec[i] == _to)
			tilevec.erase(tilevec.begin() + i);
		else
			++i;
	}
	newTile->ResetVec();
	newTile->AddImage(newTile->GetCnt(), newTile->GetType());
	SceneMgr::GetInst()->GetCurScene()->AddObject(newTile, OBJECT_GROUP::TILE);
}
