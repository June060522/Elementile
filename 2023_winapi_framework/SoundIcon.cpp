#include "pch.h"
#include "SoundIcon.h"
#include "Texture.h"
#include "ResMgr.h"
#include "GameSceneUI.h"

SoundIcon::SoundIcon(Texture* _tex, Vec2 _pos, Vec2 _scale, Vec2 _vmenupos, GameSceneUI* _pGameSceneUI)
	:Image(_tex, _pos, _scale, _vmenupos, _pGameSceneUI)
	,m_pGameSceneUI(_pGameSceneUI)
{
	m_pTex = _tex;
	m_pOffTex = ResMgr::GetInst()->TexLoad(L"SoundOff", L"Texture\\soundoff.bmp");
}

void SoundIcon::Function()
{
	ResMgr::GetInst()->SetSoundVol(!ResMgr::GetInst()->GetSoundVol());
}

void SoundIcon::Render(HDC _dc)
{
	if (m_pGameSceneUI->GetMenuOpen() || m_fTime > 0.f)
	{
		if (ResMgr::GetInst()->GetSoundVol())
		{
			float width = m_pOffTex->GetWidth();
			float height = m_pOffTex->GetHeight();
			float left = GetPos().x - (width * (GetScale().x / 200.f));
			float top = GetPos().y - (height * (GetScale().y / 200.f));
			TransparentBlt(_dc, left, top,
				width * (GetScale().x / 100.f), height * (GetScale().y / 100.f),
				m_pOffTex->GetDC(), 0, 0,
				width, height, RGB(255, 0, 255));
		}
		else
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
}
