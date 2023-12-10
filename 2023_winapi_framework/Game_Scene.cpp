#include "pch.h"
#include "Core.h"
#include "Game_Scene.h"
#include "StageManager.h"
#include "DataManager.h"
#include "SelectManager.h"
#include "SceneMgr.h"
#include "Debug.h"
#include "UIText.h"
#include "GameSceneUI.h"
#include "ResMgr.h"

void Game_Scene::Init()
{
	m_GameSceneUI = new GameSceneUI();
	GetGroupObject(OBJECT_GROUP::TILE).clear();
	GetGroupObject(OBJECT_GROUP::DOTWEEN).clear();
	SelectManager::GetInst()->Init();
	StageManager::GetInst()->Init(DataManager::GetInst()->GetLastStage(), this);
	DataManager::GetInst()->SaveData();
	m_GameSceneUI->Init();
}

void Game_Scene::Update()
{
	if (GetGroupObject(OBJECT_GROUP::TILE).size() == 0)
	{
		if(DataManager::GetInst()->GetLastStage() == DataManager::GetInst()->GetHighStage())
			DataManager::GetInst()->SetHighStage(1);
		DataManager::GetInst()->SetLastStage(DataManager::GetInst()->GetLastStage() + 1);
		SceneMgr::GetInst()->LoadScene(L"GameScene");
	}
	SelectManager::GetInst()->Update();
	SelectManager::GetInst()->TileClick(GetGroupObject(OBJECT_GROUP::TILE));
	Scene::Update();
	
	ResMgr::GetInst()->Update();
	m_GameSceneUI->Update();
}

void Game_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);
	m_GameSceneUI->Render(_dc);
}

void Game_Scene::Release()
{
	Scene::Release();
	m_GameSceneUI->Release();
}