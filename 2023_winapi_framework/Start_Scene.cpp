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
    m_vObj.push_back(new UIText(Vec2(-85.f, -155.f), L"N"));
    m_vObj.push_back(new UIText(Vec2(-90.f, -160.f), L"o"));
    m_vObj.push_back(new UIText(Vec2(-95.f, -165.f), L"B"));
    m_vObj.push_back(new UIText(Vec2(-100.f, -170.f), L"l"));
    m_vObj.push_back(new UIText(Vec2(-105.f, -175.f), L"e"));
    m_vObj.push_back(new UIText(Vec2(-110.f, -180.f), L"n"));
    m_vObj.push_back(new UIText(Vec2(-115.f, -185.f), L"d"));

    DataManager::GetInst()->Init();
    int result = AddFontResource(L"Res\\Font\\Font.ttf");

    for(size_t i=0; i < m_vObj.size(); ++i)
    AddObject(m_vObj[i], OBJECT_GROUP::UI);
}

void Start_Scene::Update()
{
    deltaTime += TimeMgr::GetInst()->GetDT();
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
                AddObject(new Dotween(m_vObj[i], Vec2(200 * (i + 1), 100), 1.f, DOTWEEN_TYPE::MOVE
                ), OBJECT_GROUP::DOTWEEN);
            SceneMgr::GetInst()->GetCurScene()->
                AddObject(new Dotween(m_vObj[i], Vec2(160 * (i + 1), 180), 1.f, 1, DOTWEEN_TYPE::MOVE
                ), OBJECT_GROUP::DOTWEEN);
        }
        t = 0;
    }

    const KEY_STATE& leftMouseButtonState = KeyMgr::GetInst()->GetKey(KEY_TYPE::LBUTTON);
    mousePos = KeyMgr::GetInst()->GetMousePos();

    if (mousePos.x >= 0 && mousePos.x <= 1920 &&
        mousePos.y >= 0 && mousePos.y <= 1080)
    {
        if (leftMouseButtonState == KEY_STATE::DOWN || leftMouseButtonState == KEY_STATE::PRESS)
        {
            SceneMgr::GetInst()->LoadScene(L"GameScene");
        }
    }
}

void Start_Scene::Render(HDC _dc)
{
    Scene::Render(_dc);

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

void Start_Scene::Release()
{
    Scene::Release();

    RemoveFontResource(L"Res\\Font\\Font.ttf");
}
