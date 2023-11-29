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
const float darknessActivationTime = 5.0f;  


void IntroScene::Init()
{   
    m_string = new UIText(Vec2(-80.f, -150.f), L"난쟁2"); 

    m_vObj.push_back(new UIText(Vec2(-300.f, 1080.f), L"★"));
    AddObject(m_string, OBJECT_GROUP::UI);
    DataManager::GetInst()->Init();
    

    int title = AddFontResource(L"Res\\Font\\인천교육소통.ttf");

    //SceneMgr::GetInst()->GetCurScene()->
    //    AddObject(new Dotween(m_string, Vec2(250, 560), 1.8f, DOTWEEN_TYPE::MOVE
    //    ), OBJECT_GROUP::DOTWEEN);
    //SceneMgr::GetInst()->GetCurScene()->
    //    AddObject(new Dotween(m_string, Vec2(500, 250), 2.f, 1.5f, DOTWEEN_TYPE::MOVE
    //    ), OBJECT_GROUP::DOTWEEN);
    //SceneMgr::GetInst()->GetCurScene()->
    //    AddObject(new Dotween(m_string, Vec2(570, 350), 1.6f, 2.7f, DOTWEEN_TYPE::MOVE
    //    ), OBJECT_GROUP::DOTWEEN);

    for (size_t i = 0; i < m_vObj.size(); ++i)
        AddObject(m_vObj[i], OBJECT_GROUP::STAR);
}

void IntroScene::Update()
{
    deltaTime += TimeMgr::GetInst()->GetDT();

    for (size_t i = 0; i < m_vObj.size(); ++i)
    {
        SceneMgr::GetInst()->GetCurScene()->
            AddObject(new Dotween(m_vObj[i], Vec2(700, 350), 1.5f, DOTWEEN_TYPE::MOVE
            ), OBJECT_GROUP::DOTWEEN);
    }

    if (deltaTime >= 7)
    {
        HFONT hFont = CreateFont(1000, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
            CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"인천교육소통");

    }

    //여기서 별의 이미지가 파티클로 사라지고 글씨가 나타나게 한다
    if (deltaTime >= 9.5f)
    {
        //글자 사이트 크게 하기
       

        for (size_t i = 0; i < GET_OBJECT(OBJECT_GROUP::STAR).size();)
        {
             GET_OBJECT(OBJECT_GROUP::STAR).erase(GET_OBJECT(OBJECT_GROUP::STAR).begin() + i);
        }
        
        SceneMgr::GetInst()->GetCurScene()->
            AddObject(new Dotween(m_string, Vec2(250, 560), 1.8f, DOTWEEN_TYPE::MOVE
            ), OBJECT_GROUP::DOTWEEN);
    }

    if (deltaTime >= 25.0f && darknessLevel < 300)
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

    darknessLevel = max(darknessLevel, 255);

    COLORREF bgColor = RGB( darknessLevel,  darknessLevel,  darknessLevel);
    HBRUSH hBrush = CreateSolidBrush(bgColor);
    FillRect(_dc, &rcClient, hBrush);
    DeleteObject(hBrush);

    darknessLevel = max(darknessLevel, 255);
    HFONT hFont = CreateFont(200, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
        CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"인천교육소통");
    SelectObject(_dc, hFont);

    if (darknessLevel >= 280)
    {
        SceneMgr::GetInst()->LoadScene(L"NameScene");
    }
    else
    {
        DeleteObject(hFont);
        SetTextColor(_dc, RGB(0, 0, 0));
        SetBkMode(_dc, TRANSPARENT);
    }
    Scene::Render(_dc);

    DeleteObject(hFont);
}

void IntroScene::Release()
{
    Scene::Release();
    RemoveFontResource(L"Res\\Font\\인천교육소통.ttf");
}

void IntroScene::SetTextSize(HWND _hWnd, int newSize)
{
    /*newSize = 50;
    HFONT hFont = GetStockObject(DEFAULT_GUI_FONT);
    LOGFONT lf;
    GetObject(hFont, sizeof(LOGFONT), &lf);
    lf.lfHeight = newSize;
    HFONT hNewFont = CreateFontIndirect(&lf);*/
}
