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
#include "KeyMgr.h"
#include "ServerManager.h"

void Game_Scene::Init()
{
	m_GameSceneUI = new GameSceneUI();
	GetGroupObject(OBJECT_GROUP::TILE).clear();
	GetGroupObject(OBJECT_GROUP::DOTWEEN).clear();
	SelectManager::GetInst()->Init();
	StageManager::GetInst()->Init(DataManager::GetInst()->GetLastStage(), this);
	m_GameSceneUI->Init();
	switch (DataManager::GetInst()->GetLastStage())
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 6:
	case 7:
	case 9:
	case 11:
	case 21:
	case 22:
	case 30:
	case 36:
		m_GameSceneUI->SetInfoPenalOpen(true);
		break;
	}
}

void Game_Scene::Update()
{
	if (GetGroupObject(OBJECT_GROUP::TILE).size() == 0)
	{
		if (DataManager::GetInst()->GetLastStage() == DataManager::GetInst()->GetHighStage())
		{
			DataManager::GetInst()->SetHighStage(1);
			DataManager::GetInst()->SaveData();
			ServerManager::GetInst()->Save();
		}
		DataManager::GetInst()->SetLastStage(DataManager::GetInst()->GetLastStage() + 1);
		DataManager::GetInst()->SaveData();
		SceneMgr::GetInst()->LoadScene(L"GameScene");
	}
	SelectManager::GetInst()->Update();
	if (!m_GameSceneUI->GetStagePenalOpen() && !m_GameSceneUI->GetRankingPenalOpen()
		&& !m_GameSceneUI->GetInfoPenalOpen())
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