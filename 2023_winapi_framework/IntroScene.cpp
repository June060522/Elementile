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
    m_string = new UIText(Vec2(600, 310), L"난쟁2");

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

        m_vObj.push_back(new IntroStarTxt(100, Vec2(xPos, yPos), L"★", 150, 2.f, 4.f));
    }



    //m_string->SetAlpha(0.0f);

    AddObject(m_string, OBJECT_GROUP::UI);
    DataManager::GetInst()->Init();

    AddFontResource(L"Res\\Font\\인천교육소통.ttf");

    for (size_t i = 0; i < m_vObj.size(); ++i)
        AddObject(m_vObj[i], OBJECT_GROUP::STAR);
}

void IntroScene::Update()
{
    deltaTime += TimeMgr::GetInst()->GetDT();

    // 별 이동
    for (size_t i = 0; i < m_vObj.size(); ++i)
    {
        SceneMgr::GetInst()->GetCurScene()->
            AddObject(new Dotween(m_vObj[i], Vec2(655, 320), 1.5f, DOTWEEN_TYPE::MOVE
            ), OBJECT_GROUP::DOTWEEN);
    }

    // 일정 시간이 지나면 별 삭제
    if (deltaTime >= 8.5f)
    {
        GET_OBJECT(OBJECT_GROUP::STAR).clear();

        // 글씨 나타나기
        SceneMgr::GetInst()->GetCurScene()->
            AddObject(new Dotween(m_string, Vec2(600, 310), 0.f, DOTWEEN_TYPE::MOVE
            ), OBJECT_GROUP::DOTWEEN);
    }

    // 어둡기 효과
    if (deltaTime >= 8.3f && darknessLevel < 300)
    {
        darknessLevel += 1;
    }

    // 키 입력으로 씬 전환
    HandleSceneChangeInput();

    Scene::Update();
}

void IntroScene::HandleSceneChangeInput()
{
    if (KEY_DOWN(KEY_TYPE::T))
        SceneMgr::GetInst()->LoadScene(L"NameScene");

    if (KEY_DOWN(KEY_TYPE::Z))
        SceneMgr::GetInst()->LoadScene(L"IntroScene");

    if (KEY_DOWN(KEY_TYPE::X))
        SceneMgr::GetInst()->LoadScene(L"StartScene");

    if (KEY_DOWN(KEY_TYPE::C))
        SceneMgr::GetInst()->LoadScene(L"GameScene");
}

void IntroScene::Render(HDC _dc)
{
    RECT rcClient;
    GetClientRect(Core::GetInst()->GetHwnd(), &rcClient);

    // 어둡게 설정
    COLORREF bgColor = RGB(darknessLevel, darknessLevel, darknessLevel);
    HBRUSH hBrush = CreateSolidBrush(bgColor);
    FillRect(_dc, &rcClient, hBrush);
    DeleteObject(hBrush);

    // 어두운 상태에서 폰트 설정
    if (darknessLevel < 255)
    {
        HFONT hFont = CreateFont(200, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
            CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"인천교육소통");
        SelectObject(_dc, hFont);

        // darknessLevel이 270 이하인 경우에만 렌더링
        if (darknessLevel <= 270)
        {
            DeleteObject(hFont);
            SetTextColor(_dc, RGB(0, 0, 0));
            SetBkMode(_dc, TRANSPARENT);
            Scene::Render(_dc);
        }
    }
    else
    {
        // darknessLevel이 255 이상이면 GameTitleScene으로 전환
        SceneMgr::GetInst()->LoadScene(L"GameTitleScene");
    }
}

void IntroScene::Release()
{
    Scene::Release();
    RemoveFontResource(L"Res\\Font\\인천교육소통.ttf");
}
