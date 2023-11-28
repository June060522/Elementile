#include "pch.h"
#include "StageManager.h"
#include "Game_Scene.h"
#include "Object.h"
#include "Tile.h"
#include "TileImage.h"
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
			else if (m_board[i][j] == 'F')
			{
				m_curGameScene->AddObject(MakeTile(i, j, TILE_TYPE::FIRE, 2), OBJECT_GROUP::TILE);
			}
			else if (m_board[i][j] == 'l')
			{
				m_curGameScene->AddObject(MakeTile(i, j, TILE_TYPE::FIRE, 3), OBJECT_GROUP::TILE);
			}
			else if (m_board[i][j] == 'L')
			{
				m_curGameScene->AddObject(MakeTile(i, j, TILE_TYPE::FIRE, 4), OBJECT_GROUP::TILE);
			}
			else if (m_board[i][j] == 'w')
			{
				m_curGameScene->AddObject(MakeTile(i, j, TILE_TYPE::WATER, 1), OBJECT_GROUP::TILE);
			}
			else if (m_board[i][j] == 'W')
			{
				m_curGameScene->AddObject(MakeTile(i, j, TILE_TYPE::WATER, 2), OBJECT_GROUP::TILE);
			}
			else if (m_board[i][j] == 's')
			{
				m_curGameScene->AddObject(MakeTile(i, j, TILE_TYPE::WATER, 3), OBJECT_GROUP::TILE);
			}
			else if (m_board[i][j] == 'S')
			{
				m_curGameScene->AddObject(MakeTile(i, j, TILE_TYPE::WATER, 4), OBJECT_GROUP::TILE);
			}
			else if (m_board[i][j] == 'g')
			{
				m_curGameScene->AddObject(MakeTile(i, j, TILE_TYPE::GRASS, 1), OBJECT_GROUP::TILE);
			}
			else if (m_board[i][j] == 'G')
			{
				m_curGameScene->AddObject(MakeTile(i, j, TILE_TYPE::GRASS, 2), OBJECT_GROUP::TILE);
			}
			else if (m_board[i][j] == 't')
			{
				m_curGameScene->AddObject(MakeTile(i, j, TILE_TYPE::GRASS, 3), OBJECT_GROUP::TILE);
			}
			else if (m_board[i][j] == 'T')
			{
				m_curGameScene->AddObject(MakeTile(i, j, TILE_TYPE::GRASS, 4), OBJECT_GROUP::TILE);
			}                                                                                                                                                                                  
		}
	}
}

Object* StageManager::MakeTile(const int& _yIdx, const int& _xIdx, const TILE_TYPE& _type, const int& _cnt)
{
	Vec2 pos;
	Object* pObj = new Tile(XY{ _xIdx,_yIdx }, _type, _cnt);
	Tile* tempTile = (Tile*)pObj;
	pos = Vec2(_xIdx * 128, _yIdx * 105);
	if (_yIdx % 2 == 1)
	{
		pos.x -= 65;
	}
	pos.x += (float)Core::GetInst()->GetResolution().x / 4.f;
	pos.y += (float)Core::GetInst()->GetResolution().y / 12;
	pObj->SetScale(Vec2(32, 32));
	pObj->SetPos(pos);
	tempTile->AddImage(_cnt, _type);
	return pObj;
}