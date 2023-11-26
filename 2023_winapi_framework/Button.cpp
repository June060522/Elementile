#include "pch.h"
#include "Button.h"
#include "KeyMgr.h"

Button::Button()
{

}

Button::~Button()
{
}

void Button::Update()
{
    OnClick();
    const KEY_STATE& leftMouseButtonState = KeyMgr::GetInst()->GetKey(KEY_TYPE::LBUTTON);
    const POINT& mousePos = KeyMgr::GetInst()->GetMousePos();

    if (mousePos.x >= 10 && mousePos.x <= 150 &&
        mousePos.y >= 10 && mousePos.y <= 150)
    {
        if (leftMouseButtonState == KEY_STATE::DOWN || leftMouseButtonState == KEY_STATE::PRESS)
        {
            Func();
            DestroyWindow(GetActiveWindow());
        }
    }
}

void Button::Render(HDC _dc)
{
	RECT_RENDER(100, 100, 100, 100, _dc);
}

void Button::OnClick()
{

}

void Button::Func()
{

}
