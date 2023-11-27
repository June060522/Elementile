#include "pch.h"
#include "IntroScene.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "DataManager.h"
#include <windows.h>
#include "Button.h"
#include "KeyMgr.h"
#include "Core.h"
#include "BaseWindow.h"

int darknessLevel = 0;
float elapsedTime = 0.0f; // ��� �ð��� ��Ÿ���� ����
const float transitionTime = 30.0f; // 30�� �Ŀ� ���� ����
const int maxDarknessLevel = 100; // darknessLevel�� �ִ밪

void IntroScene::Init()
{
    DataManager::GetInst()->Init();
    AddObject(new Button(), OBJECT_GROUP::UI);
    int result = AddFontResource(L"Res\\Font\\Font.ttf");
}

void IntroScene::Update()
{
    float deltaTime = 1; // deltaTime�� ��� ����� ���� (������ �� �ð�)

    elapsedTime += deltaTime;

    if (elapsedTime > transitionTime)
    {
        darknessLevel += 1;
    }

    if (KEY_DOWN(KEY_TYPE::Z))
        SceneMgr::GetInst()->LoadScene(L"IntroScene");

    if (KEY_DOWN(KEY_TYPE::X))
    {
        // darknessLevel�� ���� ��ġ�� �����ϸ� StartScene���� ��ȯ
        if (darknessLevel >= 250)
        {
            SceneMgr::GetInst()->LoadScene(L"StartScene");
        }
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

    // darknessLevel�� 255�� �ʰ����� �ʵ��� ����
    darknessLevel = min(darknessLevel, 255);

    COLORREF bgColor = RGB(255 - darknessLevel, 255 - darknessLevel, 255 - darknessLevel);
    HBRUSH hBrush = CreateSolidBrush(bgColor);
    FillRect(_dc, &rcClient, hBrush);
    DeleteObject(hBrush);

    HFONT hFont = CreateFont(200, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
        CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Merriweather Sans ExtraBold");
    SelectObject(_dc, hFont);

    TextOut(_dc, pos.x, pos.y, L"NoBland", wcslen(L"NoBland"));
    SetTextColor(_dc, RGB(255, 0, 0));

    SetBkMode(_dc, TRANSPARENT);

    DeleteObject(hFont);
}

void IntroScene::Release()
{
    Scene::Release();
    RemoveFontResource(L"Res\\Font\\Font.ttf");
}
