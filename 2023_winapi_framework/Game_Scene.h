#pragma once
#include "Scene.h"
class Tile;
class Game_Scene :
	public Scene
{
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
	virtual void Release() override;

private:
	const bool TileClick();

private:
	POINT	m_pMousePos;
	Tile*	m_tSelectTile;
	XY		m_posIdx;
};