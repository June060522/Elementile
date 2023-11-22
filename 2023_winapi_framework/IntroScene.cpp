#include "pch.h"
#include "IntroScene.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

void IntroScene::Init()
{
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
}

void IntroScene::Release()
{
	Scene::Release();
}