#include "pch.h"
#include "Core.h"
#include "Game_Scene.h"
#include "Object.h"
#include "Tile.h"

void Game_Scene::Init()
{
	Vec2 vResolution = Core::GetInst()->GetResolution();
	Object* pObj = new Tile(XY{0,0},TILE_TYPE::FIRE);
	pObj->SetPos(Vec2(vResolution.x / 2, vResolution.y / 2));
	pObj->SetScale(Vec2(100, 100));
	AddObject(pObj, OBJECT_GROUP::TILE);
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
