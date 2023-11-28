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
    mousePos = KeyMgr::GetInst()->GetMousePos();

    if (mousePos.x >= 10 && mousePos.x <= 150 &&
        mousePos.y >= 10 && mousePos.y <= 150)
    {
        if (leftMouseButtonState == KEY_STATE::DOWN || leftMouseButtonState == KEY_STATE::PRESS)
        {
            //Func();
            DestroyWindow(GetActiveWindow());
        }
    }

    if (mousePos.x >= 700 && mousePos.x <= 800 && mousePos.y >= 10 && mousePos.y <= 150) {
        //Func(_dc);
    }
}

void Button::Render(HDC _dc)
{
    Func(_dc);
}

void Button::Func(HDC _dc)
{
    Rectangle(_dc, 100, 10, 100, 150);
}

void Button::OnClick()
{

}
