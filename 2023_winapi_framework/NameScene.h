#pragma once
#include "Scene.h"
class NameScene :
    public Scene
{
public:
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    virtual void Release() override;
private:
    Vec2 pos = Vec2(500, 350);
    Object* m_string1;
    Object* m_string2;
    Object* m_string3;
};


