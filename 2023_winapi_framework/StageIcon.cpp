#include "pch.h"
#include "StageIcon.h"
#include "ResMgr.h"
#include "StagePanel.h"
#include "Texture.h"
#include "DataManager.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "Debug.h"

StageIcon::StageIcon(Vec2 _vPos, Vec2 _vScale, int _iStage, StagePanel* _pStagePanel)
{
	SetPos(_vPos);
	SetScale(_vScale);
	m_iStage = _iStage;
	m_pStagePanel = _pStagePanel;

	m_pLevelBorder = ResMgr::GetInst()->TexLoad(L"LevelBorder", L"Texture\\levelborder.bmp");
	m_pLevelBorderX = ResMgr::GetInst()->TexLoad(L"LevelBorderX", L"Texture\\levelborderx.bmp");
}

void StageIcon::Update()
{
	POINT mousePos;
	Vec2 leftTop;
	Vec2 rightBottom;
	mousePos = KeyMgr::GetInst()->GetMousePos();
	leftTop = { ((m_iStage - 1) % 10 + 1) * 80 - 30 + 300, ((m_iStage - 1) / 10) * 80 - 30 + 70 };
	rightBottom = { ((m_iStage - 1) % 10 + 1) * 80 + 30 + 300, ((m_iStage - 1) / 10) * 80 + 30 + 70 };
	
	if (mousePos.x >= leftTop.x && mousePos.x <= rightBottom.x &&
		mousePos.y >= leftTop.y && mousePos.y <= rightBottom.y)
	{
		if (m_iStage <= DataManager::GetInst()->GetHighStage())
		{
			DataManager::GetInst()->SetLastStage(m_iStage);
			SceneMgr::GetInst()->LoadScene(L"GameScene");
		}
	}
}

void StageIcon::Render(HDC _dc)
{
	if (m_iStage <= DataManager::GetInst()->GetHighStage())
	{
		float width = m_pLevelBorder->GetWidth();
		float height = m_pLevelBorder->GetHeight();
		Vec2 vScale = GetScale();
		Vec2 vPos = GetPos();
		float left = vPos.x - (width * (vScale.x / 200.f));
		float top = vPos.y - (height * (vScale.y / 200.f));
		TransparentBlt(_dc, left, top,
			width * (vScale.x / 100.f), height * (vScale.y / 100.f),
			m_pLevelBorder->GetDC(), 0, 0,
			width, height, RGB(255, 0, 255));

		HFONT hFont = CreateFont(30, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"인천교육소통");
		SelectObject(_dc, hFont);
		SetBkMode(_dc, 0);
		wstring s = to_wstring(m_iStage);
		TextOut(_dc, vPos.x - 6 * s.length(), vPos.y - 15, s.c_str(), s.length());
		DeleteObject(hFont);
	}
	else
	{
		float width = m_pLevelBorderX->GetWidth();
		float height = m_pLevelBorderX->GetHeight();
		Vec2 vScale = GetScale();
		Vec2 vPos = GetPos();
		float left = vPos.x - (width * (vScale.x / 200.f));
		float top = vPos.y - (height * (vScale.y / 200.f));
		TransparentBlt(_dc, left, top,
			width * (vScale.x / 100.f), height * (vScale.y / 100.f),
			m_pLevelBorderX->GetDC(), 0, 0,
			width, height, RGB(255, 0, 255));
	}
}