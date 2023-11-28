#pragma once
#include "Object.h"
class Dotween : public Object
{
public:
	Dotween(Object* _target, const Vec2& value, const float& _fdelay, DOTWEEN_TYPE _etype);
	Dotween(Object* _target, const Vec2& value, const float& _fdelay,const float& _fwait, DOTWEEN_TYPE _etype);
public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
private:
	void DoMove();
	void DoScale();
private:
	Object*		 m_target;
	Vec2		 m_voriginval;
	Vec2		 m_vendval;
	float		 m_fcurtime;
	float		 m_ftime;
	float		 m_fwaittime;
	DOTWEEN_TYPE m_etype;
};