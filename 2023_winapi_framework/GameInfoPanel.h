#pragma once
class Texture;
class GameInfoPanel
{
public:
	GameInfoPanel(wstring s);

public:
	virtual void Render(HDC _dc);
	virtual void Update();

public:
	bool isGetopen() { return m_isopen; }
	void Open() { m_isopen = true; }
	void Close() { m_isopen = false; }
protected:
	void BGRender(HDC _dc);
	void BGUpdate();

private:
	wstring m_wexplain;
	bool m_isopen;

	Texture* m_pDarkBG;
	Texture* m_pBack;
};

