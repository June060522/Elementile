#include "pch.h"
#include "Start_Scene.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "Dotween.h"
#include "Core.h"
#include "KeyMgr.h"
#include "DataManager.h"
#include "ResMgr.h"
#include "TimeMgr.h"
#include "UIText.h"
#include "ResMgr.h"
#include "Texture.h"

int StartdarknessLevel = 255;
float StartelapsedTime = -5.0f;
const float StartdarknessActivationTime = 5.0f;

float t = 2.5f;
        
void Start_Scene::Init()
{
	for (int i = (int)OBJECT_GROUP::END - 1; i >= 0; --i)
	{
		SceneMgr::GetInst()->GetCurScene()->GetGroupObject((OBJECT_GROUP)i).clear();
	}
	m_vObj.clear();

	m_vObj.push_back(new UIText(Vec2(493.f, 100.f), L"No Blend"));
	DataManager::GetInst()->Init();
	int result = AddFontResource(L"Res\\Font\\Font.ttf");

	for (size_t i = 0; i < m_vObj.size(); ++i)
		AddObject(m_vObj[i], OBJECT_GROUP::UI);

	m_Stage = L"Stage ";
	m_Stage += to_wstring(DataManager::GetInst()->GetLastStage());

	m_pSoundOn = ResMgr::GetInst()->TexLoad(L"Sound", L"Texture\\sound.bmp");
	m_pSoundOff = ResMgr::GetInst()->TexLoad(L"SoundOff", L"Texture\\soundoff.bmp");
	m_pDoorOpen = ResMgr::GetInst()->TexLoad(L"Door Open", L"Texture\\dooropen.bmp");
	m_pDoorClose = ResMgr::GetInst()->TexLoad(L"Door Close", L"Texture\\doorclose.bmp");
}

void Start_Scene::Update()
{
	StartScreenDoFade();
	Scene::Update();
	t += TimeMgr::GetInst()->GetDT();
	TitleMoveDotween();
	mousePos = KeyMgr::GetInst()->GetMousePos();

	if (leftMouseButtonState == KEY_STATE::DOWN)
	{
		if (mousePos.x >= 25 && mousePos.x <= 125
			&& mousePos.y >= 25 && mousePos.y <= 125)
		{
			ResMgr::GetInst()->SetSoundVol(!ResMgr::GetInst()->GetSoundVol());
		}
		else if (mousePos.x >= 1445 && mousePos.x <= 1505 &&
			mousePos.y >= 30 && mousePos.y <= 125)
		{
			ExitProcess(0 );
		}
		else
			SceneMgr::GetInst()->LoadScene(L"GameScene");
	}
	ResMgr::GetInst()->Update();
}

void Start_Scene::Render(HDC _dc)
{
	ObjectRender(_dc);
	IconRender(_dc);
	HFONT hFont = CreateFont(50, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Merriweather Sans ExtraBold");
	SelectObject(_dc, hFont);
	TextOut(_dc, 700, 500, m_Stage.c_str(), m_Stage.size());

	DeleteObject(hFont);
}

void Start_Scene::Release()
{
	Scene::Release();

	RemoveFontResource(L"Res\\Font\\Font.ttf");
}

void Start_Scene::StartScreenDoFade()
{
	deltaTime += TimeMgr::GetInst()->GetDT();
	StartelapsedTime += deltaTime;

	if (StartelapsedTime <= 300.0f && StartdarknessLevel < 300)
	{
		StartdarknessLevel -= 1;
	}
}

void Start_Scene::TitleMoveDotween()
{
	if (t >= 2.5f)
	{
		int x;
		for (size_t i = 0; i < m_vObj.size(); ++i)
		{
			SceneMgr::GetInst()->GetCurScene()->
				AddObject(new Dotween(m_vObj[i], Vec2(188 * (i + 1) / 2 + 400, 100), 1.f, DOTWEEN_TYPE::MOVE
				), OBJECT_GROUP::DOTWEEN);
			SceneMgr::GetInst()->GetCurScene()->
				AddObject(new Dotween(m_vObj[i], Vec2(177 * (i + 1) / 2 + 400, 120), 1.2f, 1, DOTWEEN_TYPE::MOVE
				), OBJECT_GROUP::DOTWEEN);
		}
		t = 0;
	}
}

void Start_Scene::ObjectRender(HDC _dc)
{
	RECT rcClient;
	GetClientRect(Core::GetInst()->GetHwnd(), &rcClient);

	// 迄飘 利侩 棺 力格 积己
	HFONT hFont = CreateFont(200, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Merriweather Sans ExtraBold");
	SelectObject(_dc, hFont);

	StartdarknessLevel = max(StartdarknessLevel, 0);
	COLORREF bgColor = RGB(255 - StartdarknessLevel, 255 - StartdarknessLevel, 255 - StartdarknessLevel);
	HBRUSH hBrush = CreateSolidBrush(bgColor);
	FillRect(_dc, &rcClient, hBrush);
	DeleteObject(hBrush);

	SetTextColor(_dc, RGB(0, 0, 0));
	SetBkMode(_dc, TRANSPARENT);
	Scene::Render(_dc);
	DeleteObject(hFont);
}

void Start_Scene::IconRender(HDC _dc)
{
	if (!ResMgr::GetInst()->GetSoundVol())
	{
		float width = m_pSoundOn->GetWidth();
		float height = m_pSoundOn->GetHeight();
		Vec2 pos = { 75,75 };
		Vec2 scale = { 20,20 };
		float left = pos.x - (width * (scale.x / 200.f));
		float top = pos.y - (height * (scale.y / 200.f));
		TransparentBlt(_dc, left, top,
			width * (scale.x / 100.f), height * (scale.y / 100.f),
			m_pSoundOn->GetDC(), 0, 0,
			width, height, RGB(255, 0, 255));
	}
	else
	{
		float width = m_pSoundOff->GetWidth();
		float height = m_pSoundOff->GetHeight();
		Vec2 pos = { 75,75 };
		Vec2 scale = { 20,20 };
		float left = pos.x - (width * (scale.x / 200.f));
		float top = pos.y - (height * (scale.y / 200.f));
		TransparentBlt(_dc, left, top,
			width * (scale.x / 100.f), height * (scale.y / 100.f),
			m_pSoundOff->GetDC(), 0, 0,
			width, height, RGB(255, 0, 255));
	}
	POINT mousePos = KeyMgr::GetInst()->GetMousePos();
	if (mousePos.x >= 1445 && mousePos.x <= 1505 &&
		mousePos.y >= 30 && mousePos.y <= 125)
	{
		float width = m_pDoorOpen->GetWidth();
		float height = m_pDoorOpen->GetHeight();
		Vec2 pos = { 1475,75 };
		Vec2 scale = { 20,20 };
		float left = pos.x - (width * (scale.x / 200.f));
		float top = pos.y - (height * (scale.y / 200.f));
		TransparentBlt(_dc, left, top,
			width * (scale.x / 100.f), height * (scale.y / 100.f),
			m_pDoorOpen->GetDC(), 0, 0,
			width, height, RGB(255, 0, 255));
	}
	else
	{
		float width = m_pDoorClose->GetWidth();
		float height = m_pDoorClose->GetHeight();
		Vec2 pos = { 1475,75 };
		Vec2 scale = { 20,20 };
		float left = pos.x - (width * (scale.x / 200.f));
		float top = pos.y - (height * (scale.y / 200.f));
		TransparentBlt(_dc, left, top,
			width * (scale.x / 100.f), height * (scale.y / 100.f),
			m_pDoorClose->GetDC(), 0, 0,
			width, height, RGB(255, 0, 255));
	}
}