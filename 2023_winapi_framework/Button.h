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
    void OnClick(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);
    virtual void Func();
private:
    Texture* m_pTex;
};