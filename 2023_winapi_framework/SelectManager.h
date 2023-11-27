#pragma once
class Object;
class Tile;
class SelectManager
{
	SINGLE(SelectManager);
public:
	void Init();
public:
	const void TileClick(const vector<Object*>& _tilegroup);
private:
	const bool& TriangleInPoint(Vec2& _p1, Vec2& _p2,
		Vec2& _p3, Vec2& _point);
	float Cross(const Vec2& _v1, const Vec2& _v2)
	{
		return _v1.x * _v2.y - _v1.y * _v2.x;
	}
public:
	Tile* GetSelectTile() { return m_selectTile; }
private:
	Tile* m_selectTile;
	Vec2 m_pMousePos;
	float m_fRadius, m_fCorrectionX, m_fCorrectionY;
};