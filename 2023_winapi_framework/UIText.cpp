#include "pch.h"
#include "UIText.h"
#include "Object.h"

UIText::UIText(Vec2 _vPos, wstring _wstr)
	:m_wstr(_wstr)
{
	SetPos(_vPos);
}

void UIText::Update()
{
}

void UIText::Render(HDC _dc)
{
	TextOut(_dc, GetPos().x, GetPos().y, m_wstr.c_str(), wcslen(m_wstr.c_str()));
}