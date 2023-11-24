#include "pch.h"
#include "StageManager.h"
#include "Game_Scene.h"
#include "Object.h"
#include "Tile.h"
#include "Core.h"

void StageManager::Init(const int& curStage, Game_Scene* _curGameScene)
{
	m_curGameScene = _curGameScene;
	vResolution = Core::GetInst()->GetResolution();

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
	string temp;
	string path = "Stage\\Stage";
	path += to_string(curStage);
	path += ".txt";
	ifstream inputFile(path);
	bool isOpen = inputFile.is_open();
	if (isOpen)
	{
		for (int i = 0; i < BOARD_Y; i++)
		{
			inputFile >> temp;
			for (int j = 0; j < temp.size(); j++)
				m_board[i][j] = temp[j];
		}
		inputFile.close();
	}
	else
		assert(isOpen);
	RenderBoard();
}

const void StageManager::RenderBoard()
{
	for (int i = 0; i < BOARD_Y; i++)
	{
		for (int j = 0; j < BOARD_X; j++)
		{
			if (m_board[i][j] == '0')
			{
				continue;
			}
			else if (m_board[i][j] == 'f')
			{
				m_curGameScene->AddObject(MakeTile(i, j, TILE_TYPE::FIRE, 1), OBJECT_GROUP::TILE);
			}
			else if (m_board[i][j] == 'w')
			{
				m_curGameScene->AddObject(MakeTile(i, j, TILE_TYPE::WATER, 1), OBJECT_GROUP::TILE);
			}
			else if (m_board[i][j] == 'g')
			{
				m_curGameScene->AddObject(MakeTile(i, j, TILE_TYPE::GRASS, 1), OBJECT_GROUP::TILE);
			}
		}
	}
}

Object* StageManager::MakeTile(const int& _yIdx, const int& _xIdx, const TILE_TYPE& _type, const int& _cnt)
{
	Vec2 pos;
	Object* pObj = new Tile(XY{ _xIdx,_yIdx }, _type, 1);
	pos = Vec2(_xIdx * 135, _yIdx * 100);
	if (_yIdx % 2 == 1)
	{
		pos.x -= 67;
	}
	pos.x += (float)Core::GetInst()->GetResolution().x / 5;
	pos.y += (float)Core::GetInst()->GetResolution().y / 7;
	pObj->SetScale(Vec2(100, 100));
	pObj->SetPos(pos);
	CreateImage(pObj,_cnt);
	return pObj;
}

const void StageManager::CreateImage(const Object* _pObj, const int& _cnt)
{

}