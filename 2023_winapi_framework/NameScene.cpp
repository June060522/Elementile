#include "pch.h"
#include "Core.h"
#include "KeyMgr.h"
#include "DataManager.h"
#include "ResMgr.h"
#include "NameScene.h"
#include "SceneMgr.h"

int currentCharIndex = 0;
int maxCharIndex;
int charDelay = 100;
DWORD lastCharTime = 0;

void NameScene::Init()
{
    DataManager::GetInst()->Init();
    int result = AddFontResource(L"Res\\Font\\Font.ttf");

    maxCharIndex = wcslen(L"June & Min1");
}

void NameScene::Update()
{
    Scene::Update();

    if (currentCharIndex < maxCharIndex)
    {
        // 현재 시간을 가져와서 charDelay 이상이 지났는지 확인
        DWORD currentTime = GetTickCount();

        if (currentTime - lastCharTime >= charDelay)
        {
            // charDelay 이상이 지났으면 다음 글자로 이동
            ++currentCharIndex;

            // 현재 시간 업데이트
            lastCharTime = currentTime;
        }
    }
    else
    {
        // Displayed all characters, transition to the StartScene
          SceneMgr::GetInst()->LoadScene(L"StartScene");
    }
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

    COLORREF bgColor = RGB(0, 0, 0);
    HBRUSH hBrush = CreateSolidBrush(bgColor);
    FillRect(_dc, &rcClient, hBrush);
    DeleteObject(hBrush);

    SetTextColor(_dc, RGB(255, 0, 0));
    SetBkMode(_dc, TRANSPARENT);

    // 출력 중인 글자만큼만 출력
    TextOut(_dc, pos.x, pos.y, L"June & Min1", currentCharIndex);

    DeleteObject(hFont);
}

void NameScene::Release()
{
    Scene::Release();

    RemoveFontResource(L"Res\\Font\\Font.ttf");
}
