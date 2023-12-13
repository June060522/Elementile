#pragma once
#include "Object.h"
class Texture;
class TileImage : public Object
{
public:
	TileImage(const TILE_TYPE& _eType, int _cnt = 1);
	~TileImage();
public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
public:
	const void SetCorrectionPosX(const int& val) { m_fCorrectionPosX = val; }
	const void SetCorrectionPosY(const int& val) { m_fCorrectionPosY = val; }
	const float& GetCorrectionPosX() { return m_fCorrectionPosX; }
	const float& GetCorrectionPosY() { return m_fCorrectionPosY; }
	const void SetCorrectionScaleX(const int& val) { m_fCorrectionScaleX = val; }
	const void SetCorrectionScaleY(const int& val) { m_fCorrectionScaleY = val; }
	const float& GetCorrectionScaleX() { return m_fCorrectionScaleX; }
	const float& GetCorrectionScaleY() { return m_fCorrectionScaleY; }
private:
	float		m_fCorrectionPosX;
	float		m_fCorrectionPosY;
	float		m_fCorrectionScaleX;
	float		m_fCorrectionScaleY;
	TILE_TYPE	m_eType;
	Texture*	m_pTex;

	wstring		m_tileCnt;
};