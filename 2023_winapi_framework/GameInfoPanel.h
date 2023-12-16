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
	void BGUpdate();

private:
	
	GameSceneUI* m_pGameSceneUI;
	Texture* m_pDarkBG;
	Texture* m_pBack;
};

