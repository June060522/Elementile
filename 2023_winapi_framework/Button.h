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
     void Func();
private:
    HWND _hWnd;
    Texture* m_pTex;
};