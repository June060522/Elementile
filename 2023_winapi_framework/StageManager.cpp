#include "pch.h"
#include "StageManager.h"
#include "Game_Scene.h"
#include "Object.h"
#include "Tile.h"
#include "Core.h"

void StageManager::Init(const int& curStage, Game_Scene* _curGameScene)
{
	m_curGameScene = _curGameScene;

	for (int i = 0; i < BOARD_Y; i++)
	{
		for (int j = 0; j < BOARD_X; j++)
		{
			m_board[i][j] = NULL;
		}
	}
	LoadMap(curStage);
}

const void StageManager::LoadMap(const int& curStage)
{
	string path = "Stage\\Stage";
	path += curStage + ".txt";
	ifstream inputFile(path);
	bool isOpen = inputFile.is_open();
	if (isOpen)
	{
		for (int i = 0; i < BOARD_Y; i++)
		{
			inputFile >> m_board[i];
		}
		inputFile.close();
	}
	else
		assert(isOpen);
	RenderBoard();
}

void StageManager::RenderBoard()
{
	for (int i = 0; i < BOARD_Y; i++)
	{
		for (int j = 0; j < BOARD_X; j++)
		{
			if (m_board[i][j] != 1)
			{
				m_curGameScene->AddObject(MakeTile(), OBJECT_GROUP::TILE);
			}
		}
	}
}

Object* StageManager::MakeTile()
{
	Vec2 vResolution = Core::GetInst()->GetResolution();
	Object* pObj = new Tile(XY{ 0,0 }, TILE_TYPE::FIRE);
	pObj->SetPos(Vec2(vResolution.x / 2, vResolution.y / 2));
	pObj->SetScale(Vec2(100, 100));
	return pObj;
}
