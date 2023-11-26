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
				m_curGameScene->AddObject(MakeTile(i, j, TILE_TYPE::WATER, 5), OBJECT_GROUP::TILE);
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
				m_curGameScene->AddObject(MakeTile(i, j, TILE_TYPE::GRASS, 5), OBJECT_GROUP::TILE);
			}
		}
	}
}

Object* StageManager::MakeTile(const int& _yIdx, const int& _xIdx, const TILE_TYPE& _type, const int& _cnt)
{
	Vec2 pos;
	Object* pObj = new Tile(XY{ _xIdx,_yIdx }, _type, _cnt);
	pos = Vec2(_xIdx * 135, _yIdx * 100);
	if (_yIdx % 2 == 1)
	{
		pos.x -= 67;
	}
	pos.x += (float)Core::GetInst()->GetResolution().x / 5;
	pos.y += (float)Core::GetInst()->GetResolution().y / 7;
	pObj->SetScale(Vec2(100, 100));
	pObj->SetPos(pos);
	CreateImage(pObj, _cnt, _type);
	return pObj;
}

const void StageManager::CreateImage(const Object* _pObj, const int& _cnt, const TILE_TYPE& _type)
{
	Vec2 pos;
	Vec2 scale;
	switch (_cnt) // 그릴 이미지 갯수 일단 5개까지만
	{
	case 1:
	{
		pos = Vec2(_pObj->GetPos().x + 15, _pObj->GetPos().y);
		scale = Vec2(15, 15);
		AddImage(pos, scale, _type);
	}
	break;
	case 2:
	{
		scale = Vec2(13, 13);
		pos = Vec2(_pObj->GetPos().x + 50, _pObj->GetPos().y + 7);
		AddImage(pos, scale, _type);

		pos = Vec2(_pObj->GetPos().x - 10, _pObj->GetPos().y + 7);
		AddImage(pos, scale, _type);
	}
	break;
	case 3:
	{
		scale = Vec2(11, 11);
		Vec2 midPos = Vec2(_pObj->GetPos().x + 25, _pObj->GetPos().y + 10);
		float radius = 30.0f;
		for (int i = 0; i < 3; i++)
		{
			float angle = i * (2 * M_PI / 3.0f) + M_PI / 6.0f;

			pos.x = midPos.x + radius * cos(angle);
			pos.y = midPos.y + radius * sin(angle);

			AddImage(pos, scale, _type);
		}
	}
	break;
	case 4:
	{
		int middis = 23;
		float radius = 30.0f;
		Vec2 midPos = Vec2(_pObj->GetPos().x + 26, _pObj->GetPos().y + 13);
		scale = Vec2(9, 9);

		pos.x = midPos.x + middis;
		pos.y = midPos.y + middis;
		AddImage(pos, scale, _type);

		pos.x = midPos.x + middis;
		pos.y = midPos.y - middis;
		AddImage(pos, scale, _type);

		pos.x = midPos.x - middis;
		pos.y = midPos.y + middis;
		AddImage(pos, scale, _type);

		pos.x = midPos.x - middis;
		pos.y = midPos.y - middis;
		AddImage(pos, scale, _type);
	}
	break;
	case 5:
	{
		scale = Vec2(8, 8);
		Vec2 midPos = Vec2(_pObj->GetPos().x + 28, _pObj->GetPos().y + 15);

		float radius = 33.0f;

		for (int i = 0; i < 5; i++)
		{
			float angle = (i * (2 * M_PI / 5.0f)) + M_PI / 2.f;

			pos.x = midPos.x + radius * cos(angle);
			pos.y = midPos.y + radius * sin(-angle);

			AddImage(pos, scale, _type);
		}
	}
	break;
	default:
		assert(_cnt);
		break;
	}
}

const void StageManager::AddImage(const Vec2& _pos, const Vec2& _scale, const TILE_TYPE& _type)
{
	Object* pObj = new TileImage(_type);
	pObj->SetPos(_pos);
	pObj->SetScale(_scale);
	m_curGameScene->AddObject(pObj, OBJECT_GROUP::TILEIMAGE);
}
