#pragma once
#include "Object.h"
class UIText :
    public Object
{
public:
    UIText(Vec2 _vPos, wstring _wstr);
public:
    //UIText(Vec2 _vPos, wstring _wstr);
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
protected:
    wstring m_wstr;
};