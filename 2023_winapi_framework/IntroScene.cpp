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
float elapsedTime = -5.0f; // Set initial elapsedTime to -5 seconds
const float darknessActivationTime = 5.0f; // Darkness activation time
const float transitionTime = 5.0f; // 5 seconds after the scene change
const int maxDarknessLevel = 100; // Maximum value for darknessLevel

void IntroScene::Init()
{
    increasingDarkness = true;
    transitionExecuted = false;
    time = 0;
    ftime = 100;
    DataManager::GetInst()->Init();
    AddObject(new Button(), OBJECT_GROUP::UI);
    //int result = AddFontResource(L"Res\\Font\\Font.ttf");
    int title = AddFontResource(L"Res\\Font\\인천교육소통.ttf");

    elapsedTime = -5.0f;
}

void IntroScene::Update()
{
    float deltaTime = 1; // 실제 deltaTime을 얻기 위해 이를 대체하세요
    elapsedTime += deltaTime;

    currentCharIndex = 0;
    maxCharIndex =0;

    if (elapsedTime >= 50.0f && darknessLevel < 350)
    {
        if (increasingDarkness && darknessLevel < 250)
        {
            darknessLevel += 1;
        }
        else if (!increasingDarkness && darknessLevel > 0)
        {
            darknessLevel = max(darknessLevel - 1, 0);
        }

        if (darknessLevel >= 250 && !transitionExecuted)
        {
            // darknessLevel이 250에 도달하면 천천히 하얀색으로 전환
            float transitionDuration = 2.0f; // 전환 기간을 조절하세요
            float transitionProgress = min((elapsedTime - darknessActivationTime) / transitionDuration, 1.0f);
            int targetDarkness = 0; // 목표로 하는 darknessLevel

            // 보간된 값으로 darknessLevel 조절
            //darknessLevel = static_cast<int>(darknessLevel + (targetDarkness - darknessLevel) * transitionProgress);

            // 전환이 완료되면 타이머와 상태를 초기화
            if (transitionProgress >= 1.0f)
            {
                elapsedTime = -5.0f; // 타이머 초기화
                increasingDarkness = true; // 전환 상태 초기화
                transitionExecuted = true; // 전환 플래그 설정
            }
        }
        else if (darknessLevel <= 0)
        {
            increasingDarkness = true;
            transitionExecuted = false; // darknessLevel이 250 아래로 내려가면 전환 플래그 초기화
        }
    }

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

    darknessLevel = min(max(darknessLevel, 0), 255);

    COLORREF bgColor = RGB(255 - darknessLevel, 255 - darknessLevel, 255 - darknessLevel);
    HBRUSH hBrush = CreateSolidBrush(bgColor);
    FillRect(_dc, &rcClient, hBrush);
    DeleteObject(hBrush);

    HFONT hFont = CreateFont(200, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
        CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"인천교육소통");
    SelectObject(_dc, hFont);

    if (darknessLevel >= 250)
    {
        SetTextColor(_dc, RGB(255, 0, 0));
        SetBkMode(_dc, TRANSPARENT);
        TextOut(_dc, pos.x, pos.y, L"June and min", wcslen(L"June and min"));
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
