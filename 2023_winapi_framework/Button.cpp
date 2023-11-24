#include "pch.h"
#include "Button.h"

Button::Button()
{

}

Button::~Button()
{
}

void Button::Update()
{
	POINT cursorPos;
	GetCursorPos(&cursorPos);
	ScreenToClient(GetActiveWindow(), &cursorPos);

    if (cursorPos.x >= 100 && cursorPos.x <= 200 &&
        cursorPos.y >= 100 && cursorPos.y <= 200)
    {
        //OnClick();
    }
}

void Button::Render(HDC _dc)
{
	RECT_RENDER(100, 100, 100, 100, _dc);
}

void Button::OnClick(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    Func();
    DestroyWindow(_hWnd); 
}

void Button::Func()
{
}
