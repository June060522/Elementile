#pragma once
class Texture;
class Object;
class GameSceneUI
{
public:
	void Init();
	void Update();
	void Render(HDC _dc);
	void Release();
private:
	void UIRender(HDC _dc);

public:
	void SetMenuOpen(const bool _value) { m_isOpen = _value; }
	bool& GetMenuOpen() { return m_isOpen; }

private:
	Texture* m_pMenuTex;
	Texture* m_pRETex;
	Texture* m_pMainTex;
	Texture* m_pLvTex;
	Texture* m_pSoundTex;

	bool m_isOpen;
	bool m_isStageOpen;

	Object* m_pMenu;
	Object* m_pRe;
	Object* m_pMain;
	Object* m_pLv;
	Object* m_pSound;
};