#pragma once
#include "Object.h"
class Texture;
class TileImage;
class Tile : public Object
{
public:
	Tile(XY _posidx, TILE_TYPE _eType, int _cnt);
	~Tile();
public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
public:
	void AddImage(const int& _cnt, const TILE_TYPE& _type);
	void AddVec(const Vec2& _vScale,const Vec2& _vPos, const TILE_TYPE& _type);
	void ResetVec() { m_tilevec.resize(0); }
public:
	const XY& GetposIdx() const { return m_posidx; }
	const void SetposIdx(XY xy) { m_posidx = xy; }
	const TILE_TYPE& GetType() const { return m_eType; }
	const int& GetCnt() const { return m_cnt; }
	const void SetCnt(int val) {m_cnt += val; }
	const void SetState(const TILE_STATE value) { m_eState = value; }
	const TILE_STATE GetState() const { return m_eState; }
	const bool CanGo(Tile* _temptile);
private:
	vector<TileImage*>	m_tilevec;
	Texture*		m_pTex;
	Texture*		m_pTexDark;
	Texture*		m_pBGDark;
	Texture*		m_pselect;
	XY				m_posidx;
	TILE_TYPE		m_eType;
	int				m_cnt;
	TILE_STATE		m_eState;
};