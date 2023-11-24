#pragma once
class Texture;
class TileImage
{
public:
	TileImage(const TILE_TYPE& _eType);
	~TileImage();
public:
	const void SetPos(const Vec2& _vPos) { m_vPos = _vPos; }
	const void SetScale(const Vec2& _vScale) { m_vScale = _vScale; }
private:
	TILE_TYPE m_eType;
	Texture*  m_pTex;
	Vec2	  m_vPos;
	Vec2	  m_vScale;
};