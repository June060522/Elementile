#pragma once
class Texture;
class Object;
class StagePanel;
class GameSceneUI
{
public:
	void Init();
	void Update();
	void Render(HDC _dc);
	void Release();
public:
	void UIRender(HDC _dc);

public:
	void SetMenuOpen(const bool _value) { m_isOpen = _value; }
	bool& GetMenuOpen() { return m_isOpen; }
	void SetStagePenalOpen(const bool _value) { m_isStageOpen = _value; }
	bool& GetStagePenalOpen() { return m_isStageOpen; }

private:
	Texture* m_pMenuTex;
	Texture* m_pRETex;
	Texture* m_pMainTex;
	Texture* m_pLvTex;
	Texture* m_pSoundTex;
	Texture* m_pRankingTex;

	bool m_isOpen;
	bool m_isStageOpen;

	Object* m_pMenu;
	Object* m_pRe;
	Object* m_pMain;
	Object* m_pLv;
	Object* m_pSound;
	Object* m_pRanking;

	StagePanel* m_pStagePanel;

	bool m_isBegin;
};