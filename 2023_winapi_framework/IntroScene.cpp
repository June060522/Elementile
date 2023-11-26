#include "pch.h"
#include "IntroScene.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "DataManager.h"
#include <windows.h>
#include "Button.h"
#include "KeyMgr.h"

void IntroScene::Init()
{
	DataManager::GetInst()->Init();
	AddObject(new Button(), OBJECT_GROUP::UI);
	int result = AddFontResource(L"Res\\Font\\Font.ttf");
	
}

void IntroScene::Update()
{
    
	if(KEY_DOWN(KEY_TYPE::Z))
		SceneMgr::GetInst()->LoadScene(L"IntroScene");
	if (KEY_DOWN(KEY_TYPE::X))
		SceneMgr::GetInst()->LoadScene(L"StartScene");
	if(KEY_DOWN(KEY_TYPE::C))
		SceneMgr::GetInst()->LoadScene(L"GameScene");
	Scene::Update();
}

void IntroScene::Render(HDC _dc)
{
    Scene::Render(_dc);

    //迄飘 利侩 棺 力格 积己
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