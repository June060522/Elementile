#pragma once
class Texture;
class GameSceneUI;
class GameInfoPanel
{
public:
	GameInfoPanel(GameSceneUI* _pGameSceneUI);

public:
	virtual void Render(HDC _dc);
	virtual void Update();

private:
	void ExplainRender(HDC _dc);
	void BGRender(HDC _dc);
	void TexRender(HDC _dc);
	void BGUpdate();

private:
	GameSceneUI* m_pGameSceneUI;
	Texture* m_pDarkBG;
	Texture* m_pBack;

	Texture* m_pFire;
	Texture* m_pWater;
	Texture* m_pGrass;
	Texture* m_pWind;
	Texture* m_pArrowRU;
	Texture* m_pArrowRD;
	Texture* m_pArrowL;
	Texture* m_pArrowR;
	Texture* m_pLockF;
	Texture* m_pLockW;
	Texture* m_pLockG;
	Texture* m_pPlus;
	Texture* m_pMinus;
	Texture* m_pTeleport;
};