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
#include "IntroStarTxt.h"

int darknessLevel = 0;
const float darknessActivationTime = 5.0f;  

void IntroScene::Init()
{   
    m_string = new UIText(Vec2(655, 320), L"난쟁2");

    for (int i = 0; i < 4; i++)
    {
        float xPos, yPos;

        if (i == 0)
        {
            // 위쪽에서 아래쪽으로
            xPos = -0;
            yPos = -0;
        }
        else if (i == 1)
        {
            // 왼쪽에서 오른쪽으로
            xPos = Core::GetInst()->GetResolution().x;
            yPos = 0;
        }
        else if (i == 2)
        {
            // 아래쪽에서 위쪽으로
            xPos = 0;
            yPos = Core::GetInst()->GetResolution().y;
        }
        else
        {
            // 오른쪽에서 왼쪽으로
            xPos = Core::GetInst()->GetResolution().x;
            yPos = Core::GetInst()->GetResolution().y;
        }

        m_vObj.push_back(new IntroStarTxt(100, Vec2(xPos, yPos), L"★", 150, 2.f, 3.f));
    }

    

    //m_string->SetAlpha(0.0f);
    
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
            AddObject(new Dotween(m_vObj[i], Vec2(655, 320), 1.5f, DOTWEEN_TYPE::MOVE
            ), OBJECT_GROUP::DOTWEEN);
    }

    //여기서 별의 이미지가 파티클로 사라지고 글씨가 나타나게 한다
    if (deltaTime >= 9.5f)
    {
        for (size_t i = 0; i < GET_OBJECT(OBJECT_GROUP::STAR).size();)
        {
             GET_OBJECT(OBJECT_GROUP::STAR).erase(GET_OBJECT(OBJECT_GROUP::STAR).begin() + i);
        }
        
        SceneMgr::GetInst()->GetCurScene()->
            AddObject(new Dotween(m_string, Vec2(600, 370), 1.2f, DOTWEEN_TYPE::MOVE
            ), OBJECT_GROUP::DOTWEEN);
    }

    if (deltaTime >= 18.0f && darknessLevel < 300)
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

    // 처음에는 어둡게
    COLORREF bgColor = RGB(darknessLevel, darknessLevel, darknessLevel);
    HBRUSH hBrush = CreateSolidBrush(bgColor);
    FillRect(_dc, &rcClient, hBrush);
    DeleteObject(hBrush);

    if (darknessLevel < 255)
    {
        // 별이 사라지기 전까지 폰트 설정
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
    else
    {
        // 별이 사라진 후에는 다시 흰색 바탕화면으로
        COLORREF bgColor = RGB(255, 255, 255);
        HBRUSH hBrush = CreateSolidBrush(bgColor);
        FillRect(_dc, &rcClient, hBrush);
        DeleteObject(hBrush);

        // 별을 다시 그릴 때 별들을 하얗게 표현하려면 아래의 코드를 추가
        for (size_t i = 0; i < m_vObj.size(); ++i)
        {
            m_vObj[i]->Render(_dc);
        }
    }
}

void IntroScene::Release()
{
    Scene::Release();
    RemoveFontResource(L"Res\\Font\\인천교육소통.ttf");
}
