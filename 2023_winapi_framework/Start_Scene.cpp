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

int StartdarknessLevel = 255;
float StartelapsedTime = -5.0f;
const float StartdarknessActivationTime = 5.0f;

float t = 0;

void Start_Scene::Init()
{
	for (int i = (int)OBJECT_GROUP::END - 1; i >= 0; --i)
	{
		SceneMgr::GetInst()->GetCurScene()->GetGroupObject((OBJECT_GROUP)i).clear();
	}
	m_vObj.clear();

	m_vObj.push_back(new UIText(Vec2(-85.f, -155.f), L"NoBlend"));
	DataManager::GetInst()->Init();
	int result = AddFontResource(L"Res\\Font\\Font.ttf");

	for (size_t i = 0; i < m_vObj.size(); ++i)
		AddObject(m_vObj[i], OBJECT_GROUP::UI);

	m_Stage = L"Stage";
	m_Stage += to_wstring(DataManager::GetInst()->GetLastStage());
}

void Start_Scene::Update()
{
	StartScreenDoFade();
	Scene::Update();
	t += TimeMgr::GetInst()->GetDT();
	TitleMoveDotween();
	mousePos = KeyMgr::GetInst()->GetMousePos();
	
	if (mousePos.x >= 0 && mousePos.x <= 1920 &&
		mousePos.y >= 0 && mousePos.y <= 1080)
	{
		if (leftMouseButtonState == KEY_STATE::DOWN)
		{
			SceneMgr::GetInst()->LoadScene(L"GameScene");
		}
	}
}

void Start_Scene::Render(HDC _dc)
{
	ObjectRender(_dc);
	HFONT hFont = CreateFont(50, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Merriweather Sans ExtraBold");
	SelectObject(_dc, hFont);
	TextOut(_dc,500,500, m_Stage.c_str(), m_Stage.size());

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