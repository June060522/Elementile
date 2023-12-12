#pragma once
class Texture;
class GameSceneUI;
class StageIcon;
class StagePanel
{
public:
	StagePanel(GameSceneUI* _pGameSceneUI);
public:
	void Update();
	void Render(HDC _dc);
private:
	void BGRender(HDC _dc);
	void BackIconRender(HDC _dc);
	void StageRender(HDC _dc);

public:
	int& GetPage() { return m_iPage; }
private:
	GameSceneUI* m_pGameSceneUI;

	Texture* m_pDarkBG;
	Texture* m_pBack;

	vector<StageIcon*> m_vecStageIcon;
	int m_iPage = 0;
};

