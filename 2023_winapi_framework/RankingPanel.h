#pragma once
class Texture;
class GameSceneUI;
class RankingPanel
{
public:
	RankingPanel(GameSceneUI* _pGameSceneUI);
public:
	void Update();
	void Render(HDC _dc);
private:
	void BGRender(HDC _dc);
	void BackIconRender(HDC _dc);
	void RankingRender(HDC _dc);

private:
	GameSceneUI* m_pGameSceneUI;

	Texture* m_pDarkBG;
	Texture* m_pBack;
	Texture* m_pFirstPlace;
	Texture* m_pSecondPlace;
	Texture* m_pThirdPlace;
};

