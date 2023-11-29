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

int StartdarknessLevel = 255;
float StartelapsedTime = -5.0f;
const float StartdarknessActivationTime = 5.0f;

float t =0;

void Start_Scene::Init()
{
    m_vObj.push_back(new UIText(Vec2(-80.f, -150.f), L"N"));
    m_vObj.push_back(new UIText(Vec2(-80.f, -150.f), L"o"));
    m_vObj.push_back(new UIText(Vec2(-80.f, -150.f), L"B"));
    m_vObj.push_back(new UIText(Vec2(-80.f, -150.f), L"l"));
    m_vObj.push_back(new UIText(Vec2(-80.f, -150.f), L"e"));
    m_vObj.push_back(new UIText(Vec2(-80.f, -150.f), L"n"));
    m_vObj.push_back(new UIText(Vec2(-80.f, -150.f), L"d"));

    DataManager::GetInst()->Init();
    int result = AddFontResource(L"Res\\Font\\Font.ttf");

    for(size_t i=0; i < m_vObj.size(); ++i)
    AddObject(m_vObj[i], OBJECT_GROUP::UI);

    
}

void Start_Scene::Update()
{
    float deltaTime = 0.24f; // 실제 deltaTime을 얻기 위해 이를 대체하세요
    StartelapsedTime += deltaTime;

    if (StartelapsedTime <= 300.0f && StartdarknessLevel < 300)
    {
        StartdarknessLevel -= 1;
    }

    Scene::Update();

    t += TimeMgr::GetInst()->GetDT();
    if (t >= 2)
    {
        for (size_t i = 0; i < m_vObj.size(); ++i)
        {
            SceneMgr::GetInst()->GetCurScene()->
                AddObject(new Dotween(m_vObj[i], Vec2(250, 560), 1.5f, DOTWEEN_TYPE::MOVE
                ), OBJECT_GROUP::DOTWEEN);
            SceneMgr::GetInst()->GetCurScene()->
                AddObject(new Dotween(m_vObj[i], Vec2(250, 660), 1.5f, 1, DOTWEEN_TYPE::MOVE
                ), OBJECT_GROUP::DOTWEEN);
        }
        t = 0;
    }

    
}

void Start_Scene::Render(HDC _dc)
{
    Scene::Render(_dc);

    RECT rcClient;
    GetClientRect(Core::GetInst()->GetHwnd(), &rcClient);

    // 폰트 적용 및 제목 생성
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

void Start_Scene::Release()
{
    Scene::Release();

    RemoveFontResource(L"Res\\Font\\Font.ttf");
}
