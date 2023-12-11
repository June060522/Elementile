#include "pch.h"
#include "Dotween.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Texture.h"
#include "Debug.h"

Dotween::Dotween(Object* _target, const Vec2& value, const float& _fdelay, DOTWEEN_TYPE _etype)
	: m_target(_target)
	, m_vendval(value)
	, m_ftime(_fdelay)
	, m_fcurtime(0.f)
	, m_etype(_etype)
	, m_fwaittime(0)
	, m_pTex(nullptr)
{
	SetOriginVal(m_etype);
}

Dotween::Dotween(Object* _target, const Vec2& value, const float& _fdelay, const float& _fwait, DOTWEEN_TYPE _etype)
	: m_target(_target)
	, m_vendval(value)
	, m_ftime(_fdelay)
	, m_fcurtime(0.f)
	, m_etype(_etype)
	, m_fwaittime(_fwait)
	, m_pTex(nullptr)
{
	SetOriginVal(m_etype);
}

Dotween::Dotween(Texture* _target, const float& value, const float& originvalue, const float& _fdelay, DOTWEEN_TYPE _etype)
	: m_pTex(_target)
	, m_foriginval(originvalue)
	, m_fendval(value)
	, m_ftime(_fdelay)
	, m_fcurtime(0.f)
	, m_etype(_etype)
{
	SetOriginVal(m_etype);
}
Dotween::Dotween(Texture* _target, const float& value, const float& originvalue, const float& _fdelay, const float& _fwait, DOTWEEN_TYPE _etype)
	: m_pTex(_target)
	, m_fendval(value)
	, m_foriginval(originvalue)
	, m_ftime(_fdelay)
	, m_fcurtime(0.f)
	, m_etype(_etype)
	, m_fwaittime(_fwait)
{
	SetOriginVal(m_etype);
}
void Dotween::SetOriginVal(DOTWEEN_TYPE _etype)
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
	m_fwaittime -= TimeMgr::GetInst()->GetDT();
	if (m_fwaittime <= 0)
	{
		m_isBegin = true;
		m_fcurtime += TimeMgr::GetInst()->GetDT();
		switch (m_etype)
		{
		case DOTWEEN_TYPE::MOVE:
			DoMove();
			break;
		case DOTWEEN_TYPE::SCALE:
			DoScale();
			break;
		case DOTWEEN_TYPE::ROTATE:
			break;
		case DOTWEEN_TYPE::FADE:

			break;
		}
		if (m_target == nullptr)
			DoKill();
		if (m_fcurtime >= m_ftime)
		{
			switch (m_etype)
			{
			case DOTWEEN_TYPE::MOVE:
				m_target->SetPos(m_vendval);
				break;
			case DOTWEEN_TYPE::SCALE:
				m_target->SetScale(m_vendval);
				break;
			}

			for (size_t i = 0; i < GET_OBJECT(OBJECT_GROUP::DOTWEEN).size();)
			{
				if (GET_OBJECT(OBJECT_GROUP::DOTWEEN)[i] == this)
					GET_OBJECT(OBJECT_GROUP::DOTWEEN).erase(GET_OBJECT(OBJECT_GROUP::DOTWEEN).begin() + i);
				else
					++i;
			}
		}
	}
	else
		SetOriginVal(m_etype);
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
	m_target->SetScale(
		Vec2(m_voriginval.x + (m_vendval.x - m_voriginval.x) * (m_fcurtime / m_ftime)
			, m_voriginval.y + (m_vendval.y - m_voriginval.y) * (m_fcurtime / m_ftime)));
}

void Dotween::DoKill()
{
	for (size_t i = 0; i < GET_OBJECT(OBJECT_GROUP::DOTWEEN).size();)
	{
		Dotween* dotween = (Dotween*)(GET_OBJECT(OBJECT_GROUP::DOTWEEN)[i]);
		if (dotween->GetTarget() == this->GetTarget()
			&& dotween->GetPlay() && dotween->GetType() == this->GetType())
		{
			GET_OBJECT(OBJECT_GROUP::DOTWEEN).erase(GET_OBJECT(OBJECT_GROUP::DOTWEEN).begin() + i);
		}
	}
}