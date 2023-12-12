#include "pch.h"
#include "TileImage.h"
#include "ResMgr.h"
#include "Texture.h"

TileImage::TileImage(const TILE_TYPE& _eType, int _cnt)
	:m_eType(_eType)
{
	switch (m_eType)
	{
	case TILE_TYPE::WATER:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Water", L"Texture\\water.bmp");
		break;
	case TILE_TYPE::FIRE:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Fire", L"Texture\\fire.bmp");
		break;
	case TILE_TYPE::GRASS:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Grass", L"Texture\\grass.bmp");
		break;
	case TILE_TYPE::FIRELOCK:
		if (_cnt == 1)
			m_pTex = ResMgr::GetInst()->TexLoad(L"LockFire1", L"Texture\\lockfire1.bmp");
		if (_cnt == 2)
			m_pTex = ResMgr::GetInst()->TexLoad(L"LockFire2", L"Texture\\lockfire2.bmp");
		if (_cnt == 3)
			m_pTex = ResMgr::GetInst()->TexLoad(L"LockFire3", L"Texture\\lockfire3.bmp");
		if (_cnt == 4)
			m_pTex = ResMgr::GetInst()->TexLoad(L"LockFire4", L"Texture\\lockfire4.bmp");
		if (_cnt == 5)
			m_pTex = ResMgr::GetInst()->TexLoad(L"LockFire5", L"Texture\\lockfire5.bmp");
		break;
	case TILE_TYPE::WATERLOCK:
		if (_cnt == 1)
			m_pTex = ResMgr::GetInst()->TexLoad(L"LockWater1", L"Texture\\lockwater1.bmp");
		if (_cnt == 2)
			m_pTex = ResMgr::GetInst()->TexLoad(L"LockWater2", L"Texture\\lockwater2.bmp");
		if (_cnt == 3)
			m_pTex = ResMgr::GetInst()->TexLoad(L"LockWater3", L"Texture\\lockwater3.bmp");
		if (_cnt == 4)
			m_pTex = ResMgr::GetInst()->TexLoad(L"LockWater4", L"Texture\\lockwater4.bmp");
		if (_cnt == 5)
			m_pTex = ResMgr::GetInst()->TexLoad(L"LockWater5", L"Texture\\lockwater5.bmp");
		break;
	case TILE_TYPE::GRASSLOCK:
		if (_cnt == 1)
			m_pTex = ResMgr::GetInst()->TexLoad(L"LockGrass1", L"Texture\\lockgrass1.bmp");
		if (_cnt == 2)
			m_pTex = ResMgr::GetInst()->TexLoad(L"LockGrass2", L"Texture\\lockgrass2.bmp");
		if (_cnt == 3)
			m_pTex = ResMgr::GetInst()->TexLoad(L"LockGrass3", L"Texture\\lockgrass3.bmp");
		if (_cnt == 4)
			m_pTex = ResMgr::GetInst()->TexLoad(L"LockGrass4", L"Texture\\lockgrass4.bmp");
		if (_cnt == 5)
			m_pTex = ResMgr::GetInst()->TexLoad(L"LockGrass5", L"Texture\\lockgrass5.bmp");
		break;
	case TILE_TYPE::TELEPORT:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Teleport", L"Texture\\teleport.bmp");
		break;
	case TILE_TYPE::MOVEL:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Movel", L"Texture\\arrowleft.bmp");
		break;
	case TILE_TYPE::MOVELU:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Movelu", L"Texture\\arrowleftup.bmp");
		break;
	case TILE_TYPE::MOVELD:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Moveld", L"Texture\\arrowleftdown.bmp");
		break;
	case TILE_TYPE::MOVER:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Mover", L"Texture\\arrowright.bmp");
		break;
	case TILE_TYPE::MOVERU:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Moveru", L"Texture\\arrowrightup.bmp");
		break;
	case TILE_TYPE::MOVERD:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Moverd", L"Texture\\arrowrightdown.bmp");
		break;
	case TILE_TYPE::WIND:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Wind", L"Texture\\wind.bmp");
		break;
	case TILE_TYPE::PLUS:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Plus", L"Texture\\plus.bmp");
		break;
	case TILE_TYPE::MINUS:
		m_pTex = ResMgr::GetInst()->TexLoad(L"Minus", L"Texture\\minus.bmp");
		break;
	}
}

TileImage::~TileImage()
{
}

void TileImage::Update()
{
}

void TileImage::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	int Width = m_pTex->GetWidth();
	int Height = m_pTex->GetHeight();
	float centerX = vPos.x;
	float centerY = vPos.y;

	float left = centerX - (Width * (vScale.x / 200));
	float top = centerY - (Height * (vScale.y / 200));

	TransparentBlt(_dc, left, top,
		Width * (vScale.x / 100), Height * (vScale.y / 100),
		m_pTex->GetDC(), 0, 0,
		Width, Height, RGB(255, 0, 255));
}