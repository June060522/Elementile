#include "pch.h"
#include "UIText.h"

UIText::UIText(Vec2 _vPos, wstring _wstr)
	:m_vPos(_vPos)
	,m_wstr(_wstr)
{
}

void UIText::Update()
{
}

void UIText::Render(HDC _dc)
{
	TextOut(_dc, m_vPos.x, m_vPos.y, m_wstr.c_str(), wcslen(m_wstr.c_str()));
}