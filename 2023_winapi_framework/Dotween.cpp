#include "pch.h"
#include "Dotween.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"

Dotween::Dotween(Object* _target, const Vec2& value, const float& _fdelay, DOTWEEN_TYPE _etype)
	:m_target(_target)
	, m_vendval(value)
	, m_ftime(_fdelay)
	, m_fcurtime(0.f)
	, m_etype(_etype)
	, m_fwaittime(0)
{
	SetOriginVal(m_etype);
}

Dotween::Dotween(Object* _target, const Vec2& value, const float& _fdelay, const float& _fwait, DOTWEEN_TYPE _etype)
	:m_target(_target)
	, m_vendval(value)
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
			DoScale();
			break;
		case DOTWEEN_TYPE::FADE:
			DoFade();
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
	//BITMAP bmp;
	//GetObject(hBitmap, sizeof(BITMAP), &bmp);

	//// 이미지 중심 계산
	//float centerX = bmp.bmWidth / 2.0f;
	//float centerY = bmp.bmHeight / 2.0f;

	//// 변환 매트릭스 설정
	//XFORM xForm;
	//xForm.eM11 = cos(angle);
	//xForm.eM12 = -sin(angle);
	//xForm.eM21 = sin(angle);
	//xForm.eM22 = cos(angle);
	//xForm.eDx = centerX - centerX * cos(angle) + centerY * sin(angle);
	//xForm.eDy = centerY - centerX * sin(angle) - centerY * cos(angle);

	//// 변환 적용
	//SetGraphicsMode(hdc, GM_ADVANCED);
	//SetWorldTransform(hdc, &xForm);

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