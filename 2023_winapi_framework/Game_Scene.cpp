#include "pch.h"
#include "Core.h"
#include "Game_Scene.h"
#include "StageManager.h"
#include "DataManager.h"
#include "KeyMgr.h"
#include "Tile.h"
#include "Debug.h"

void Game_Scene::Init()
{
	StageManager::GetInst()->Init(DataManager::GetInst()->GetLastStage(), this);
}

void Game_Scene::Update()
{
	Debug(m_pMousePos.x);
	if (TileClick())
	{

	}
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

const bool Game_Scene::TileClick()
{
	if (KeyMgr::GetInst()->GetKey(KEY_TYPE::LBUTTON) == KEY_STATE::DOWN)
	{
		m_pMousePos = KeyMgr::GetInst()->GetMousePos();
		m_posIdx.yidx = m_pMousePos.y - (float)Core::GetInst()->GetResolution().y / 7;
		m_posIdx.yidx /= 100;
		m_posIdx.xidx = m_pMousePos.x - (float)Core::GetInst()->GetResolution().x / 5;
		if (m_posIdx.yidx % 2 == 1)
			m_posIdx.yidx -= 67;
		m_posIdx.xidx /= 135;
	}
	return true;
}