#include "pch.h"
#include "Core.h"
#include "Game_Scene.h"
#include "StageManager.h"
#include "DataManager.h"
#include "SelectManager.h"
#include "Debug.h"

void Game_Scene::Init()
{
	SelectManager::GetInst()->Init();
	StageManager::GetInst()->Init(DataManager::GetInst()->GetLastStage(), this);
}

void Game_Scene::Update()
{
	SelectManager::GetInst()->Update();
	SelectManager::GetInst()->TileClick(GetGroupObject(OBJECT_GROUP::TILE));
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