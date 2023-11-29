#pragma once
#include "Object.h"
#include "Scene.h"
//#include "Bullet.h"

class DevMin :
    public Object
{
public:
    //void Init();
    void Update() override;
    void Render(HDC _dc) override;
    //void Release();
};

