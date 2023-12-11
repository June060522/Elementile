#include "pch.h"
#include "Image.h"
#include "Texture.h"
#include "KeyMgr.h"
#include "Debug.h"
#include "GameSceneUI.h"
#include "TimeMgr.h"
#include "Dotween.h"
#include "SceneMgr.h"
#include "Scene.h"

Image::Image(Texture* _tex, Vec2 _pos, Vec2 _scale, Vec2 _vmenupos, GameSceneUI* _pGameSceneUI)
	:m_pTex(_tex)
	,m_pGameSceneUI(_pGameSceneUI)
{
	m_vmenuPos = _vmenupos;
	m_vendPos = _pos;
	m_fDelay = 0.3f;
	m_fTime = 0.f;
	m_ismenuOpen = false;
	SetScale(_scale);
	SetPos(_vmenupos);
}

void Image::Update()
{
	m_fTime -= fDT;
	if (m_ismenuOpen != m_pGameSceneUI->GetMenuOpen())
	{
		if (m_ismenuOpen)
		{
			SceneMgr::GetInst()->GetCurScene()->AddObject(new Dotween(this, m_vmenuPos, m_fDelay, DOTWEEN_TYPE::MOVE), OBJECT_GROUP::DOTWEEN);
		}
		else
		{
			SceneMgr::GetInst()->GetCurScene()->AddObject(new Dotween(this, m_vendPos, m_fDelay, DOTWEEN_TYPE::MOVE), OBJECT_GROUP::DOTWEEN);
		}
		m_ismenuOpen = !m_ismenuOpen;
		m_fTime = m_fDelay;
	}
	if (m_fTime <= 0)
	{
		if (KeyMgr::GetInst()->GetKey(KEY_TYPE::LBUTTON) == KEY_STATE::DOWN && !m_pGameSceneUI->GetStagePenalOpen())
		{
			POINT mousePos;
			Vec2 leftTop;
			Vec2 rightBottom;
			mousePos = KeyMgr::GetInst()->GetMousePos();
			leftTop = { GetPos().x - 35,GetPos().y - 35 };
			rightBottom = { GetPos().x + 35,GetPos().y + 35 };
			if (mousePos.x >= leftTop.x && mousePos.x <= rightBottom.x &&
				mousePos.y >= leftTop.y && mousePos.y <= rightBottom.y)
			{
				Function();
			}
		}
	}
}

void Image::Render(HDC _dc)
{
	if (m_pGameSceneUI->GetMenuOpen() || m_fTime > 0.f)
	{
		float width = m_pTex->GetWidth();
		float height = m_pTex->GetHeight();
		float left = GetPos().x - (width * (GetScale().x / 200.f));
		float top = GetPos().y - (height * (GetScale().y / 200.f));
		TransparentBlt(_dc, left, top,
			width * (GetScale().x / 100.f), height * (GetScale().y / 100.f),
			m_pTex->GetDC(), 0, 0,
			width, height, RGB(255, 0, 255));
	}
}

void Image::Function()
{
}
