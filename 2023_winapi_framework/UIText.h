#pragma once
#include "Object.h"
class UIText :
    public Object
{
public:
    UIText(Vec2 _vPos, wstring _wstr);
public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
private:
    wstring m_wstr;
};