#pragma once
#include "Scene.h"
class Start_Scene :
    public Scene
{
public:
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    virtual void Release() override;
private:
    Vec2 pos = Vec2(500, 350);
    vector<Object*> m_vObj;
};

