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

void StageManager::RenderBoard()
{
	for (int i = 0; i < BOARD_Y; i++)
	{
		for (int j = 0; j < BOARD_X; j++)
		{
			if (m_board[i][j] == '0')
				continue;
			else if (m_board[i][j] == 'f')
			{
				m_curGameScene->AddObject(MakeTile(i,j, TILE_TYPE::FIRE), OBJECT_GROUP::TILE);
			}
			else if (m_board[i][j] == 'w')
			{
				m_curGameScene->AddObject(MakeTile(i, j, TILE_TYPE::WATER), OBJECT_GROUP::TILE);
			}
			else if (m_board[i][j] == 'g')
			{
				m_curGameScene->AddObject(MakeTile(i, j, TILE_TYPE::GRASS), OBJECT_GROUP::TILE);
			}
		}
	}
}

Object* StageManager::MakeTile(const int& _yIdx,const int& _xIdx, const TILE_TYPE& _type)
{
	Vec2 pos;
	Object* pObj = new Tile(XY{ _xIdx,_yIdx }, _type);
		pos = Vec2(_xIdx * 65 + 10 * _xIdx, _yIdx * 65);
	if (_yIdx % 2 == 1)
	{
		pos.x -= 30;
	}
	pos.x += (float)Core::GetInst()->GetResolution().x / 3;
	pos.y += (float)Core::GetInst()->GetResolution().y / 5;
	pObj->SetPos(pos);
	pObj->SetScale(Vec2(50, 50));
	return pObj;
}