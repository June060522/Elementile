#include "pch.h"
#include "Start_Scene.h"
#include "Core.h"
#include "KeyMgr.h"
#include "DataManager.h"
#include "ResMgr.h"

int currentCharIndex = 0;
int maxCharIndex;
int charDelay = 100;
DWORD lastCharTime = 0;

void Start_Scene::Init()
{
    DataManager::GetInst()->Init();
    int result = AddFontResource(L"Res\Font\Font.ttf");

    maxCharIndex = wcslen(L"June & Min");
}

void Start_Scene::Update()
{
    Scene::Update();

    if (currentCharIndex < maxCharIndex)
    {
        // Gradual appearance effect
        DWORD currentTime = GetTickCount();

        if (currentTime - lastCharTime >= charDelay)
        {
            ++currentCharIndex;
            lastCharTime = currentTime;
        }
    }
}

void Start_Scene::Render(HDC _dc)
{
    Scene::Render(_dc);

    HFONT hFont = CreateFont(200, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
        CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Merriweather Sans ExtraBold");
    SelectObject(_dc, hFont);

    for (int i = 0; i < currentCharIndex; ++i)
    {
        // Calculate alpha based on the current index
        int alpha = 255 - (i * (255 / maxCharIndex));

        // Set the text color with alpha
        SetTextColor(_dc, RGB(255, 0, 0) | (alpha << 24));

        // Output each character separately
        TextOut(_dc, pos.x + i * 30, pos.y, &L"June & Min"[i], 1);
    }

    SetBkMode(_dc, TRANSPARENT);

    DeleteObject(hFont);
}

void Start_Scene::Release()
{
    Scene::Release();
    RemoveFontResource(L"Res\Font\Font.ttf");
}