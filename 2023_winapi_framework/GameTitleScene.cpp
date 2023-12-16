#include "pch.h"
#include "Dotween.h"
#include "DataManager.h"
#include "Core.h"
#include "UIText.h"
#include "SceneMgr.h"
#include "TimeMgr.h"
#include "GameTitleScene.h"
#include <Windows.h>

int TitledarknessLevel = 0;

void GameTitleScene::Init()
{
    m_string = new UIText(Vec2(600, 310), L"난쟁2");

    AddObject(m_string, OBJECT_GROUP::UI);
    AddFontResource(L"Res\\Font\\인천교육소통.ttf");
}

void GameTitleScene::Update()
{
    timer += TimeMgr::GetInst()->GetDT();

    SceneMgr::GetInst()->GetCurScene()->
        AddObject(new Dotween(m_string, Vec2(600, 310), 0.f, DOTWEEN_TYPE::MOVE
        ), OBJECT_GROUP::DOTWEEN);



    Scene::Update();

    if (timer >= 2.5f)
    {
        SceneMgr::GetInst()->LoadScene(L"NameScene");
    }


}

void GameTitleScene::Render(HDC _dc)
{
    RECT rcClient;
    GetClientRect(Core::GetInst()->GetHwnd(), &rcClient);

    TitledarknessLevel = max(TitledarknessLevel, 255);

    COLORREF bgColor = RGB(TitledarknessLevel, TitledarknessLevel, TitledarknessLevel);
    HBRUSH hBrush = CreateSolidBrush(bgColor);
    FillRect(_dc, &rcClient, hBrush);
    DeleteObject(hBrush);

    TitledarknessLevel = max(TitledarknessLevel, 255);
    HFONT hFont = CreateFont(200, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
        CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"인천교육소통");
    SelectObject(_dc, hFont);

    Scene::Render(_dc);

    DeleteObject(hFont);
}

void GameTitleScene::Release()
{
	Scene::Release();
	RemoveFontResource(L"Res\\Font\\인천교육소통.ttf");
}
