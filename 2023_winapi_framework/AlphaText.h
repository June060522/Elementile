#pragma once
#include "UIText.h"
class AlphaText :
    public UIText
{
public:
    AlphaText(Vec2 _vPos, wstring _wstr);

    void SetAlpha(float alpha);
private:
    float m_alpha;
};


