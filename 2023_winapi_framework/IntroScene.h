#pragma once
#include "Scene.h"
class UIText;
class IntroScene :
    public Scene
{
public:
    virtual void Init() override;
    virtual void Update() override;
    float lerp(float a, float b, float t);
    virtual void Render(HDC _dc) override;
    virtual void Release() override;
private:
    Vec2 pos = Vec2(500, 350);
    //int darknessLevel;
    //float elapsedTime;
    //const float darknessActivationTime = 5;
     DWORD lastCharTime;
     UIText* m_string;
};

