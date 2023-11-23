#include "pch.h"
#include "Start_Scene.h"
#include "Core.h"
#include "KeyMgr.h"
#include "ResMgr.h"
void Start_Scene::Init()
{

}

void Start_Scene::Update()
{
	Scene::Update();
	//if(KEY_DOWN(KEY_TYPE::ENTER))
	//	// ¾À º¯°æ
}

void Start_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);

	HFONT hFont = CreateFont(30, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"MerriweatherSans-ExtraBold");
    SelectObject(_dc, hFont);

    SetTextColor(_dc, RGB(255, 255, 255));

    SetBkMode(_dc, TRANSPARENT);

    RECT rect = { 100, 100, 500, 200 };

    DrawText(_dc, L"Hello, World!", -1, &rect, DT_CENTER | DT_VCENTER);

    // Clean up the font
    DeleteObject(hFont);

}

void Start_Scene::Release()
{
	Scene::Release();
}
