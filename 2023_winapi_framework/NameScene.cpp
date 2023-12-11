#include "pch.h"
#include "Core.h"
#include "KeyMgr.h"
#include "UIText.h"
#include "DataManager.h"
#include "ResMgr.h"
#include "NameScene.h"
#include "SceneMgr.h"
#include "TimeMgr.h"
#include "Scene.h";
#include "Dotween.h";



int NamedarknessLevel = 255;
float NameelapsedTime = -5.0f;
const float NamedarknessActivationTime = 5.0f;

void NameScene::Init()
{
    m_string1 = new UIText(Vec2(-700.f, 300.f), L"June");
    AddObject(m_string1, OBJECT_GROUP::UI);
    m_string2 = new UIText(Vec2(800.f, -300.f), L" & ");
    AddObject(m_string2, OBJECT_GROUP::UI);
    m_string3 = new UIText(Vec2(1600.f, 300.f), L"Min");
    AddObject(m_string3, OBJECT_GROUP::UI);
    DataManager::GetInst()->Init();
    int result = AddFontResource(L"Res\\Font\\Font.ttf");
    SceneMgr::GetInst()->GetCurScene()->
        AddObject(new Dotween(m_string1, Vec2((float)GET_WINSIZE.x / 2 - 370, (float)GET_WINSIZE.y / 2 - 123), 1.8f, DOTWEEN_TYPE::MOVE
        ), OBJECT_GROUP::DOTWEEN);
    SceneMgr::GetInst()->GetCurScene()->
        AddObject(new Dotween(m_string2, Vec2((float)GET_WINSIZE.x / 2 - 50, (float)GET_WINSIZE.y / 2 - 123), 1.2f, 1.5f, DOTWEEN_TYPE::MOVE
        ), OBJECT_GROUP::DOTWEEN);
    SceneMgr::GetInst()->GetCurScene()->
        AddObject(new Dotween(m_string3, Vec2((float)GET_WINSIZE.x / 2 + 125, (float)GET_WINSIZE.y / 2 - 123), 1.5f, 2.1f, DOTWEEN_TYPE::MOVE
        ), OBJECT_GROUP::DOTWEEN);
}

void NameScene::Update()
{
     // 실제 deltaTime을 얻기 위해 이를 대체하세요
    deltaTime += TimeMgr::GetInst()->GetDT();
    NameelapsedTime += deltaTime;

    if (NameelapsedTime <= 300.0f && NamedarknessLevel < 300)
    {
        NamedarknessLevel -= 1;
    }

    Scene::Update();
}

void NameScene::Render(HDC _dc)
{
    Scene::Render(_dc);

    RECT rcClient;
    GetClientRect(Core::GetInst()->GetHwnd(), &rcClient);

    // 폰트 적용 및 제목 생성
    HFONT hFont = CreateFont(200, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
        CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Merriweather Sans ExtraBold");
    SelectObject(_dc, hFont);

    NamedarknessLevel = max(NamedarknessLevel, 0);
    COLORREF bgColor = RGB(255 - NamedarknessLevel, 255 - NamedarknessLevel, 255 - NamedarknessLevel);
    HBRUSH hBrush = CreateSolidBrush(bgColor);
    FillRect(_dc, &rcClient, hBrush);
    DeleteObject(hBrush);

    if (deltaTime > 6.2f)
    {
        ResMgr::GetInst()->Play(L"BGM");
        SceneMgr::GetInst()->LoadScene(L"StartScene");
    }


    SetTextColor(_dc, RGB(0, 0, 0));
    SetBkMode(_dc, TRANSPARENT);
    Scene::Render(_dc);

    DeleteObject(hFont);
}

void NameScene::Release()
{
    Scene::Release();

    RemoveFontResource(L"Res\\Font\\Font.ttf");
}


