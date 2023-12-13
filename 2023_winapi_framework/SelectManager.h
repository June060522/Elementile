#pragma once
class Object;
class Tile;
class SelectManager
{
	SINGLE(SelectManager);
public:
	void Init();
	void Update();
public:
	const void TileClick(const vector<Object*>& _tilegroup);
	const Tile* GetTile() const { return m_selectTile; }
private:
	const bool& TriangleInPoint(Vec2& _p1, Vec2& _p2,
		Vec2& _p3, Vec2& _point);
	float Cross(const Vec2& _v1, const Vec2& _v2){return _v1.x * _v2.y - _v1.y * _v2.x;}
	const void Merge();
	const void SetTilePos(Tile* _tile);
public:
	Tile* GetSelectTile() { return m_selectTile; }
private:
	bool	m_canMove;
	float	m_ftime;
	float	m_fmovetime;
	Tile*	m_to;
	Tile*	m_selectTile;
	Vec2 m_pMousePos;
	float m_fRadius, m_fCorrectionX, m_fCorrectionY;
};