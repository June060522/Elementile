#include "pch.h"
#include "Dotween.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"

Dotween::Dotween(Object* _target, const Vec2& value, const float& _fdelay, DOTWEEN_TYPE _etype)
	:m_target(_target)
	,m_vendval(value)
	,m_ftime(_fdelay)
	,m_fcurtime(0.f)
	,m_etype(_etype)
{
	switch (m_etype)
	{
	case DOTWEEN_TYPE::MOVE:
		m_voriginval = m_target->GetPos();
		break;
	case DOTWEEN_TYPE::SCALE:
		m_voriginval = m_target->GetScale();
		break;
	}
}

void Dotween::Update()
{
	m_fcurtime += TimeMgr::GetInst()->GetDT();
	switch (m_etype)
	{
	case DOTWEEN_TYPE::MOVE:
		DoMove();
		break;
	case DOTWEEN_TYPE::SCALE:
		DoScale();
		break;
	}
	if (m_fcurtime >= m_ftime)
	{
		for (size_t i = 0; i < SceneMgr::GetInst()->GetCurScene()
			->GetGroupObject(OBJECT_GROUP::DOTWEEN).size();)
		{
			if (SceneMgr::GetInst()->GetCurScene()->GetGroupObject(OBJECT_GROUP::DOTWEEN)[i] == this)
				SceneMgr::GetInst()->GetCurScene()
				->GetGroupObject(OBJECT_GROUP::DOTWEEN).erase(
				SceneMgr::GetInst()->GetCurScene()->GetGroupObject(OBJECT_GROUP::DOTWEEN).begin() + i);
			else
				++i;

		}
	}
}

void Dotween::Render(HDC _dc)
{
}

void Dotween::DoMove()
{
	m_target->SetPos(
		Vec2(m_voriginval.x + (m_vendval.x - m_voriginval.x) * (m_fcurtime / m_ftime)
		, m_voriginval.y + (m_vendval.y - m_voriginval.y) * (m_fcurtime / m_ftime)));
}

void Dotween::DoScale()
{
}
