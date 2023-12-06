#include "pch.h"
#include "Dotween.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Texture.h"

Dotween::Dotween(Object* _target, const Vec2& value, const float& _fdelay, DOTWEEN_TYPE _etype)
	: m_target(_target)
	, m_vendval(value)
	, m_ftime(_fdelay)
	, m_fcurtime(0.f)
	, m_etype(_etype)
	, m_fwaittime(0)
	, m_tex(nullptr)
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
	, m_tex(nullptr)
{
	SetOriginVal(m_etype);
}
Dotween::Dotween(Object* _target, const float& value, const float& _fdelay, Texture* _tex, DOTWEEN_TYPE _etype)
	: m_target(_target)
	, m_fendval(value)
	, m_ftime(_fdelay)
	, m_fcurtime(0.f)
	, m_etype(_etype)
	, m_fwaittime(0)
	, m_tex(nullptr)
{
	m_tex = _tex;
	SetOriginVal(m_etype);
}
Dotween::Dotween(Object* _target, const float& value, const float& _fdelay, Texture* _tex, const float& _fwait, DOTWEEN_TYPE _etype)
	: m_target(_target)
	, m_fendval(value)
	, m_ftime(_fdelay)
	, m_fcurtime(0.f)
	, m_etype(_etype)
	, m_fwaittime(_fwait)
	, m_tex(nullptr)
{
	m_tex = _tex;
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
	case DOTWEEN_TYPE::ROTATE:
		m_voriginval = m_target->GetScale();
		break;
	case DOTWEEN_TYPE::FADE:
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
			DoRotate();
			break;
		case DOTWEEN_TYPE::FADE:
			DoFade();
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
			case DOTWEEN_TYPE::ROTATE:
				break;
			case DOTWEEN_TYPE::FADE:
				break;
			case DOTWEEN_TYPE::END:
				break;
			default:
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

void Dotween::DoRotate()
{
	float centerX = m_tex->GetWidth() / 2.f;
	float centerY = m_tex->GetHeight() / 2.f;
	float angle = m_foriginval + (m_fendval - m_foriginval) * (m_fcurtime / m_ftime);
	// 변환 매트릭스 설정
	XFORM xForm;
	xForm.eM11 = cos(angle);
	xForm.eM12 = -sin(angle);
	xForm.eM21 = sin(angle);
	xForm.eM22 = cos(angle);
	xForm.eDx = centerX - centerX * cos(angle) + centerY * sin(angle);
	xForm.eDy = centerY - centerX * sin(angle) - centerY * cos(angle);

	// 변환 적용
	SetGraphicsMode(m_tex->GetDC(), GM_ADVANCED);
	SetWorldTransform(m_tex->GetDC(), &xForm);
}

void Dotween::DoFade()
{
	//BITMAP bmp;
	//GetObject(hBitmap, sizeof(BITMAP), &bmp);

	//// 이미지 정보 설정
	//BLENDFUNCTION blendFunc;
	//blendFunc.BlendOp = AC_SRC_OVER;
	//blendFunc.BlendFlags = 0;
	//blendFunc.SourceConstantAlpha = alpha;  // 알파값 설정 (0: 투명, 255: 불투명)
	//blendFunc.AlphaFormat = AC_SRC_ALPHA;

	//// 이미지 그리기
	//AlphaBlend(hdc, 0, 0, bmp.bmWidth, bmp.bmHeight,
	//	CreateCompatibleDC(hdc), 0, 0, bmp.bmWidth, bmp.bmHeight,
	//	blendFunc);
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