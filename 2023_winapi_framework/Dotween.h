#pragma once
#include "Object.h"
class Texture;
class Dotween : public Object
{
public:
	Dotween(Object* _target, const Vec2& value, const float& _fdelay, DOTWEEN_TYPE _etype);
	Dotween(Object* _target, const Vec2& value, const float& _fdelay, const float& _fwait, DOTWEEN_TYPE _etype);
	Dotween(Texture* _target, const float& value, const float& originvalue, const float& _fdelay, DOTWEEN_TYPE _etype);
	Dotween(Texture* _target, const float& value, const float& originvalue, const float& _fdelay, const float& _fwait, DOTWEEN_TYPE _etype);
public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
public:
	const Object* GetTarget() const { return m_target; }
	const bool& GetPlay()const { return m_isBegin; }
	const DOTWEEN_TYPE& GetType() { return m_etype; }

private:
	void DoMove();
	void DoScale();
	void DoRotate();
	void DoFade();
	void DoKill();
	void SetOriginVal(DOTWEEN_TYPE _etype);
private:
	Object*		 m_target;
	Vec2		 m_voriginval;
	Vec2		 m_vendval;
	float		 m_fcurtime;
	float		 m_ftime;
	float		 m_fwaittime;
	bool		 m_isBegin;
	DOTWEEN_TYPE m_etype;
	Texture*	 m_pTex;
	float		 m_foriginval;
	float		 m_fendval;
};