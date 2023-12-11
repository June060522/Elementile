#pragma once
#include "Object.h"
class Texture;
class Image :
    public Object
{
public:
    Image(Texture* _tex, Vec2 _pos, Vec2 _scale, Vec2 _menuPos);
public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
protected:
    virtual void Function();
protected:
    Texture* m_pTex;
    Vec2 m_vendPos;
    Vec2 m_vmenuPos;
};

