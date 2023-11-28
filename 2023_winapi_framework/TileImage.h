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
public:
	const void SetCorrectionX(const int& val) { m_fCorrectionX = val; }
	const void SetCorrectionY(const int& val) { m_fCorrectionY = val; }
	const float& GetCorrectionX() { return m_fCorrectionX; }
	const float& GetCorrectionY() { return m_fCorrectionY; }
private:
	float		m_fCorrectionX;
	float		m_fCorrectionY;
	TILE_TYPE	m_eType;
	Texture*	m_pTex;
};