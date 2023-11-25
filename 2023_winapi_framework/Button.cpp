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
    OnClick();
}

void Button::Render(HDC _dc)
{
	RECT_RENDER(100, 100, 100, 100, _dc);
}

void Button::OnClick()
{
    HWND hWnd = GetActiveWindow();

    POINT cursorPos;
    GetCursorPos(&cursorPos);
    ScreenToClient(hWnd, &cursorPos);

    if (cursorPos.x >= 10 && cursorPos.x <= 150 &&
        cursorPos.y >= 10 && cursorPos.y <= 150)
    {
        Func();
        DestroyWindow(hWnd);
    }
}

void Button::Func()
{

}
