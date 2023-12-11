#include "pch.h"
#include "StagePanel.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Core.h"
#include "KeyMgr.h"
#include "GameSceneUI.h"
#include "Debug.h"

StagePanel::StagePanel(GameSceneUI* _pGameSceneUI)
	:m_pGameSceneUI(_pGameSceneUI)
{
	m_pDarkBG = ResMgr::GetInst()->TexLoad(L"DarkBack", L"Texture\\darkBG.bmp");
	m_pBack = ResMgr::GetInst()->TexLoad(L"BackButton", L"Texture\\back.bmp");
}

void StagePanel::Update()
{
	if (KeyMgr::GetInst()->GetKey(KEY_TYPE::LBUTTON) == KEY_STATE::DOWN)
	{
		POINT mousePos;
		Vec2 leftTop;
		Vec2 rightBottom;
		mousePos = KeyMgr::GetInst()->GetMousePos();
		leftTop = { 50, 750 };
		rightBottom = { 150,850 };
		if (mousePos.x >= leftTop.x && mousePos.x <= rightBottom.x &&
			mousePos.y >= leftTop.y && mousePos.y <= rightBottom.y)
		{
			m_pGameSceneUI->SetStagePenalOpen(false);
		}
	}
}

void StagePanel::Render(HDC _dc)
{
	float width = m_pDarkBG->GetWidth();
	float height = m_pDarkBG->GetHeight();
	Vec2 vScale = {200, 200};
	Vec2 vPos = { (int)Core::GetInst()->GetResolution().x / 2, (int)Core::GetInst()->GetResolution().y / 2 };
	float left = vPos.x - (width * (vScale.x / 200.f));
	float top = vPos.y - (height * (vScale.y / 200.f));
	TransparentBlt(_dc, left, top,
		width * (vScale.x / 100.f), height * (vScale.y / 100.f),
		m_pDarkBG->GetDC(), 0, 0,
		width, height, RGB(255, 0, 255));

	width = m_pBack->GetWidth();
	height = m_pBack->GetHeight();
	vScale = { 15, 15 };
	vPos = { 100, 800 };
	left = vPos.x - (width * (vScale.x / 200.f));
	top = vPos.y - (height * (vScale.y / 200.f));
	TransparentBlt(_dc, left, top,
		width * (vScale.x / 100.f), height * (vScale.y / 100.f),
		m_pBack->GetDC(), 0, 0,
		width, height, RGB(255, 0, 255));
}