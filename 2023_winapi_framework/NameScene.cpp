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

    maxCharIndex = wcslen(L"June & Min");
}

void NameScene::Update()
{
    Scene::Update();

    if (currentCharIndex < maxCharIndex)
    {
        // ���� �ð��� �����ͼ� charDelay �̻��� �������� Ȯ��
        DWORD currentTime = GetTickCount();

        if (currentTime - lastCharTime >= charDelay)
        {
            // charDelay �̻��� �������� ���� ���ڷ� �̵�
            ++currentCharIndex;

            // ���� �ð� ������Ʈ
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

    // ��Ʈ ���� �� ���� ����
    HFONT hFont = CreateFont(200, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
        CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Merriweather Sans ExtraBold");
    SelectObject(_dc, hFont);

    SetTextColor(_dc, RGB(255, 0, 0));
    SetBkMode(_dc, TRANSPARENT);

    // ��� ���� ���ڸ�ŭ�� ���
    TextOut(_dc, pos.x, pos.y, L"June & Min", currentCharIndex);

    DeleteObject(hFont);
}

void NameScene::Release()
{
    Scene::Release();

    RemoveFontResource(L"Res\\Font\\Font.ttf");
}
