#pragma once
#include "Object.h"
class Texture;
class Button :
    public Object
{
public:
    Button();
    ~Button();
    
public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
public:
     void OnClick();
     void Func(HDC _dc);
private:
    HWND _hWnd;
    POINT mousePos;
    Texture* m_pTex;
};