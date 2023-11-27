#include "pch.h"
#include "IntroScene.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "DataManager.h"
#include <windows.h>
#include "Button.h"
#include "Core.h"
#include "TimeMgr.h"

int darknessLevel = 0;
float elapsedTime = -5.0f; 
const float darknessActivationTime = 5.0f;  

void IntroScene::Init()
{   
    DataManager::GetInst()->Init();
    AddObject(new Button(), OBJECT_GROUP::UI);
    //int result = AddFontResource(L"Res\\Font\\Font.ttf");
    int title = AddFontResource(L"Res\\Font\\인천교육소통.ttf");
}

void IntroScene::Update()
{
    float deltaTime = 0.5f; // 실제 deltaTime을 얻기 위해 이를 대체하세요
    elapsedTime += deltaTime;

    if (elapsedTime >= 300.0f && darknessLevel < 300)
    {
        darknessLevel += 1;

        if (darknessLevel >= 300)
        {
            // darknessLevel이 250에 도달하면 천천히 하얀색으로 전환
            float transitionDuration = 1.0f; // 전환 기간을 조절하세요
            float transitionProgress = min((elapsedTime - darknessActivationTime) / transitionDuration, 1.0f);
            int targetDarkness = 0; // 목표로 하는 darknessLevel
        }
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
    Scene::Render(_dc);

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
        SetTextColor(_dc, RGB(255, 255, 255));
        SetBkMode(_dc, TRANSPARENT);
        TextOut(_dc, pos.x, pos.y, L"난쟁2", wcslen(L"난쟁2"));
    }

    DeleteObject(hFont);
}

void IntroScene::Release()
{
    Scene::Release();
    //RemoveFontResource(L"Res\\Font\\Font.ttf");
    RemoveFontResource(L"Res\\Font\\인천교육소통.ttf");
}
