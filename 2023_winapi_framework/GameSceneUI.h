#pragma once
class Texture;
class Object;
class StagePanel;
class RankingPanel;
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
	void SetRankingPenalOpen(const bool _value) { m_isRankingOpen = _value; }
	bool& GetRankingPenalOpen() { return m_isRankingOpen; }
	void SetIdAndRank(string _id,int _val,int _idx)
	{
		wstring id = L"";
		id.assign(_id.begin(), _id.end());
		m_wid[_idx] = id;
		m_iscore[_idx] = _val;
	}
	wstring GetId(int _idx) { return m_wid[_idx]; }
	int GetScore(int _idx) { return m_iscore[_idx]; }

private:
	Texture* m_pMenuTex;
	Texture* m_pRETex;
	Texture* m_pMainTex;
	Texture* m_pLvTex;
	Texture* m_pSoundTex;
	Texture* m_pRankingTex;

	bool m_isOpen;
	bool m_isStageOpen;
	bool m_isRankingOpen;

	Object* m_pMenu;
	Object* m_pRe;
	Object* m_pMain;
	Object* m_pLv;
	Object* m_pSound;
	Object* m_pRanking;

	StagePanel* m_pStagePanel;
	RankingPanel* m_pRankingPanel;

	wstring m_wid[3];
	int m_iscore[3];
};