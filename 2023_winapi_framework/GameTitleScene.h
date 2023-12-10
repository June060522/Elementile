#pragma once
#include "Object.h"
#include "Scene.h"
class object;
class GameTitleScene :
    public Scene
{
public:
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    virtual void Release() override;
private:
    Object* m_string;
    float timer;
};

