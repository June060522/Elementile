#pragma once
#include "Scene.h"
class Object;
class IntroScene :
    public Scene
{
public:
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    virtual void Release() override;
    //virtual void SetTextSize(HWND _hWnd, int newSize);
private:
    Vec2 pos = Vec2(550, 350);
     DWORD lastCharTime;
     Object* m_string;
     vector<Object*> m_vObj;
     vector<Object*> m_vObj2;
     float deltaTime;
};

