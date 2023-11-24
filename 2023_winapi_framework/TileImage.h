#pragma once
#include "Object.h"
class Texture;
class TileImage : public Object
{
public:
	TileImage(const TILE_TYPE& _eType);
	~TileImage();
public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
private:
	TILE_TYPE m_eType;
	Texture*  m_pTex;
};