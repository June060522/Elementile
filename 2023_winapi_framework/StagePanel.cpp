#include "pch.h"
#include "StagePanel.h"
#include "ResMgr.h"
#include "Texture.h"
#include "Core.h"
#include "KeyMgr.h"
#include "GameSceneUI.h"
#include "Debug.h"
#include "StageIcon.h"

StagePanel::StagePanel(GameSceneUI* _pGameSceneUI)
	:m_pGameSceneUI(_pGameSceneUI)
{
	m_pDarkBG = ResMgr::GetInst()->TexLoad(L"DarkBack", L"Texture\\darkBG.bmp");
	m_pBack = ResMgr::GetInst()->TexLoad(L"BackButton", L"Texture\\back.bmp");

	for (int i = 0; i < 10; i++)
	{
		for (int j = 1; j <= 10; j++)
		{
			m_vecStageIcon.push_back(new StageIcon(
				{80 * j + 300, 80 * (i + 1) - 10}, {10,10}, i * 10 + j, this));
		}
	}
}

void StagePanel::Update()
{
	if (KeyMgr::GetInst()->GetKey(KEY_TYPE::LBUTTON) == KEY_STATE::DOWN)
	{
		for (auto i : m_vecStageIcon)
			i->Update();

		POINT mousePos;
		Vec2 leftTop;
		Vec2 rightBottom;
		mousePos = KeyMgr::GetInst()->GetMousePos();
		leftTop = { 50, 750 };
		rightBottom = { 150,850 };
		if (mousePos.x >= leftTop.x && mousePos.x <= rightBottom.x &&
			mousePos.y >= leftTop.y && mousePos.y <= rightBottom.y)
		{
			ResMgr::GetInst()->Play(L"Button");
			m_pGameSceneUI->SetStagePenalOpen(false);
		}

	}
}

void StagePanel::Render(HDC _dc)
{
	BGRender(_dc);
	BackIconRender(_dc);
	StageRender(_dc);
}

void StagePanel::BGRender(HDC _dc)
{
	BLENDFUNCTION blendFunc;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.BlendFlags = 0;
	blendFunc.SourceConstantAlpha = 128;
	blendFunc.AlphaFormat = AC_SRC_ALPHA;

	float width = m_pDarkBG->GetWidth();
	float height = m_pDarkBG->GetHeight();
	Vec2 vScale = { 300, 200 };
	Vec2 vPos = { (int)Core::GetInst()->GetResolution().x / 2, (int)Core::GetInst()->GetResolution().y / 2 };
	float left = vPos.x - (width * (vScale.x / 200.f));
	float top = vPos.y - (height * (vScale.y / 200.f));

	AlphaBlend(_dc, left, top, width * (vScale.x / 100.f), height * (vScale.y / 100.f),
		m_pDarkBG->GetDC(), 0, 0, width, height, blendFunc);
}

void StagePanel::BackIconRender(HDC _dc)
{
	float width = m_pBack->GetWidth();
	float height = m_pBack->GetHeight();
	Vec2 vScale = { 15, 15 };
	Vec2 vPos = { 75, 800 };
	float left = vPos.x - (width * (vScale.x / 200.f));
	float top = vPos.y - (height * (vScale.y / 200.f));
	TransparentBlt(_dc, left, top,
		width * (vScale.x / 100.f), height * (vScale.y / 100.f),
		m_pBack->GetDC(), 0, 0,
		width, height, RGB(255, 0, 255));
}

void StagePanel::StageRender(HDC _dc)
{
	for (auto i : m_vecStageIcon)
		i->Render(_dc);
}