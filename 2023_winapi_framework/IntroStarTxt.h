#pragma once
#include "UIText.h"
class IntroStarTxt
	: public UIText
{
public:
	IntroStarTxt(int _iFontSize, Vec2 _vPos, wstring _wstr, int _iSetSize
		, float _fMaxTime, float _fWaitTime = 0);
public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;
private:
	int m_ioriginval;
	int m_iFontSize;
	int m_iSetSize;
	float m_fMaxTime;
	float m_fCurTime;
	float m_fWaitTime;
};