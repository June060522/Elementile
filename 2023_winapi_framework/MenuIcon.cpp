#include "pch.h"
#include "MenuIcon.h"
#include "Dotween.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "GameSceneUI.h"
#include "Core.h"
#include "Debug.h"

MenuIcon::MenuIcon(Texture* _tex, Vec2 _pos, Vec2 _scale, GameSceneUI* _pGameSceneUI)
	:Image(_tex,_pos,_scale)
	, m_fAngle(0.f)
{
	m_pGameSceneUI = _pGameSceneUI;
}

void MenuIcon::Function()
{
	if (!m_pGameSceneUI->GetMenuOpen())
	{
		m_pGameSceneUI->SetMenuOpen(!m_pGameSceneUI->GetMenuOpen());
		m_fAngle = 45.f;
	}
	else
	{
		m_pGameSceneUI->SetMenuOpen(!m_pGameSceneUI->GetMenuOpen());
		m_fAngle = 0.f;

	}
}

void MenuIcon::Render(HDC _dc)
{
	Vec2 vCenter = GetPos();
	Vec2 vScale = GetScale();
	POINT tPoint[3] = { 0 };
	float fx, fy, fxDest, fyDest;
	float fRadian = m_fAngle * M_PI / 180.f;
	float cosTheta = cosf(fRadian);
	float sinTheta = sinf(fRadian);
	float width = m_pTex->GetWidth();
	float height = m_pTex->GetHeight();
	for (int i = 0; i < 3; ++i)
	{
		if (i == 0) {
			fx = -width * (GetScale().x / 100.f) / 2.f;
			fy = -height * (GetScale().y / 100.f) / 2.f;
		}
		else if (i == 1) {
			fx = width * (GetScale().x / 100.f) / 2.f;
			fy = -height * (GetScale().y / 100.f) / 2.f;
		}
		else if (i == 2) {
			fx = -width * (GetScale().x / 100.f) / 2.f;
			fy = height * (GetScale().y / 100.f) / 2.f;
		}
		fxDest = fx * cosTheta - fy * sinTheta;
		fyDest = fx * sinTheta + fy * cosTheta;
		tPoint[i].x = (fxDest + vCenter.x);
		tPoint[i].y = (fyDest + vCenter.y);
	}

	HDC _hDC = CreateCompatibleDC(_dc);
	HBITMAP _hWnd = CreateCompatibleBitmap(_dc,
		Core::GetInst()->GetResolution().x, Core::GetInst()->GetResolution().y);
	SelectObject(_hDC, _hWnd);


	float left = GetPos().x - (width * (GetScale().x / 200.f));
	float top = GetPos().y - (height * (GetScale().y / 200.f));

	PatBlt(_hDC, 0, 0, Core::GetInst()->GetResolution().x, Core::GetInst()->GetResolution().y, WHITENESS);
	TransparentBlt(_hDC, left, top,
		width * (GetScale().x / 100.f), height * (GetScale().y / 100.f),
		m_pTex->GetDC(), 0, 0,
		width, height, RGB(255, 0, 255));

	PlgBlt(_dc, tPoint, _hDC,
		left, top,width * (GetScale().x / 100.f), height * (GetScale().y / 100.f), nullptr, 0,0);
}