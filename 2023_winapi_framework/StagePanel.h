#pragma once
class Texture;
class GameSceneUI;
class StagePanel
{
public:
	StagePanel(GameSceneUI* _pGameSceneUI);
public:
	void Update();
	void Render(HDC _dc);
private:
	GameSceneUI* m_pGameSceneUI;

	Texture* m_pDarkBG;
	Texture* m_pBack;
};

