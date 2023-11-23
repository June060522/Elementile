#include "pch.h"
#include "Core.h"
#include "Game_Scene.h"
#include "StageManager.h"
#include "DataManager.h"

void Game_Scene::Init()
{
	StageManager::GetInst()->Init(DataManager::GetInst()->GetLastStage(), this);
}

void Game_Scene::Update()
{
	Scene::Update();
}

void Game_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);
}

void Game_Scene::Release()
{
	Scene::Release();
}
