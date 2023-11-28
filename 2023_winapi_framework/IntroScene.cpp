#include "pch.h"
#include "IntroScene.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Dotween.h"
#include "DataManager.h"
#include <windows.h>
#include "Button.h"
#include "Core.h"
#include "TimeMgr.h"
#include "UIText.h"

int darknessLevel = 0;
float elapsedTime = -5.0f; 
const float darknessActivationTime = 5.0f;  

void IntroScene::Init()
{   
    m_string = new UIText(Vec2(-80.f, -150.f), L"난쟁2");
    DataManager::GetInst()->Init();
    AddObject(m_string, OBJECT_GROUP::UI);
    //AddObject(new Button(), OBJECT_GROUP::UI);
    //int result = AddFontResource(L"Res\\Font\\Font.ttf");
    int title = AddFontResource(L"Res\\Font\\인천교육소통.ttf");

    SceneMgr::GetInst()->GetCurScene()->
        AddObject(new Dotween(m_string, Vec2(500, 250), 1.f, DOTWEEN_TYPE::MOVE
        ), OBJECT_GROUP::DOTWEEN);

}

void IntroScene::Update()
{
    float deltaTime = 0.5f; // 실제 deltaTime을 얻기 위해 이를 대체하세요
    elapsedTime += deltaTime;

    if (elapsedTime >= 300.0f && darknessLevel < 300)
    {
        darknessLevel += 1;
    }
    
    if (KEY_DOWN(KEY_TYPE::T))
        SceneMgr::GetInst()->LoadScene(L"NameScene");

    if (KEY_DOWN(KEY_TYPE::Z))
        SceneMgr::GetInst()->LoadScene(L"IntroScene");

    if (KEY_DOWN(KEY_TYPE::X))
    {
        SceneMgr::GetInst()->LoadScene(L"StartScene");
    }

    if (KEY_DOWN(KEY_TYPE::C))
        SceneMgr::GetInst()->LoadScene(L"GameScene");

    Scene::Update();
}

void IntroScene::Render(HDC _dc)
{
    RECT rcClient;
    GetClientRect(Core::GetInst()->GetHwnd(), &rcClient);

    darknessLevel = min(max(darknessLevel, 0), 300);

    COLORREF bgColor = RGB(255 - darknessLevel, 255 - darknessLevel, 255 - darknessLevel);
    HBRUSH hBrush = CreateSolidBrush(bgColor);
    FillRect(_dc, &rcClient, hBrush);
    DeleteObject(hBrush);

    HFONT hFont = CreateFont(200, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
        CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"인천교육소통");
    SelectObject(_dc, hFont);

    if (darknessLevel >= 300)
    {
        SceneMgr::GetInst()->LoadScene(L"NameScene");
    }
    else
    {
        SetTextColor(_dc, RGB(0, 0, 0));
        SetBkMode(_dc, TRANSPARENT);
    }
    Scene::Render(_dc);

    DeleteObject(hFont);
}

void IntroScene::Release()
{
    Scene::Release();
    //RemoveFontResource(L"Res\\Font\\Font.ttf");
    RemoveFontResource(L"Res\\Font\\인천교육소통.ttf");
}
