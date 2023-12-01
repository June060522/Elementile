#pragma once
class Animator;
class Object
{
public:
	Object();
	virtual ~Object();
//public:	// 크기, 위치
	//POINT m_ptPos;
	//POINT m_ptScale;
public:
	virtual void Update();
	virtual void FinalUpdate() final;
	virtual void Render(HDC _dc);
	void Component_Render(HDC _dc);
public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	const Vec2& GetPos() const { return m_vPos; }
	const Vec2& GetScale() const { return m_vScale; }
	Animator* GetAnimator()
	{
		return m_pAnimator;
	}
	const wstring& GetName() const { return m_strName; }
	void SetName(wstring _name) { m_strName = _name; }
	bool GetIsDead() const { return !m_IsAlive; }
private:
	void SetDead() { m_IsAlive = false; }
	friend class EventMgr;
public:
	void CreateAnimator();
private:
	Vec2 m_vPos; // 위치
	Vec2 m_vScale; // 크기
	wstring m_strName; // 이름.
	bool m_IsAlive;
	float m_AlphaValue;
	Animator* m_pAnimator;
};

