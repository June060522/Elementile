#pragma once
#include "Object.h"
class Texture;
class Tile : public Object
{
public:
	Tile(XY _posidx, TILE_TYPE _eType, int _cnt);
	~Tile();
public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
public:
	const XY& GetposIdx() const { return m_posidx; }
	const TILE_TYPE& GetType() const { return m_eType; }
	const int& GetCnt() const { return m_cnt; }
	const void SetLight(const bool value) { m_islight = value; }
	const bool CanGo(Tile* _temptile);
private:
	Texture*	m_pTex;
	Texture*	m_pTexDark;
	XY			m_posidx;
	TILE_TYPE	m_eType;
	int			m_cnt;
	bool		m_islight;
};