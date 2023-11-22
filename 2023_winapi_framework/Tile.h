#pragma once
#include "Object.h"
class Texture;
class Tile : public Object
{
public:
	Tile(XY _posidx, TILE_TYPE _eType);
	~Tile();
public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
public:
	const XY& GetposIdx() const { return m_posidx; }
	const TILE_TYPE& GetType() const { return m_eType; }
private:
	Texture* m_pTex;
	XY m_posidx;
	TILE_TYPE m_eType;
};